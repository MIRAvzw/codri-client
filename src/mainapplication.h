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

        // Singleton objects
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

        // Member objects
        QSettings* mSettings;
        ServicePublisher* mServicePublisher;
    };
}

#endif // MAINAPPLICATION_H
