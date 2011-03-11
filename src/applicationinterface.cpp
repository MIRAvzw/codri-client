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

ApplicationInterface::ApplicationInterface(QObject *parent) : QObject(parent)
{
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup("ApplicationInterface");

    // Setup logging
    mLogger =  Log4Qt::Logger::logger("ApplicationInterface");
    mLogger->trace() << Q_FUNC_INFO;

    // Create the XMLRPC-server
    //mServer = new XmlRpcServer(0, "Dev_server.crt", "Dev_server.pem");
    mServer = new XmlRpcServer(this);
    if (mServer->listen(
                QHostAddress(mSettings->value("listen_address", "127.0.0.1").toString()),
                mSettings->value("listen_port", 8080).toInt()))
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
