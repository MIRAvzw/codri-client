//
// Configuration
//

// Includes
#include "mainapplication.h"
#include <QtGui/QDesktopServices>
#include <QtCore/QDir>
#include <QtCore/QStringBuilder>
#include <QtCore/QTimer>
#include "consoleappender.h"
#include "ttcclayout.h"
#include "logmanager.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

MainApplication* MainApplication::mInstance = NULL;

MainApplication::MainApplication(int & argc, char ** argv) : QApplication(argc, argv)
{
    // Singleton assertion (well, some singleton-hybrid, to be fair)
    Q_ASSERT(mInstance == NULL);
    mInstance = this;

    // Configure the application
    setOrganizationName("MIRA");
    setOrganizationDomain("mira.be");
    setApplicationName("Ad-Astra III");
    setApplicationVersion("0.1");

    // Load the settings
    mSettings = new QSettings(this);

    // Initialize subsystems
    initLogging();
    initServicePublishing();
}

MainApplication::~MainApplication()
{
    // Remove the singleton configuration
    mInstance = NULL;

    // Save the settings
    settings().sync();

    // Destroy components
    destroyServicePublishing();
    destroyLogging();
}


//
// Subsystem initialization and destruction
//

void MainApplication::initLogging()
{
    // Create objects
    Log4Qt::ConsoleAppender *tLogAppender = new Log4Qt::ConsoleAppender(this);
    Log4Qt::TTCCLayout *tLogLayout = new Log4Qt::TTCCLayout(this);

    // Configure layout
    tLogLayout->setDateFormat(Log4Qt::TTCCLayout::ISO8601);

    // Configure appender
    tLogAppender->setTarget(Log4Qt::ConsoleAppender::STDOUT_TARGET);
    tLogAppender->setLayout(tLogLayout);
    tLogAppender->activateOptions();

    // Configure root logger
    Log4Qt::LogManager::rootLogger()->addAppender(tLogAppender);

    // Register a logger for the main application
    mLogger = Log4Qt::Logger::logger(QString("main"));
}

void MainApplication::destroyLogging()
{
    // Delete main logger
    // TODO: deletion through QObject ownership chain?
    delete mLogger;

    // Remove appender from logger
    Log4Qt::LogManager::rootLogger()->removeAllAppenders();
}


void MainApplication::initServicePublishing()
{
    // Create object
    mServicePublisher = new ServicePublisher("TestKiosk", this);

}

void MainApplication::destroyServicePublishing()
{

}


//
// Application control
//

void MainApplication::start()
{
    QTimer::singleShot(0, this, SLOT(run()));
    QObject::connect(this, SIGNAL(lastWindowClosed()), this, SLOT(close()));
}


//
// Singleton objects
//

MainApplication *MainApplication::instance()
{
    return mInstance;
}

QSettings& MainApplication::settings()
{
    return *instance()->mSettings;
}


//
// UI events
//

void MainApplication::run()
{
}

void MainApplication::close()
{
}
