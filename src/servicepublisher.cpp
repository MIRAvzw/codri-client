//
// Configuration
//

// Includes
#include "servicepublisher.h"
#include <QtCore/QtDebug>

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

ServicePublisher::ServicePublisher(QString iName, QObject *parent) : QObject(parent), mPublisher(this)
{
    // Load settings
    mSettings = new QSettings(this);

    // Setup logging
    mLogger =  Log4Qt::Logger::logger("ServicePublisher");
    mLogger->trace() << Q_FUNC_INFO;

    // Connect Avahi signals
    connect(&mPublisher, SIGNAL(changeNotification(QAvahiServicePublisher::Notification)), this, SLOT(catchNotification(QAvahiServicePublisher::Notification)));

    // Publish the service
    mPublisher.publish(
                iName,
                mSettings->value("ServicePublisher/type", "_mirakiosk._tcp").toString(),
                mSettings->value("ApplicationInterface/listen_port", 8080).toInt(),
                mSettings->value("ServicePublisher/description", "").toString());
}

ServicePublisher::~ServicePublisher()
{
    mLogger->trace() << Q_FUNC_INFO;
}


void ServicePublisher::catchNotification(QAvahiServicePublisher::Notification iNotification)
{
    mLogger->trace() << Q_FUNC_INFO;

    switch (iNotification) {
    case QAvahiServicePublisher::Error:
        mLogger->error() << mPublisher.errorString();
        break;
    case QAvahiServicePublisher::ServicesRegistering:
        mLogger->debug() << "Registering services";
        break;
    case QAvahiServicePublisher::ServicesRegistered:
        mLogger->debug() << "Registered services";
        break;
    case QAvahiServicePublisher::ServiceNameCollision:
        mLogger->warn() << "Name collision";
        break;
    case QAvahiServicePublisher::ServicesUncommited:
        mLogger->debug() << "Registering services";
        break;
    case QAvahiServicePublisher::ServicesCommited:
        mLogger->debug() << "Services commited";
        break;
    case QAvahiServicePublisher::ClientConnecting:
        mLogger->debug() << "Client connecting";
        break;
    case QAvahiServicePublisher::ServerRunning:
        mLogger->debug() << "Server running";
        break;
    case QAvahiServicePublisher::ServerRegistering:
        mLogger->debug() << "Server registering";
        break;
    case QAvahiServicePublisher::ServerNameCollision:
        mLogger->warn() << "Server name collision";
        break;
    default:
        mLogger->warn() << "Unknown notification";
    }
}
