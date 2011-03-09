//
// Configuration
//

// Includes
#include "applicationinterface.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

ApplicationInterface::ApplicationInterface(const QString &address, quint16 port, QObject *parent) : QObject(parent)
{
    // Setup logging
    mLogger =  new LogFacility("ServicePublisher", this);
    mLogger->trace() << Q_FUNC_INFO;

    // Create the XMLRPC-server
    //mServer = new XmlRpcServer(0, "Dev_server.crt", "Dev_server.pem");
    mServer = new XmlRpcServer(this);
    if (mServer->listen(QHostAddress(address), port))
    {
        mServer->registerSlot(this, SLOT(testFunc(QVariant)), "/RPC/");
    }
}


//
// RPC handlers
//

QVariant ApplicationInterface::testFunc(const QVariant &param)
{
    mLogger->trace() << Q_FUNC_INFO;

    return param;
}
