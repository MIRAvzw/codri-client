//
// Configuration
//

// Include guard
#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

// Library includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtGui/QApplication>
#include <QtCore/QSocketNotifier>
#include <QtCore/QDateTime>
#include <Log4Qt/Logger>

// Local includes
#include "qexception.h"
#include "userinterface.h"
#include "networkinterface.h"

// Platform-specific system includes
#if defined(Q_OS_LINUX)
#include <sys/ioctl.h>
#include <net/if.h>
#elif defined(Q_OS_WIN32)
#include <winsock2.h>
#include <iphlpapi.h>
#endif

namespace MIRA
{
    class MainApplication : public QApplication
    {
        Q_OBJECT
    public:
        // Construction and destruction
        explicit MainApplication(int& argc, char** argv) throw(QException);
        ~MainApplication();

        // System signals (Unix)
        static void handleInterruptUnix(int unused);
        static void handleTerminateUnix(int unused);

        // Basic I/O
    public:
        QString id() const;
        QDateTime startup() const;

    public slots:
        // System signals
        void handleInterrupt();
        void handleTerminate();

        // Singleton object getters
    public:
        static MainApplication *instance();

        // Application control
    public:
        void start();
        void fatal();

        // UI events
    public slots:
        void run();
        void quitGracefully();

    private:
        // Singleton object
        static MainApplication *mInstance;

        // Member data
        QString mId;
        QDateTime mTimestampStartup;

        // Subsystem objects
        QSettings* mSettings;
        Log4Qt::Logger *mLogger;
        UserInterface* mUserInterface;
        NetworkInterface* mNetworkInterface;

        static int sigintFd[2];
        static int sigtermFd[2];

        QSocketNotifier *snInt;
        QSocketNotifier *snTerm;

        // Auxiliary
        QString macAddress();
    };
}

#endif // MAINAPPLICATION_H
