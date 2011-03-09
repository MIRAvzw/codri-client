//
// Configuration
//

// Includes
#include "mainapplication.h"
#include <QtGui/QDesktopServices>
#include <QtCore/QDir>
#include <QtCore/QStringBuilder>
#include <QtCore/QTimer>

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

    // Initialize logging subsystem
    mLogger = new LogFacility("main", this);

    // Initialize service publishing subsystem
    mServicePublisher = new ServicePublisher("TestKiosk", this);

    // Initialize application interface subsystem
    mApplicationInterface = new ApplicationInterface("127.0.0.1", 8080, this);
}

MainApplication::~MainApplication()
{
    // Remove the singleton configuration
    mInstance = NULL;

    // Save the settings
    settings().sync();
}


//
// Application control
//

void MainApplication::start()
{
    mLogger->trace() << Q_FUNC_INFO;

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
    mLogger->trace() << Q_FUNC_INFO;
}

void MainApplication::close()
{
    mLogger->trace() << Q_FUNC_INFO;
}
