//
// Configuration
//

// Include guard
#ifndef SERVICEPUBLISHER_H
#define SERVICEPUBLISHER_H

// System includes
#include <QtCore/QObject>
#include <QtCore/QSettings>

// Local includes
#include "qavahiservicepublisher.h"
#include "logfacility.h"

namespace MIRA
{
    class ServicePublisher : public QObject
    {
    Q_OBJECT
    public:
        // Construction and destruction
        explicit ServicePublisher(QString iName, QObject *parent = 0);
        ~ServicePublisher();

    private slots:
        void catchNotification(QAvahiServicePublisher::Notification);

    private:
        // Member objects
        QSettings *mSettings;
        QAvahiServicePublisher mPublisher;
        LogFacility *mLogger;

    };
}

#endif // SERVICEPUBLISHER_H
