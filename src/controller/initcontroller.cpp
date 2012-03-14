/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "initcontroller.h"


//
// Construction and destruction
//

Codri::InitController::InitController(Controller *iController)
    : QStateMachine(iController), mController(iController) {
    // Setup logging
    mLogger =  Log4Qt::Logger::logger(metaObject()->className());

    // Main states
    mStateInitializing = new QStateMachine(this);
    mStateFailed = new QState(this);
    mStateSuccess = new QFinalState(this);
    setInitialState(mStateInitializing);
    mFinished = false;

    // Subsystem states
    mInitUser = new QState(mStateInitializing);
    mInitPlatform = new QState(mStateInitializing);
    mInitNetwork = new QState(mStateInitializing);
    mInitRepository = new QState(mStateInitializing);
    mStateInitializing->setInitialState(mInitUser);

    // User interface transitions
    connect(mInitUser, SIGNAL(entered()), this, SLOT(initializeUser()));
    mInitUser->addTransition(this, SIGNAL(userSuccess()), mInitPlatform);
    mStateInitializing->addTransition(this, SIGNAL(userFailure()), mStateFailed);

    // Platform interface transitions
    connect(mInitPlatform, SIGNAL(entered()), this, SLOT(initializePlatform()));
    mInitPlatform->addTransition(this, SIGNAL(platformSuccess()), mInitRepository);
    mStateInitializing->addTransition(this, SIGNAL(platformFailure()), mStateFailed);

    // Repository interface transitions
    connect(mInitRepository, SIGNAL(entered()), this, SLOT(initializeRepository()));
    mInitRepository->addTransition(this, SIGNAL(repositorySuccess()), mInitNetwork);
    mStateInitializing->addTransition(this, SIGNAL(repositoryFailure()), mStateFailed);

    // Network interface transitions
    connect(mInitNetwork, SIGNAL(entered()), this, SLOT(initializeNetwork()));
    mStateInitializing->addTransition(this, SIGNAL(networkSuccess()), mStateSuccess);
    mStateInitializing->addTransition(this, SIGNAL(userFailure()), mStateFailed);

    // Main transitions
    connect(this, SIGNAL(finished()), this, SLOT(_onFinished()));
    connect(mStateFailed, SIGNAL(entered()), this, SIGNAL(failure()));
    connect(mStateSuccess, SIGNAL(entered()), this, SIGNAL(success()));
}


//
// Initialization slots
//

void Codri::InitController::initializeUser() {
    try {
        // FIXME: parent?
        mController->mUserInterface = new UserInterface();
        mController->mUserInterface->show();

        emit userSuccess();
    } catch (const QException &iException) {
        mLogger->error() << "User interface initialization failed: " << iException.what();
        foreach (const QString& tCause, iException.causes())
            mLogger->error() << "Caused by: " << tCause;
        emit userFailure();
    }
}

void Codri::InitController::initializePlatform() {
    try {
        // TODO: platform abstraction
        mController->mPlatformInterface = new PlatformInterface(this);

        emit platformSuccess();
    } catch (const QException &iException) {
        mLogger->error() << "Platform interface initialization failed: " << iException.what();
        foreach (const QString& tCause, iException.causes())
            mLogger->error() << "Caused by: " << tCause;
        emit platformFailure();
    }
}

void Codri::InitController::initializeRepository() {
    try {
        mController->mRepositoryInterface = new RepositoryInterface(this);

        emit repositorySuccess();
    } catch (const QException &iException) {
        mLogger->error() << "Repository interface initialization failed: " << iException.what();
        foreach (const QString& tCause, iException.causes())
            mLogger->error() << "Caused by: " << tCause;
        emit repositoryFailure();
    }
}

void Codri::InitController::initializeNetwork() {
    try {
        mController->mNetworkInterface = new NetworkInterface(this);

        emit networkSuccess();
    } catch (const QException &iException) {
        mLogger->error() << "Network interface initialization failed: " << iException.what();
        foreach (const QString& tCause, iException.causes())
            mLogger->error() << "Caused by: " << tCause;
        emit networkFailure();
    }
}


//
// State machine status
//

void Codri::InitController::_onFinished() {
    // TODO: why isn't this provided?
    mFinished = true;
}

bool Codri::InitController::isFinished() const {
    return mFinished;
}
