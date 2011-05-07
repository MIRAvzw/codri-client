#include <QtCore/QCoreApplication>
#include "mainapplication.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MainApplication* tApplication = new MainApplication();

    return a.exec();
}
