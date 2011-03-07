
#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtGui/QApplication>
#include <QtCore/QTimer>
#include <QtCore/QTextStream>

#include "servicediscoverer.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    ServiceDiscoverer* tServiceDiscoverer = new ServiceDiscoverer();
    QObject::connect(tServiceDiscoverer, SIGNAL(done()), &app, SLOT(quit()));
    QTimer::singleShot(0, tServiceDiscoverer, SLOT(run()));
    return app.exec();
}
