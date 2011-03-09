//
// Configuration
//

// Include guard
#ifndef SERVICEPUBLISHER_H
#define SERVICEPUBLISHER_H

// System includes
#include <QtCore/QObject>

// Local includes
#include "qavahiservicepublisher.h"

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
        QAvahiServicePublisher mPublisher;

    };
}

#endif // SERVICEPUBLISHER_H
