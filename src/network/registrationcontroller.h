/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef NETWORK_REGISTRATIONCONTROLLER_H_
#define NETWORK_REGISTRATIONCONTROLLER_H_

// Library includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtCore/QStateMachine>
#include <QtCore/QState>
#include <QtCore/QFinalState>
#include <Log4Qt/Logger>

// Local includes
#include "network/serverclient.h"

namespace Codri {
    class RegistrationController : public QStateMachine {
    Q_OBJECT
    public:
        // Construction and destruction
        RegistrationController(ServerClient *iServerClient, QObject *iParent);

        // Construction helpers
    private:
        void initFSM();

    private:
        // Member data
        ServerClient* mServerClient;

        // Subsystem objects
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;
    };
}

#endif  // NETWORK_REGISTRATIONCONTROLLER_H_
