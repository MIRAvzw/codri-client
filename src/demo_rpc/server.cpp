#include "server.h"
#include "../../lib/qtxmlrpc/server/src/xmlrpcserver.h"

#include <QHostAddress>

Server::Server(const QString &address, quint16 port, QObject *parent) : QObject( parent )
{
    qDebug() << "+ " << Q_FUNC_INFO;

    XmlRpcServer *srv = new XmlRpcServer(0, "Dev_server.crt", "Dev_server.pem");
    if (srv->listen(QHostAddress(address), port))
    {
        srv->registerSlot( this, SLOT( testFunc(QVariant) ), "/RPC/");
    }
}


QVariant Server::testFunc(const QVariant &param)
{
    qDebug() << "+ " << Q_FUNC_INFO;

    return param;
}
