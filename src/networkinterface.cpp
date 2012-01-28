//
// Configuration
//

// Local includes
#include "networkinterface.h"
#include "networkinterface/resources/configurationresource.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

NetworkInterface::NetworkInterface(QObject *iParent) throw(QException) : QObject(iParent)
{
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup("NetworkInterface");

    // Setup logging
    mLogger =  Log4Qt::Logger::logger("NetworkInterface");
    mLogger->trace() << Q_FUNC_INFO;

    // TODO: connect signals

    // TODO: fix memory
    mLogger->debug() << "Starting webservice dispatcher";
    mWebserviceDispatcher = new WebserviceDispatcher(QHostAddress("127.0.0.1"), 8080);
    Resource* tConfigurationResource = new ConfigurationResource(mWebserviceDispatcher, 0);
    mWebserviceDispatcher->addService("configuration", tConfigurationResource);
    mWebserviceDispatcher->start();

    // Schedule an alive timer
    /*
    mAliveTimer = new QTimer(this);
    connect(mAliveTimer, SIGNAL(timeout()), this, SLOT(_sendAlive()));
    mAliveTimer->start(mSettings->value("alivetimer", 300*1000).toInt());
    */
}

NetworkInterface::~NetworkInterface()
{
    mLogger->trace() << Q_FUNC_INFO;
}


//
// Getters and setters
//

QString NetworkInterface::uuid() const
{
    // TODO
    return "";
}
