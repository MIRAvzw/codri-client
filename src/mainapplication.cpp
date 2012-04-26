/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "mainapplication.h"

// System includes
#include <sys/socket.h>
#include <csignal>

// Library includes
#include <QtCore/QMetaType>
#include <QtGui/QDesktopServices>
#include <QtCore/QDir>
#include <QtCore/QStringBuilder>
#include <QtCore/QTimer>
#include <log4qt/TTCCLayout>
#include <log4qt/ConsoleAppender>
#include <log4qt/FileAppender>


//
// Construction and destruction
//

// Initialize static members
Codri::MainApplication *Codri::MainApplication::mInstance = NULL;

Codri::MainApplication::MainApplication(int &iArgumentCount, char **iArgumentValues) throw(QException)
    : QApplication(iArgumentCount, iArgumentValues) {
    // Singleton assertion (well, some singleton-hybrid, to be fair)
    Q_ASSERT(mInstance == NULL);
    mInstance = this;

    // Register custom types
    qRegisterMetaType<QException>("QException");

    // Configure the application
    setOrganizationName("Codri");
    setOrganizationDomain("codri.be");
    setApplicationName("Codri");
    setApplicationVersion("0.1");

    // Load the settings
    mSettings = new QSettings(this);

    // Initialize logging subsystem
    mLogger = Log4Qt::Logger::logger(metaObject()->className());
    if (mLogger->appenders().size() == 0) {
        // Create a layout
        Log4Qt::TTCCLayout *tLayout = new Log4Qt::TTCCLayout();
        tLayout->setDateFormat(Log4Qt::TTCCLayout::ISO8601);
        tLayout->activateOptions();

        // Create a console appender
        Log4Qt::ConsoleAppender *tConsoleAppender = new Log4Qt::ConsoleAppender(tLayout, Log4Qt::ConsoleAppender::STDOUT_TARGET);
        tConsoleAppender->setThreshold(Log4Qt::Level::INFO_INT);
        tConsoleAppender->activateOptions();

        // Create a file appender
        Log4Qt::FileAppender *tFileAppender = new Log4Qt::FileAppender(tLayout, "/var/log/codri/client.log");
        tFileAppender->setThreshold(Log4Qt::Level::DEBUG_INT);
        tFileAppender->activateOptions();

        // Set appender on root logger
        Log4Qt::Logger::rootLogger()->setLevel(Log4Qt::Level::ALL_INT);
        Log4Qt::Logger::rootLogger()->addAppender(tConsoleAppender);
        Log4Qt::Logger::rootLogger()->addAppender(tFileAppender);
    }
    qInstallMsgHandler(doMessage);
    mLogger->info() << "Initializing";

    // Initialize state objects
    mKiosk = new Kiosk(this);
    mConfiguration = new Configuration(this);
    mPresentation = new Presentation(this);

    // Kiosk details
#ifdef DEVEL
    mKiosk->setVendor("N/A");
    mKiosk->setModel("Development system");
#else
    mKiosk->setVendor("Genesi");
    mKiosk->setModel("EfikaMX");
#endif

    // Start the application controller
    mController = new Controller(this);
    connect(this, SIGNAL(aboutToQuit()), mController, SLOT(stop()));
    QTimer::singleShot(0, mController, SLOT(start()));
}

Codri::MainApplication::~MainApplication() {
    // Remove the singleton configuration
    mInstance = NULL;
}


//
// QApplication interface
//

bool Codri::MainApplication::notify(QObject *iReceiver, QEvent *iEvent) {
    try {
        return QApplication::notify(iReceiver, iEvent);
    } catch(const QException &iException) {
        mLogger->fatal() << "Exception thrown: " << iException.what();
        foreach (const QString& tCause, iException.causes())
            mLogger->fatal() << "Caused by: " << tCause;
        exit(1);
    }
    return false;
}


//
// State getters
//

Codri::Kiosk *Codri::MainApplication::kiosk() const {
    return mKiosk;
}

Codri::Configuration *Codri::MainApplication::configuration() const {
    return mConfiguration;
}

Codri::Presentation *Codri::MainApplication::presentation() const {
    return mPresentation;
}


//
// Subsystem getters
//

Codri::Controller *Codri::MainApplication::controller() const {
    return mController;
}


//
// Singleton objects getters
//

Codri::MainApplication *Codri::MainApplication::instance() {
    return mInstance;
}


//
// External
//

void Codri::doMessage(QtMsgType iMessageType, const char *iMessage) {
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
