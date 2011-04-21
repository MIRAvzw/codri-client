//
// Configuration
//

// Include guard
#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

// System includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtGui/QApplication>
#include <QtCore/QSocketNotifier>

// Local includes
#include "qexception.h"
#include "logger.h"
#include "servicepublisher.h"
#include "userinterface.h"
#include "applicationinterface.h"

// Platform-specific inclused
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

        // Subsystem objects
        QSettings* mSettings;
        Log4Qt::Logger *mLogger;
        UserInterface* mUserInterface;
        ServicePublisher* mServicePublisher;
        ApplicationInterface* mApplicationInterface;

        static int sigintFd[2];
        static int sigtermFd[2];

        QSocketNotifier *snInt;
        QSocketNotifier *snTerm;

        // Auxiliary
        QString macAddress();
    };
}

#endif // MAINAPPLICATION_H
