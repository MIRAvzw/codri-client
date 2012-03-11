/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Local includes
#include "serverclient.h"
#include "mainapplication.h"


//
// Construction and destruction
//

MIRA::ServerClient::ServerClient(const QString &iLocation, QObject *iParent) : QStateMachine(iParent), mLocation(iLocation)
{
    // Network access manager
    mNetworkAccessManager = new QNetworkAccessManager(this);
    connect(mNetworkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(_onRequestFinished(QNetworkReply*)));

    // QJson objects
    mParser = new QJson::Parser();
    mSerializer = new QJson::Serializer();

    // State machine
    // TODO: log transitions
    initFSM();
    start();
}

MIRA::ServerClient::~ServerClient()
{
    // QJson objects
    delete mParser;
    delete mSerializer;
}


//
// Construction helpers
//

void MIRA::ServerClient::initFSM()
{
    QState *tIdle = new QState(this);
    QState *tRegister = new QState(this);
    QState *tRefresh = new QState(this);
    QState *tUnregister = new QState(this);
    setInitialState(tIdle);


    // IDLE STATE //

    // Transitions to active states
    tIdle->addTransition(this, SIGNAL(_registerKiosk()), tRegister);
    tIdle->addTransition(this, SIGNAL(_refreshKiosk()), tRefresh);
    tIdle->addTransition(this, SIGNAL(_unregisterKiosk()), tUnregister);


    // REGISTER STATE //

    // Transition on request success
    QSignalTransition *tRegisterSuccess = new QSignalTransition(this, SIGNAL(_onRequestSuccess()));
    tRegisterSuccess->setTargetState(tIdle);
    tRegister->addTransition(tRegisterSuccess);
    connect(tRegisterSuccess, SIGNAL(triggered()), this, SIGNAL(registrationSuccess()));

    // Transition on request error (HTTP error 409)
    ComparingSignalTransition *tRegisterConflict = new ComparingSignalTransition(this, SIGNAL(_onRequestFailure(uint)), ComparingSignalTransition::EQUALITY, 409);
    tRegisterConflict->setTargetState(tIdle);
    tRegister->addTransition(tRegisterConflict);
    connect(tRegisterConflict, SIGNAL(triggered()), this, SIGNAL(registrationConflict()));

    // Transition on request error (all other errors)
    ComparingSignalTransition *tRegisterFailure = new ComparingSignalTransition(this, SIGNAL(_onRequestFailure(uint)), ComparingSignalTransition::INEQUALITY, 409);
    tRegisterFailure->setTargetState(tIdle);
    tRegister->addTransition(tRegisterFailure);
    connect(tRegisterFailure, SIGNAL(dataTriggered(QVariant)), this, SIGNAL(registrationFailure(QVariant)));


    // REFRESH STATE //

    // Transition on request success
    QSignalTransition *tRefreshSuccess = new QSignalTransition(this, SIGNAL(_onRequestSuccess()));
    tRefreshSuccess->setTargetState(tIdle);
    tRefresh->addTransition(tRefreshSuccess);
    connect(tRefreshSuccess, SIGNAL(triggered()), this, SIGNAL(refreshSuccess()));

    // Transition on request error
    ParameterizedSignalTransition *tRefreshFailure = new ParameterizedSignalTransition(this, SIGNAL(_onRequestFailure(uint)));
    tRefreshFailure->setTargetState(tIdle);
    tRefresh->addTransition(tRefreshFailure);
    connect(tRefreshFailure, SIGNAL(dataTriggered(QVariant)), this, SIGNAL(refreshFailure(QVariant)));


    // UNREGISTER STATE //

    // Transition on request success
    QSignalTransition *tUnregisterSuccess = new QSignalTransition(this, SIGNAL(_onRequestSuccess()));
    tUnregisterSuccess->setTargetState(tIdle);
    tUnregister->addTransition(tUnregisterSuccess);
    connect(tUnregisterSuccess, SIGNAL(triggered()), this, SIGNAL(unregisterSuccess()));

    // Transition on request error
    ParameterizedSignalTransition *tUnregisterFailure = new ParameterizedSignalTransition(this, SIGNAL(_onRequestFailure(uint)));
    tUnregisterFailure->setTargetState(tIdle);
    tUnregister->addTransition(tUnregisterFailure);
    connect(tUnregisterFailure, SIGNAL(dataTriggered(QVariant)), this, SIGNAL(unregisterFailure(QVariant)));
}


//
// Functionality
//


void MIRA::ServerClient::registerKiosk()
{
    const Kiosk *tKiosk = MainApplication::instance()->kiosk();

    QVariantMap tRequest;
    tRequest["vendor"] = tKiosk->getVendor();
    tRequest["model"] = tKiosk->getModel();
    tRequest["port"] = tKiosk->getPort();

    emit _registerKiosk();
    doPOST("/network/kiosks/" + tKiosk->getUuid().toString().replace('{', "").replace('}', ""), tRequest);
}

void MIRA::ServerClient::refreshKiosk()
{
    const Kiosk *tKiosk = MainApplication::instance()->kiosk();

    emit _refreshKiosk();
    doPUT("/network/kiosks/" + tKiosk->getUuid().toString().replace('{', "").replace('}', "") + "/heartbeat");
}

void MIRA::ServerClient::unregisterKiosk()
{
    const Kiosk *tKiosk = MainApplication::instance()->kiosk();

    emit _unregisterKiosk();
    doDELETE("/network/kiosks/" + tKiosk->getUuid().toString().replace('{', "").replace('}', ""));
}


//
// Private signal handlers
//


void MIRA::ServerClient::_onRequestFinished(QNetworkReply *iReply)
{
    // Get reply data
    // TODO: do something with the error -- is the request retried if it fails?
    if (iReply->error() == QNetworkReply::NoError)
        emit _onRequestSuccess();
    else {
        unsigned int tErrorCode = iReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).isNull()
                ? 0

                : iReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();
        emit _onRequestFailure(tErrorCode);
    }
}


//
// Auxiliary
//

void MIRA::ServerClient::doGET(const QString& iPath)
{
    mNetworkAccessManager->get(createRequest(iPath));
}

void MIRA::ServerClient::doPUT(const QString& iPath, const QVariant& iPayload)
{
    mNetworkAccessManager->put(createRequest(iPath), mSerializer->serialize(iPayload));
}

void MIRA::ServerClient::doPOST(const QString& iPath, const QVariant& iPayload)
{
    mNetworkAccessManager->post(createRequest(iPath), mSerializer->serialize(iPayload));
}

void MIRA::ServerClient::doDELETE(const QString& iPath)
{
    mNetworkAccessManager->deleteResource(createRequest(iPath));
}

QNetworkRequest MIRA::ServerClient::createRequest(const QString& iPath)
{
    QNetworkRequest tRequest;
    tRequest.setUrl(QUrl(mLocation + "/" + iPath));
    tRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    return tRequest;
}
