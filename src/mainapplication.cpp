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
MainApplication *MainApplication::mInstance = NULL;
int MainApplication::sigintFd[2];
int MainApplication::sigtermFd[2];

MainApplication::MainApplication(int iArgumentCount, char **iArgumentValues) throw(QException) : QApplication(iArgumentCount, iArgumentValues)
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

    // Start the application controller
    mController = new Controller(this);
    connect(this, SIGNAL(aboutToQuit()), mController, SLOT(stop()));
    QTimer::singleShot(0, mController, SLOT(start()));
}

MainApplication::~MainApplication()
{
    // Remove the singleton configuration
    mInstance = NULL;
}


//
// Subsystem object getters
//

Controller *MainApplication::controller() const
{
    return mController;
}


//
// Singleton objects getters
//

MainApplication *MainApplication::instance()
{
    return mInstance;
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
    mController->stop();

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
    mController->stop();

    snInt->setEnabled(true);
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
