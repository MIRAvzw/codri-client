/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "controller.h"

// Library includes
#include <QtGui/QDesktopServices>
#include <QtCore/QDir>
#include <QtCore/QStringBuilder>
#include <QtCore/QTimer>
#include <Log4Qt/TTCCLayout>
#include <Log4Qt/ConsoleAppender>

// Local includes
#include "auxiliary/qexception.h"
#include "mainapplication.h"


//
// Construction and destruction
//

Codri::Controller::Controller(QObject *iParent) throw(QException)
    : QObject(iParent) {
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup("Controller");

    // Setup logging
    mLogger =  Log4Qt::Logger::logger(metaObject()->className());

    // Mark startup time
    mTimestampStartup = QDateTime::currentDateTime();

    // Initialize subsystems
    mInitController = new InitController(this);
    connect(mInitController, SIGNAL(success()), this, SLOT(_onInitializationSuccess()));
    connect(mInitController, SIGNAL(failure()), this, SLOT(_onInitializationFailure()));
}


//
// Basic I/O
//

QDateTime Codri::Controller::startup() const {
    return mTimestampStartup;
}


//
// Application control
//

void Codri::Controller::start() {
    mLogger->debug() << "Starting application";
    mInitController->start();
}

void Codri::Controller::stop() {
    if (mInitController->isFinished()) {
        mLogger->debug() << "Stopping application";
        delete mNetworkInterface;
        delete mRepositoryInterface;
        delete mUserInterface;
    } else {
        mLogger->warn() << "Error occured during initialization, not attempting clean-up";
    }
}


//
// Subsystem object getters
//

Codri::NetworkInterface *Codri::Controller::networkInterface() const {
    return mNetworkInterface;
}

Codri::UserInterface *Codri::Controller::userInterface() const {
    return mUserInterface;
}

Codri::RepositoryInterface *Codri::Controller::repositoryInterface() const {
    return mRepositoryInterface;
}


//
// Initialization events
//

void Codri::Controller::_onInitializationSuccess() {
    mLogger->info() << "Initialisation completed successfully, all functionality should be operational";

    // STATE EVENTS //

    // Kiosk
    connect(MainApplication::instance()->kiosk(), SIGNAL(onStatusChanged(Kiosk::Status)), mPlatformInterface, SLOT(setStatus(Kiosk::Status)));

    // Configuration
    connect(MainApplication::instance()->configuration(), SIGNAL(onVolumeChanged(uint8_t)), mPlatformInterface, SLOT(setVolume(uint8_t)));

    // Presentation
    connect(MainApplication::instance()->presentation(), SIGNAL(onLocationChanged(const QString&)), mRepositoryInterface, SLOT(check(const QString&)));


    // SUBSYSTEM EVENTS //

    // Repository interface
    connect(mRepositoryInterface, SIGNAL(changing()), mUserInterface, SLOT(showInit()));
    connect(mRepositoryInterface, SIGNAL(ready(QDir)), mUserInterface, SLOT(showPresentation(QDir)));
    connect(mRepositoryInterface, SIGNAL(failure(QException)), mUserInterface, SLOT(showError(QException)));

    // User interface
    // TODO: presentationError
}

void Codri::Controller::_onInitializationFailure() {
    mLogger->fatal() << "Initialisation failed, aborting";
    MainApplication::instance()->quit();
}
