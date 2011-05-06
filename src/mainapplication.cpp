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

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

// Initialize static members
MainApplication* MainApplication::mInstance = NULL;
int MainApplication::sigintFd[2];
int MainApplication::sigtermFd[2];

MainApplication::MainApplication(int& argc, char** argv) throw(QException) : QApplication(argc, argv)
{
    // Singleton assertion (well, some singleton-hybrid, to be fair)
    Q_ASSERT(mInstance == NULL);
    mInstance = this;

    // Configure the application
    setOrganizationName("MIRA");
    setOrganizationDomain("mira.be");
    setApplicationName("Ad-Astra III");
    setApplicationVersion("0.1");

    // Setup signal handling
    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sigintFd))
        qFatal("Couldn't create HUP socketpair");
    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sigtermFd))
        qFatal("Couldn't create TERM socketpair");
    snInt = new QSocketNotifier(sigintFd[1], QSocketNotifier::Read, this);
    connect(snInt, SIGNAL(activated(int)), this, SLOT(handleInterrupt()));
    snTerm = new QSocketNotifier(sigtermFd[1], QSocketNotifier::Read, this);
    connect(snTerm, SIGNAL(activated(int)), this, SLOT(handleTerminate()));

    // Load the settings
    mSettings = new QSettings(this);

    // Initialize logging subsystem
    mLogger = Log4Qt::Logger::logger("main");
    if (mLogger->appenders().size() == 0)
    {
        // Create a layout
        Log4Qt::TTCCLayout* tLayout = new Log4Qt::TTCCLayout();
        tLayout->activateOptions();

        // Create an appender
        Log4Qt::ConsoleAppender* tAppender = new Log4Qt::ConsoleAppender(tLayout, Log4Qt::ConsoleAppender::STDOUT_TARGET);
        tAppender->activateOptions();

        // Set appender on root logger
        Log4Qt::Logger::rootLogger()->addAppender(tAppender);
        Log4Qt::Logger::rootLogger()->setLevel(Log4Qt::Level::ALL_INT);
    }
    mLogger->info() << "Initializing";

    // Mark startup time
    mTimestampStartup = QDateTime::currentDateTime();

    // Initialize subsystems
    mLogger->debug() << "Loading subsystems";
    try
    {
        mLogger->debug() << "Initializing user interface";
        mUserInterface = new UserInterface();
        mUserInterface->init();
        mUserInterface->show();

        mLogger->debug() << "Initializing network interface";
        mNetworkInterface = new NetworkInterface(this);
        mNetworkInterface->init();
    }
    catch (const QException& iException)
    {
        mLogger->fatal() << "Failed to initialize: " << iException.what();
        throw QException("could not load all subsystems");
    }
}

MainApplication::~MainApplication()
{
    // Remove the singleton configuration
    mInstance = NULL;
}


//
// Basic I/O
//

QUuid MainApplication::uuid() const
{
    return QUuid(); // TODO
}

QDateTime MainApplication::startup() const
{
    return mTimestampStartup;
}


//
// Application control
//

void MainApplication::start()
{
    mLogger->trace() << Q_FUNC_INFO;

    mLogger->info() << "Initialisation completed successfully, all functionality should be operational";
    QTimer::singleShot(0, this, SLOT(run()));
    QObject::connect(this, SIGNAL(lastWindowClosed()), this, SLOT(quitGracefully()));
}

void MainApplication::fatal()
{
    mLogger->trace() << Q_FUNC_INFO;

    mLogger->fatal() << "Fatal error occured, halting application";
    quitGracefully();
}

//
// Singleton objects getters
//

MainApplication *MainApplication::instance()
{
    return mInstance;
}


//
// Subsystem object getters
//

NetworkInterface* MainApplication::networkInterface() const
{
    return mNetworkInterface;
}

UserInterface* MainApplication::userInterface() const
{
    return mUserInterface;
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
