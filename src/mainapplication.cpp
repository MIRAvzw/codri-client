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

    // Load the settings
    mSettings = new QSettings(this);

    // Initialize logging subsystem
    mLogger = Log4Qt::Logger::logger("main");

    // Generate a unique ID
    QString tMacAddress = macAddress();
    mId = tMacAddress.replace(QString(":"), QString(""));
    mLogger->info() << "Unique kiosk name: " << mId;

    // Mark startup time
    mTimestampStartup = QDateTime::currentDateTime();

    // Initialize subsystems
    mLogger->debug() << "Loading subsystems";
    try
    {
        mLogger->debug() << "Initializing user interface";
        mUserInterface = new UserInterface();
        mUserInterface->show();

        mLogger->debug() << "Initializing service publisher";
        mServicePublisher = new ServicePublisher(mId, this);

        mLogger->debug() << "Initializing application interface";
        mApplicationInterface = new ApplicationInterface(this);
    }
    catch (const QException& iException)
    {
        mLogger->fatal() << "Failed to initialize: " << iException.what();
        throw QException("could not load all subsystems");
    }

    // Setup signal handling
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
}


//
// Basic I/O
//

QString MainApplication::id() const
{
    return mId;
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

    mLogger->debug() << "Scheduling main loop";
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
// Singleton objects
//

MainApplication *MainApplication::instance()
{
    return mInstance;
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


//
// Auxiliary
//

QString MainApplication::macAddress()
{
    QString oMacAddress;

    //
    #if defined(Q_OS_WIN32)
    //

    PIP_ADAPTER_INFO pinfo = NULL;

    unsigned long len = 0;
    unsigned long nError;

    if (pinfo != NULL)
        delete (pinfo);

    nError = GetAdaptersInfo(pinfo,&len);
    if (nError != 0)
    {
        pinfo= (PIP_ADAPTER_INFO)malloc(len);
        nError = GetAdaptersInfo(pinfo,&len);
    }

    if(nError == 0)
        oMacAddress.sprintf("%02X:%02X:%02X:%02X:%02X:%02X",
                           pinfo->Address[0],
                           pinfo->Address[1],
                           pinfo->Address[2],
                           pinfo->Address[3],
                           pinfo->Address[4],
                           pinfo->Address[5]
        );


    //
    #elif defined(Q_OS_LINUX)
    //

    // Create an interface request struct
    struct ifreq ifr;
    bzero(&ifr, sizeof(ifr));
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);

    // Open a socket and perform the IOCTL
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    ioctl(fd, SIOCGIFHWADDR, &ifr);
    close(fd);

    // Format the result
    oMacAddress.sprintf("%02X:%02X:%02X:%02X:%02X:%02X",
            (unsigned char)ifr.ifr_hwaddr.sa_data[0],
            (unsigned char)ifr.ifr_hwaddr.sa_data[1],
            (unsigned char)ifr.ifr_hwaddr.sa_data[2],
            (unsigned char)ifr.ifr_hwaddr.sa_data[3],
            (unsigned char)ifr.ifr_hwaddr.sa_data[4],
            (unsigned char)ifr.ifr_hwaddr.sa_data[5]);


    //
    #else
    //

    #error Unsupported OS, please implement MainApplication::macAddress()
    #endif

    return oMacAddress;
}
