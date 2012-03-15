/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef CONTROLLER_H_
#define CONTROLLER_H_

// Library includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <Log4Qt/Logger>

// Local includes
#include "auxiliary/qexception.h"
#include "userinterface.h"
#include "networkinterface.h"
#include "repositoryinterface.h"
#include "platforminterface.h"
#include "state/kiosk.h"
#include "state/configuration.h"
#include "state/presentation.h"
#include "controller/initcontroller.h"

namespace Codri {
    class InitController;

    class Controller : public QObject {
    Q_OBJECT
    public:
        // Construction and destruction
        Controller(QObject *iParent) throw(QException);

        // Basic I/O
    public:
        QDateTime startup() const;

        // Application control
    public slots:
        void start();
        void stop();

        // Subsystem object getters
    public:
        NetworkInterface *networkInterface() const;
        UserInterface *userInterface() const;
        RepositoryInterface *repositoryInterface() const;
        PlatformInterface *platformInterface() const;

    private slots:
        // Initialization events
        void _onInitializationSuccess();
        void _onInitializationFailure();

    private:
        // Member data
        QDateTime mTimestampStartup;

        // Infrastructure
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;

        // Subsystem objects
        UserInterface *mUserInterface;
        NetworkInterface *mNetworkInterface;
        RepositoryInterface *mRepositoryInterface;
        PlatformInterface *mPlatformInterface;

        // Initialization controller
        InitController* mInitController;
        friend class InitController;
    };
}

#endif  // CONTROLLER_H_
