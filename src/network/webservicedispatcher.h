/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef NETWORK_WEBSERVICEDISPATCHER_H_
#define NETWORK_WEBSERVICEDISPATCHER_H_

// Library includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <Log4Qt/Logger>
#include <QxtWeb/QxtHttpSessionManager>

// Local includes
#include "network/resource.h"

namespace Codri {
    class WebserviceDispatcher : public QxtHttpSessionManager {
    Q_OBJECT
    public:
        WebserviceDispatcher(const QHostAddress &iHost, quint16 iPort);
        virtual ~WebserviceDispatcher();

        // Functionality
        void addService(QString iUri, Resource* iSubService);

    private:
        // Member data
        Resource* mRootService;

        // Subsystem objects
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;
    };
}

#endif  // NETWORK_WEBSERVICEDISPATCHER_H_
