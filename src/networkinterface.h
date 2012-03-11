/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
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
#include <Log4Qt/Logger>

// Local includes
#include "qexception.h"
#include "networkinterface/webservicedispatcher.h"
#include "networkinterface/serverclient.h"
#include "networkinterface/registrationcontroller.h"

namespace Codri
{
    class NetworkInterface : public QObject
    {
    Q_OBJECT
    public:
        // Construction and destruction
        NetworkInterface(QObject *iParent) throw(QException);
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

#endif  // USERINTERFACE_H_
