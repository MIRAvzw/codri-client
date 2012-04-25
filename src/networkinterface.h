/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef NETWORKINTERFACE_H_
#define NETWORKINTERFACE_H_

// Library includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtCore/QTimer>
#include <log4qt/Logger>

// Local includes
#include "auxiliary/qexception.h"
#include "network/webservicedispatcher.h"
#include "network/serverclient.h"
#include "network/registrationcontroller.h"

namespace Codri {
    class NetworkInterface : public QObject {
    Q_OBJECT
    public:
        // Construction and destruction
        explicit NetworkInterface(QObject *iParent) throw(QException);
        void start();
        ~NetworkInterface();

    private:
        // Subsystem objects
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;
        WebserviceDispatcher *mWebserviceDispatcher;
        ServerClient *mServerClient;
        RegistrationController *mRegistrationController;
    };
}

#endif  // NETWORKINTERFACE_H_
