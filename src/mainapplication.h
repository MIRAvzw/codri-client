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
#include "servicepublisher.h"
#include "logger.h"
#include "logfacility.h"
#include "applicationinterface.h"

namespace MIRA
{
    class MainApplication : public QApplication
    {
        Q_OBJECT
    public:
        // Construction and destruction
        explicit MainApplication(int& argc, char** argv);
        ~MainApplication();

        // System signals (Unix)
        static void handleInterruptUnix(int unused);
        static void handleTerminateUnix(int unused);

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

        // UI events
    public slots:
        void run();
        void quitGracefully();

    private:
        // Singleton object
        static MainApplication *mInstance;
        QSettings* mSettings;

        // Subsystem objects
        LogFacility *mLogger;
        ServicePublisher* mServicePublisher;
        ApplicationInterface* mApplicationInterface;

        static int sigintFd[2];
        static int sigtermFd[2];

        QSocketNotifier *snInt;
        QSocketNotifier *snTerm;
    };
}

#endif // MAINAPPLICATION_H
