#ifndef SERVICEPUBLISHER_H
#define SERVICEPUBLISHER_H

#include <QtCore/QObject>

#include "qavahiservicepublisher.h"

class ServicePublisher : public QObject
{
    Q_OBJECT
public:
    explicit ServicePublisher(QObject *parent = 0);

signals:
    void done();

public slots:
    void run();

private slots:
                void catchNotification(QAvahiServicePublisher::Notification);
private:
                QAvahiServicePublisher mPublisher;

};

#endif // SERVICEPUBLISHER_H
