#include <QCoreApplication>
#include <QDebug>

#include "server.h"

int main(int argc, char **argv)
{
    // Initialise the application
    QCoreApplication tApplication( argc, argv );

    // Initialise the server
    QString address = "127.0.0.1";
    quint16 port = 8080;
    Server tServer(address, port);

    qDebug() << "- " << "Entering main loop";
    return tApplication.exec();
}

