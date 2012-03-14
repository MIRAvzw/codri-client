/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "registrationcontroller.h"

// Library includes
#include <QtCore/QTimer>


//
// Construction and destruction
//

Codri::RegistrationController::RegistrationController(ServerClient* iServerClient, QObject *iParent)
    : QStateMachine(iParent), mServerClient(iServerClient) {
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup("NetworkInterface");

    // Setup logging
    mLogger =  Log4Qt::Logger::logger(metaObject()->className());

    // State machine
    // TODO: log transitions
    initFSM();
}


//
// Construction helpers
//

void Codri::RegistrationController::initFSM() {
    QState *tRegister = new QState(this);
    QState *tConflict = new QState(this);
    QState *tRefresh = new QState(this);
    setInitialState(tRegister);


    // REGISTERING STATE //

    // Action on activation
    connect(tRegister, SIGNAL(entered()), mServerClient, SLOT(registerKiosk()));

    // Transition on registration success
    tRegister->addTransition(mServerClient, SIGNAL(registrationSuccess()), tRefresh);

    // Transition on registration conflict
    tRegister->addTransition(mServerClient, SIGNAL(registrationConflict()), tConflict);

    // Transition on registration failure (delayed re-activation)
    QTimer *tRegisterRetry = new QTimer(this);
    tRegisterRetry->setSingleShot(true);
    tRegisterRetry->setInterval(mSettings->value("reconnect", 60*1000).toInt());
    connect(mServerClient, SIGNAL(registrationFailure(uint)), tRegisterRetry, SLOT(start()));
    tRegister->addTransition(tRegisterRetry, SIGNAL(timeout()), tRegister);


    // CONFLICT STATE //

    // Action on activation (try to unregister the existing kiosk)
    connect(tConflict, SIGNAL(entered()), mServerClient, SLOT(unregisterKiosk()));

    // Transition on unregister success
    tConflict->addTransition(mServerClient, SIGNAL(unregisterSuccess()), tRegister);

    // Transition on unregister failure (delayed restart of _entire_ registration procedure)
    QTimer *tConflictRetry = new QTimer(this);
    tConflictRetry->setSingleShot(true);
    tConflictRetry->setInterval(mSettings->value("reconnect", 60*1000).toInt());
    connect(mServerClient, SIGNAL(unregisterFailure(uint)), tConflictRetry, SLOT(start()));
    tConflict->addTransition(tConflictRetry, SIGNAL(timeout()), tRegister);


    // REFRESH STATE //

    // Action on activation
    connect(tRefresh, SIGNAL(entered()), mServerClient, SLOT(refreshKiosk()));

    // Transition on success (delayed re-activation)
    QTimer *tRefreshDelay = new QTimer(this);
    tRefreshDelay->setSingleShot(true);
    tRefreshDelay->setInterval(mSettings->value("heartbeat", 30*1000).toInt());
    connect(mServerClient, SIGNAL(refreshSuccess()), tRefreshDelay, SLOT(start()));
    tRefresh->addTransition(tRefreshDelay, SIGNAL(timeout()), tRefresh);

    // Transition on failure (restart _entire_ registration procedure)
    tRefresh->addTransition(mServerClient, SIGNAL(refreshFailure(uint)), tRegister);
}
