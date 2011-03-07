#ifndef SERVICEDISCOVERER_H
#define SERVICEDISCOVERER_H

#include <QtCore/QObject>

#include "qavahiservicebrowsermodel.h"
#include "qavahiservicepublisher.h"

class ServiceDiscoverer : public QObject
{
    Q_OBJECT
public:
    explicit ServiceDiscoverer(QObject *parent = 0);

signals:
    void done();

public slots:
    void run();

private slots:
		void catchPublisherNotification(QAvahiServicePublisher::Notification);
		void catchBrowserNotification(QAvahiServiceBrowserModel::Notification);

};

#endif // SERVICEDISCOVERER_H
