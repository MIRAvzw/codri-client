/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Local includes
#include "controller.h"
#include "mainapplication.h"
#include "qexception.h"

// Library includes
#include <QtGui/QDesktopServices>
#include <QtCore/QDir>
#include <QtCore/QStringBuilder>
#include <QtCore/QTimer>
#include <Log4Qt/TTCCLayout>
#include <Log4Qt/ConsoleAppender>


//
// Construction and destruction
//

MIRA::Controller::Controller(QObject *iParent) throw(QException) : QObject(iParent)
{
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

QDateTime MIRA::Controller::startup() const
{
    return mTimestampStartup;
}


//
// Application control
//

void MIRA::Controller::start()
{
    mLogger->debug() << "Starting application";
    mInitController->start();
}

void MIRA::Controller::stop()
{
    if (mInitController->isFinished())
    {
        mLogger->debug() << "Stopping application";
        delete mNetworkInterface;
        delete mDataManager;
        delete mUserInterface;
    }
    else
    {
        mLogger->warn() << "Error occured during initialization, not attempting clean-up";
    }
}


//
// Subsystem object getters
//

MIRA::NetworkInterface *MIRA::Controller::networkInterface() const
{
    return mNetworkInterface;
}

MIRA::UserInterface *MIRA::Controller::userInterface() const
{
    return mUserInterface;
}

MIRA::DataManager *MIRA::Controller::dataManager() const
{
    return mDataManager;
}


//
// Initialization events
//

void MIRA::Controller::_onInitializationSuccess()
{
    mLogger->info() << "Initialisation completed successfully, all functionality should be operational";

    // Initialize state signals
    connect(MainApplication::instance()->kiosk(), SIGNAL(onPowerChanged(Kiosk::Power)), this, SLOT(_onKioskPowerChanged(Kiosk::Power)));
    connect(MainApplication::instance()->configuration(), SIGNAL(onVolumeChanged(unsigned char)), this, SLOT(_onConfigurationVolumeChanged(unsigned char)));
    connect(MainApplication::instance()->presentation(), SIGNAL(onLocationChanged(const QString&)), this, SLOT(_onPresentationLocationChanged(const QString&)));
}

void MIRA::Controller::_onInitializationFailure()
{
    mLogger->fatal() << "Initialisation failed, aborting";
    MainApplication::instance()->quit();
}


//
// Subsystem events
//

void MIRA::Controller::_onPresentationError(const QString& iError)
{
    mLogger->error("Error on loaded media: " + iError);
    // TODO: revert media or smth
}


//
// State events
//

void MIRA::Controller::_onKioskPowerChanged(Kiosk::Power iPower)
{
    switch (iPower)
    {
    case Kiosk::OFF:
        stop();
        break;
    case Kiosk::ON:
        break;
    }
}

void MIRA::Controller::_onConfigurationVolumeChanged(unsigned char iVolume)
{
    // TODO: cache the value

    // TODO: actually change the volume
}

void MIRA::Controller::_onPresentationLocationChanged(const QString &iLocation)
{
    try
    {
        // Disable the current presentation
        // TODO: updating message
        userInterface()->showInit();

        // Download the new presentation
        QPair<QDir, unsigned long> tCheckout = dataManager()->downloadPresentation(iLocation);

        // Show the new presentation
        MainApplication::instance()->presentation()->setRevision(tCheckout.second);
        userInterface()->showPresentation(tCheckout.first);
    }
    catch (const QException &tException)
    {
        mLogger->error() << "Could not download the new presentation: " << tException.what();
        foreach (const QString& tCause, tException.causes())
            mLogger->error() << "Caused by: " << tCause;
        userInterface()->showError("could not download presentation");
        return;
    }
}
