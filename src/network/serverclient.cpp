/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "serverclient.h"

// Local includes
#include "mainapplication.h"


//
// Construction and destruction
//

Codri::ServerClient::ServerClient(const QString &iLocation, QObject *iParent)
    : QStateMachine(iParent) {
    // Actual implementation
    mImplementation = new ServerClientPrivate(iLocation, this);

    // State machine
    // TODO: log transitions
    initFSM();
    start();
}

Codri::ServerClientPrivate::ServerClientPrivate(const QString &iLocation, QObject *iParent)
    : QObject(iParent), mLocation(iLocation) {
    // Network access manager
    mNetworkAccessManager = new QNetworkAccessManager(this);
    connect(mNetworkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(_onRequestFinished(QNetworkReply*)));

    // QJson objects
    mParser = new QJson::Parser();
    mSerializer = new QJson::Serializer();
}

Codri::ServerClientPrivate::~ServerClientPrivate() {
    // QJson objects
    delete mParser;
    delete mSerializer;
}


//
// Construction helpers
//

void Codri::ServerClient::initFSM() {
    QState *tIdle = new QState(this);
    QState *tRegistering = new QState(this);
    QState *tRefreshing = new QState(this);
    QState *tUnregistering = new QState(this);
    setInitialState(tIdle);


    // IDLE STATE //

    // Transitions to active states
    tIdle->addTransition(this, SIGNAL(_registerKiosk()), tRegistering);
    tIdle->addTransition(this, SIGNAL(_refreshKiosk()), tRefreshing);
    tIdle->addTransition(this, SIGNAL(_unregisterKiosk()), tUnregistering);


    // REGISTERING STATE //

    // Action on activation
    connect(tRegistering, SIGNAL(entered()), mImplementation, SLOT(registerKiosk()));

    // Transition on request success
    QSignalTransition *tRegisterSuccess = new QSignalTransition(mImplementation, SIGNAL(_onRequestSuccess()));
    tRegisterSuccess->setTargetState(tIdle);
    tRegistering->addTransition(tRegisterSuccess);
    connect(tRegisterSuccess, SIGNAL(triggered()), this, SIGNAL(registrationSuccess()));

    // Transition on request error (HTTP error 409)
    ComparingSignalTransition *tRegisterConflict = new ComparingSignalTransition(mImplementation, SIGNAL(_onRequestFailure(uint)), ComparingSignalTransition::EQUALITY, 409);
    tRegisterConflict->setTargetState(tIdle);
    tRegistering->addTransition(tRegisterConflict);
    connect(tRegisterConflict, SIGNAL(triggered()), this, SIGNAL(registrationConflict()));

    // Transition on request error (all other errors)
    ComparingSignalTransition *tRegisterFailure = new ComparingSignalTransition(mImplementation, SIGNAL(_onRequestFailure(uint)), ComparingSignalTransition::INEQUALITY, 409);
    tRegisterFailure->setTargetState(tIdle);
    tRegistering->addTransition(tRegisterFailure);
    connect(tRegisterFailure, SIGNAL(dataTriggered(QVariant)), this, SIGNAL(registrationFailure(QVariant)));


    // REFRESHING STATE //

    // Action on activation
    connect(tRefreshing, SIGNAL(entered()), mImplementation, SLOT(refreshKiosk()));

    // Transition on request success
    QSignalTransition *tRefreshSuccess = new QSignalTransition(mImplementation, SIGNAL(_onRequestSuccess()));
    tRefreshSuccess->setTargetState(tIdle);
    tRefreshing->addTransition(tRefreshSuccess);
    connect(tRefreshSuccess, SIGNAL(triggered()), this, SIGNAL(refreshSuccess()));

    // Transition on request error
    ParameterizedSignalTransition *tRefreshFailure = new ParameterizedSignalTransition(mImplementation, SIGNAL(_onRequestFailure(uint)));
    tRefreshFailure->setTargetState(tIdle);
    tRefreshing->addTransition(tRefreshFailure);
    connect(tRefreshFailure, SIGNAL(dataTriggered(QVariant)), this, SIGNAL(refreshFailure(QVariant)));


    // UNREGISTERING STATE //

    // Action on activation
    connect(tUnregistering, SIGNAL(entered()), mImplementation, SLOT(unregisterKiosk()));

    // Transition on request success
    QSignalTransition *tUnregisterSuccess = new QSignalTransition(mImplementation, SIGNAL(_onRequestSuccess()));
    tUnregisterSuccess->setTargetState(tIdle);
    tUnregistering->addTransition(tUnregisterSuccess);
    connect(tUnregisterSuccess, SIGNAL(triggered()), this, SIGNAL(unregisterSuccess()));

    // Transition on request error
    ParameterizedSignalTransition *tUnregisterFailure = new ParameterizedSignalTransition(mImplementation, SIGNAL(_onRequestFailure(uint)));
    tUnregisterFailure->setTargetState(tIdle);
    tUnregistering->addTransition(tUnregisterFailure);
    connect(tUnregisterFailure, SIGNAL(dataTriggered(QVariant)), this, SIGNAL(unregisterFailure(QVariant)));
}


