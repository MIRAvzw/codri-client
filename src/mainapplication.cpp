/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Local includes
#include "mainapplication.h"

// Library includes
#include <QtGui/QDesktopServices>
#include <QtCore/QDir>
#include <QtCore/QStringBuilder>
#include <QtCore/QTimer>
#include <Log4Qt/TTCCLayout>
#include <Log4Qt/ConsoleAppender>

// System includes
#include <csignal>
#include <sys/socket.h>


//
// Construction and destruction
//

// Initialize static members
MIRA::MainApplication *MIRA::MainApplication::mInstance = NULL;

MIRA::MainApplication::MainApplication(int &iArgumentCount, char **iArgumentValues) throw(QException) : QApplication(iArgumentCount, iArgumentValues)
{
    // Singleton assertion (well, some singleton-hybrid, to be fair)
    Q_ASSERT(mInstance == NULL);
    mInstance = this;

    // Configure the application
    setOrganizationName("MIRA");
    setOrganizationDomain("mira.be");
    setApplicationName("Codri");
    setApplicationVersion("0.1");

    // Load the settings
    mSettings = new QSettings(this);

    // Initialize logging subsystem
    mLogger = Log4Qt::Logger::logger(metaObject()->className());
    if (mLogger->appenders().size() == 0)
    {
        // Create a layout
        Log4Qt::TTCCLayout *tLayout = new Log4Qt::TTCCLayout();
        tLayout->activateOptions();

        // Create an appender
        Log4Qt::ConsoleAppender *tAppender = new Log4Qt::ConsoleAppender(tLayout, Log4Qt::ConsoleAppender::STDOUT_TARGET);
        tAppender->activateOptions();

        // Set appender on root logger
        Log4Qt::Logger::rootLogger()->addAppender(tAppender);
        Log4Qt::Logger::rootLogger()->setLevel(Log4Qt::Level::ALL_INT);
    }
    qInstallMsgHandler(doMessage);
    mLogger->info() << "Initializing";

    // Initialize state objects
    mKiosk = new Kiosk(this);
    mConfiguration = new Configuration(this);
    mPresentation = new Presentation(this);

    // Start the application controller
    mController = new Controller(this);
    connect(this, SIGNAL(aboutToQuit()), mController, SLOT(stop()));
    QTimer::singleShot(0, mController, SLOT(start()));
}

MIRA::MainApplication::~MainApplication()
{
    // Remove the singleton configuration
    mInstance = NULL;
}


//
// State getters
//

MIRA::Kiosk *MIRA::MainApplication::kiosk() const
{
    return mKiosk;
}

MIRA::Configuration *MIRA::MainApplication::configuration() const
{
    return mConfiguration;
}

MIRA::Presentation *MIRA::MainApplication::presentation() const
{
    return mPresentation;
}


//
// Subsystem getters
//

MIRA::Controller *MIRA::MainApplication::controller() const
{
    return mController;
}


//
// Singleton objects getters
//

MIRA::MainApplication *MIRA::MainApplication::instance()
{
    return mInstance;
}


//
// External
//

void MIRA::doMessage(QtMsgType iMessageType, const char *iMessage)
{
    MainApplication *mApplication = MainApplication::instance();
    switch (iMessageType) {
        case QtDebugMsg:
            mApplication->mLogger->debug() << iMessage;
            break;
        case QtWarningMsg:
            mApplication->mLogger->warn() << iMessage;
            break;
        case QtCriticalMsg:
            mApplication->mLogger->error() << iMessage;
            break;
        case QtFatalMsg:
            mApplication->mLogger->fatal() << iMessage;
            mApplication->controller()->stop();
    }
}
