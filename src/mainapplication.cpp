//
// Configuration
//

// Includes
#include "mainapplication.h"
#include <QtGui/QDesktopServices>
#include <QtCore/QDir>
#include <QtCore/QStringBuilder>
#include <QtCore/QTimer>
#include <sys/socket.h>
#include <csignal>

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

// Initialize static members
MainApplication* MainApplication::mInstance = NULL;
int MainApplication::sigintFd[2];
int MainApplication::sigtermFd[2];

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
    mLogger->debug() << "Initializing service publisher";
    mServicePublisher = new ServicePublisher("TestKiosk", this);

    // Initialize application interface subsystem
    mLogger->debug() << "Initializing application interface";
    mApplicationInterface = new ApplicationInterface("127.0.0.1", 8080, this);

    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sigintFd))
        qFatal("Couldn't create HUP socketpair");

    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sigtermFd))
        qFatal("Couldn't create TERM socketpair");

    snInt = new QSocketNotifier(sigintFd[1], QSocketNotifier::Read, this);
    connect(snInt, SIGNAL(activated(int)), this, SLOT(handleInterrupt()));
    snTerm = new QSocketNotifier(sigtermFd[1], QSocketNotifier::Read, this);
    connect(snTerm, SIGNAL(activated(int)), this, SLOT(handleTerminate()));
}

MainApplication::~MainApplication()
{
    // Remove the singleton configuration
    mInstance = NULL;

    // Save the settings
    mLogger->debug() << "Synchronizing settings";
    settings().sync();
}


//
// Application control
//

void MainApplication::start()
{
    mLogger->trace() << Q_FUNC_INFO;

    mLogger->debug() << "Scheduling main loop";
    QTimer::singleShot(0, this, SLOT(run()));
    QObject::connect(this, SIGNAL(lastWindowClosed()), this, SLOT(quitGracefully()));
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

void MainApplication::quitGracefully()
{
    mLogger->trace() << Q_FUNC_INFO;
    mLogger->debug() << "Closing down";

    // Do some stuff here

    // Actually quit
    quit();
}


//
// System signals (Unix)
//

void MainApplication::handleInterruptUnix(int)
{
    // Write to the SIGINT-socket
    char a = '1';
    ::write(sigintFd[0], &a, sizeof(a));

}

void MainApplication::handleTerminateUnix(int)
{
    // Write to the SIGTERM-socket
    char a = '2';
    ::write(sigtermFd[0], &a, sizeof(a));
}

//
// System signals
//

void MainApplication::handleTerminate()
{
    mLogger->trace() << Q_FUNC_INFO;

    // Read the socket and temporarily disable the signal
    snTerm->setEnabled(false);
    char tmp;
    ::read(sigtermFd[1], &tmp, sizeof(tmp));

    // Quit the application
    quitGracefully();

    snTerm->setEnabled(true);
}

void MainApplication::handleInterrupt()
{
    mLogger->trace() << Q_FUNC_INFO;

    // Read the socket and temporarily disable the signal
    snInt->setEnabled(false);
    char tmp;
    ::read(sigintFd[1], &tmp, sizeof(tmp));

    // Quit the application
    quitGracefully();

    snInt->setEnabled(true);
}
