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

    private:
        // Subsystem initialization and destruction
        void initLogging();
        void destroyLogging();
        void initServicePublishing();
        void destroyServicePublishing();
        void initApplicationInterface();
        void destroyApplicationInterface();

        // Singleton object getters
    public:
        static MainApplication *instance();
        static QSettings &settings();

        // Application control
    public:
        void start();

        // UI events
    public slots:
        void run();
        void close();

    private:
        // Singleton object
        static MainApplication *mInstance;
        QSettings* mSettings;

        // Subsystem objects
        LogFacility *mLogger;
        ServicePublisher* mServicePublisher;
        ApplicationInterface* mApplicationInterface;
    };
}

#endif // MAINAPPLICATION_H
