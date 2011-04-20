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
#include "qexception.h"
#include "qavahiservicepublisher.h"
#include "logger.h"

namespace MIRA
{
    class ServicePublisher : public QObject
    {
    Q_OBJECT
    public:
        // Construction and destruction
        explicit ServicePublisher(QString iName, QObject *parent = 0) throw(QException);
        ~ServicePublisher();

    private slots:
        void catchNotification(QAvahiServicePublisher::Notification);

    private:
        // Member objects
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;
        QAvahiServicePublisher mPublisher;

    };
}

#endif // SERVICEPUBLISHER_H