//
// Public interface
//
void Codri::ServerClient::registerKiosk() {
    emit _registerKiosk();
}

void Codri::ServerClient::refreshKiosk() {
    emit _refreshKiosk();
}

void Codri::ServerClient::unregisterKiosk() {
    emit _unregisterKiosk();
}


//
// Functionality
//

void Codri::ServerClientPrivate::registerKiosk() {
    const Kiosk *tKiosk = MainApplication::instance()->kiosk();

    QVariantMap tRequest;
    tRequest["vendor"] = tKiosk->getVendor();
    tRequest["model"] = tKiosk->getModel();
    tRequest["port"] = tKiosk->getPort();

    doPOST("/network/kiosks/" + tKiosk->getUuid().toString().replace('{', "").replace('}', ""), tRequest);
}

void Codri::ServerClientPrivate::refreshKiosk() {
    const Kiosk *tKiosk = MainApplication::instance()->kiosk();

    doPUT("/network/kiosks/" + tKiosk->getUuid().toString().replace('{', "").replace('}', "") + "/heartbeat");
}

void Codri::ServerClientPrivate::unregisterKiosk() {
    const Kiosk *tKiosk = MainApplication::instance()->kiosk();

    doDELETE("/network/kiosks/" + tKiosk->getUuid().toString().replace('{', "").replace('}', ""));
}


//
// Private signal handlers
//


void Codri::ServerClientPrivate::_onRequestFinished(QNetworkReply *iReply) {
    // Get reply data
    // TODO: do something with the error -- is the request retried if it fails?
    if (iReply->error() == QNetworkReply::NoError) {
        emit _onRequestSuccess();
    } else {
        unsigned int tErrorCode = iReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).isNull()
                ? 0

                : iReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();
        emit _onRequestFailure(tErrorCode);
    }
}


//
// Auxiliary
//

void Codri::ServerClientPrivate::doGET(const QString& iPath) {
    mNetworkAccessManager->get(createRequest(iPath));
}

void Codri::ServerClientPrivate::doPUT(const QString& iPath, const QVariant& iPayload) {
    mNetworkAccessManager->put(createRequest(iPath), mSerializer->serialize(iPayload));
}

void Codri::ServerClientPrivate::doPOST(const QString& iPath, const QVariant& iPayload) {
    mNetworkAccessManager->post(createRequest(iPath), mSerializer->serialize(iPayload));
}

void Codri::ServerClientPrivate::doDELETE(const QString& iPath) {
    mNetworkAccessManager->deleteResource(createRequest(iPath));
}

QNetworkRequest Codri::ServerClientPrivate::createRequest(const QString& iPath) {
    QNetworkRequest tRequest;
    tRequest.setUrl(QUrl(mLocation + "/" + iPath));
    tRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    return tRequest;
}