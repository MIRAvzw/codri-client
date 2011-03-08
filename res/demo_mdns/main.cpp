
#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtGui/QApplication>
#include <QtCore/QTimer>
#include <QtCore/QTextStream>

#include "servicepublisher.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    ServicePublisher* tServicePublisher = new ServicePublisher();
    QObject::connect(tServicePublisher, SIGNAL(done()), &app, SLOT(quit()));
    QTimer::singleShot(0, tServicePublisher, SLOT(run()));
    return app.exec();
}
