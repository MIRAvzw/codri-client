#include "servicediscoverer.h"

ServiceDiscoverer::ServiceDiscoverer(QObject *parent) :
    QObject(parent)
{
    qDebug() << "+ " << Q_FUNC_INFO;
}

void ServiceDiscoverer::run() {
    qDebug() << "~ " << Q_FUNC_INFO;
    
    QAvahiServicePublisher *publisher = new QAvahiServicePublisher(this);
    connect(publisher, SIGNAL(changeNotification(QAvahiServicePublisher::Notification)), this, SLOT(catchPublisherNotification(QAvahiServicePublisher::Notification)));
    publisher->publish("Nummer1", "_mirakiosk._tcp", 555, "Kiosk in the MIRA Ad-Astra III application");
    
    QAvahiServiceBrowserModel *model = new QAvahiServiceBrowserModel(this);
    connect(model, SIGNAL(changeNotification(QAvahiServiceBrowserModel::Notification)), this, SLOT(catchBrowserNotification(QAvahiServiceBrowserModel::Notification)));
    model->setAutoResolve(true);
    model->browse("_mirakiosk._tcp", QAvahiServiceBrowserModel::HideIPv6 | QAvahiServiceBrowserModel::HideLocal);
    
    //emit done();
}


void ServiceDiscoverer::catchPublisherNotification(QAvahiServicePublisher::Notification iNotification) {
    qDebug() << "~ " << Q_FUNC_INFO;
    
    qDebug() << iNotification;

}

void ServiceDiscoverer::catchBrowserNotification(QAvahiServiceBrowserModel::Notification iNotification) {
    qDebug() << "~ " << Q_FUNC_INFO;
    
    qDebug() << iNotification;

}
