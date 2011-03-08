#include <QtCore/QCoreApplication>
#include <QtCore/QTimer>

#include "sampleapplication.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SampleApplication* tApplication = new SampleApplication();
    QObject::connect(tApplication, SIGNAL(done()), &a, SLOT(quit()));
    QTimer::singleShot(0, tApplication, SLOT(run()));

    return a.exec();
}
