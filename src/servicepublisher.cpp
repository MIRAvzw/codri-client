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
    mLogger =  new LogFacility("ServicePublisher", this);
    mLogger->trace() << Q_FUNC_INFO;

    connect(&mPublisher, SIGNAL(changeNotification(QAvahiServicePublisher::Notification)), this, SLOT(catchNotification(QAvahiServicePublisher::Notification)));
    mPublisher.publish(iName, "_mirakiosk._tcp", 555, "Kiosk in the MIRA Ad-Astra III application");
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
