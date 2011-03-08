#include "servicepublisher.h"

#include <QtCore/QtDebug>

ServicePublisher::ServicePublisher(QObject *parent) :
    QObject(parent), mPublisher(this)
{
    qDebug() << "+ " << Q_FUNC_INFO;
}

void ServicePublisher::run() {
    qDebug() << "~ " << Q_FUNC_INFO;

    connect(&mPublisher, SIGNAL(changeNotification(QAvahiServicePublisher::Notification)), this, SLOT(catchNotification(QAvahiServicePublisher::Notification)));
    mPublisher.publish("Nummer1", "_mirakiosk._tcp", 555, "Kiosk in the MIRA Ad-Astra III application");
    
    //emit done();
}


void ServicePublisher::catchNotification(QAvahiServicePublisher::Notification iNotification) {
    qDebug() << "~ " << Q_FUNC_INFO;


    switch (iNotification) {
    case QAvahiServicePublisher::Error:
        qWarning() << "Error:" << mPublisher.errorString();
        break;
    case QAvahiServicePublisher::ServicesRegistering:
        qDebug() << "Registering services";
        break;
    case QAvahiServicePublisher::ServicesRegistered:
        qDebug() << "Registered services";
        break;
    case QAvahiServicePublisher::ServiceNameCollision:
        qWarning() << "Name collision";
        break;
    case QAvahiServicePublisher::ServicesUncommited:
        qDebug() << "Registering services";
        break;
    case QAvahiServicePublisher::ServicesCommited:
        qDebug() << "Services commited";
        break;
    case QAvahiServicePublisher::ClientConnecting:
        qDebug() << "Client connecting";
        break;
    case QAvahiServicePublisher::ServerRunning:
        qDebug() << "Server running";
        break;
    case QAvahiServicePublisher::ServerRegistering:
        qDebug() << "Server registering";
        break;
    case QAvahiServicePublisher::ServerNameCollision:
        qWarning() << "Server name collision";
        break;
    default:
        qWarning() << "Unknown notification";
    }
}
