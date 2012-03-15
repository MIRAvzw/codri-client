/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "network/serverclient.h"

// Local includes
#include "mainapplication.h"
#include "auxiliary/parameterizedsignaltransition.h"
#include "auxiliary/comparingsignaltransition.h"


//
// Construction and destruction
//

Codri::ServerClient::ServerClient(const QString &iLocation, QObject *iParent)
    : QStateMachine(iParent) {
    // Setup logging
    mLogger =  Log4Qt::Logger::logger(metaObject()->className());

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
    mIdle = new QState(this);
    QState *tRegistering = new QState(this);
    QState *tRefreshing = new QState(this);
    QState *tUnregistering = new QState(this);
    setInitialState(mIdle);


    // IDLE STATE //

    // Transitions to active states
    mIdle->addTransition(this, SIGNAL(_registerKiosk()), tRegistering);
    mIdle->addTransition(this, SIGNAL(_refreshKiosk()), tRefreshing);
    mIdle->addTransition(this, SIGNAL(_unregisterKiosk()), tUnregistering);


    // REGISTERING STATE //

    // Action on activation
    connect(tRegistering, SIGNAL(entered()), mImplementation, SLOT(registerKiosk()));

    // Transition on request success
    QSignalTransition *tRegisterSuccess = new QSignalTransition(mImplementation, SIGNAL(_onRequestSuccess()));
    tRegisterSuccess->setTargetState(mIdle);
    tRegistering->addTransition(tRegisterSuccess);
    connect(tRegisterSuccess, SIGNAL(triggered()), this, SIGNAL(registrationSuccess()));

    // Transition on request error (HTTP error 409)
    ComparingSignalTransition *tRegisterConflict = new ComparingSignalTransition(mImplementation, SIGNAL(_onRequestFailure(uint)), ComparingSignalTransition::EQUALITY, (uint) 409);
    tRegisterConflict->setTargetState(mIdle);
    tRegistering->addTransition(tRegisterConflict);
    connect(tRegisterConflict, SIGNAL(triggered()), this, SIGNAL(registrationConflict()));

    // Transition on request error (all other errors)
    ComparingSignalTransition *tRegisterFailure = new ComparingSignalTransition(mImplementation, SIGNAL(_onRequestFailure(uint)), ComparingSignalTransition::INEQUALITY, (uint) 409);
    tRegisterFailure->setTargetState(mIdle);
    tRegistering->addTransition(tRegisterFailure);
    connect(tRegisterFailure, SIGNAL(triggeredUInt(uint)), this, SIGNAL(registrationFailure(uint)));


    // REFRESHING STATE //

    // Action on activation
    connect(tRefreshing, SIGNAL(entered()), mImplementation, SLOT(refreshKiosk()));

    // Transition on request success
    QSignalTransition *tRefreshSuccess = new QSignalTransition(mImplementation, SIGNAL(_onRequestSuccess()));
    tRefreshSuccess->setTargetState(mIdle);
    tRefreshing->addTransition(tRefreshSuccess);
    connect(tRefreshSuccess, SIGNAL(triggered()), this, SIGNAL(refreshSuccess()));

    // Transition on request error
    ParameterizedSignalTransition *tRefreshFailure = new ParameterizedSignalTransition(mImplementation, SIGNAL(_onRequestFailure(uint)));
    tRefreshFailure->setTargetState(mIdle);
    tRefreshing->addTransition(tRefreshFailure);
    connect(tRefreshFailure, SIGNAL(triggeredUInt(uint)), this, SIGNAL(refreshFailure(uint)));


    // UNREGISTERING STATE //

    // Action on activation
    connect(tUnregistering, SIGNAL(entered()), mImplementation, SLOT(unregisterKiosk()));

    // Transition on request success
    QSignalTransition *tUnregisterSuccess = new QSignalTransition(mImplementation, SIGNAL(_onRequestSuccess()));
    tUnregisterSuccess->setTargetState(mIdle);
    tUnregistering->addTransition(tUnregisterSuccess);
    connect(tUnregisterSuccess, SIGNAL(triggered()), this, SIGNAL(unregisterSuccess()));

    // Transition on request error
    ParameterizedSignalTransition *tUnregisterFailure = new ParameterizedSignalTransition(mImplementation, SIGNAL(_onRequestFailure(uint)));
    tUnregisterFailure->setTargetState(mIdle);
    tUnregistering->addTransition(tUnregisterFailure);
    connect(tUnregisterFailure, SIGNAL(triggeredUInt(uint)), this, SIGNAL(unregisterFailure(uint)));
}


//
// Public interface
//

void Codri::ServerClient::registerKiosk() {
    if (configuration().contains(mIdle)) {
        emit _registerKiosk();
    } else {
        mLogger->warn() << "Request to register while busy";
        QTimer::singleShot(100, this, SLOT(registerKiosk()));
    }
}

void Codri::ServerClient::refreshKiosk() {
    if (configuration().contains(mIdle)) {
        emit _refreshKiosk();
    } else {
        mLogger->warn() << "Request to refresh while busy";
        QTimer::singleShot(100, this, SLOT(refreshKiosk()));
    }
}

void Codri::ServerClient::unregisterKiosk() {
    if (configuration().contains(mIdle)) {
        emit _unregisterKiosk();
    } else {
        mLogger->warn() << "Request to unregister while busy";
        QTimer::singleShot(100, this, SLOT(unregisterKiosk()));
    }
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
