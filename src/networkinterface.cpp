//
// Configuration
//

// Local includes
#include "mainapplication.h"
#include "networkinterface.h"
#include "networkinterface/resources/kioskresource.h"
#include "networkinterface/resources/configurationresource.h"
#include "networkinterface/resources/presentationresource.h"

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

    // Get webservice port
    unsigned int tPort = mSettings->value("port", 8080).toUInt();
    MainApplication::instance()->controller()->kiosk()->setPort(tPort);

    // Start the webservice dispatcher
    // TODO: fix memory
    mLogger->debug() << "Starting webservice dispatcher";
    mWebserviceDispatcher = new WebserviceDispatcher(QHostAddress("127.0.0.1"), tPort);
    mWebserviceDispatcher->addService("kiosk", new KioskResource(mWebserviceDispatcher));
    mWebserviceDispatcher->addService("configuration", new ConfigurationResource(mWebserviceDispatcher));
    mWebserviceDispatcher->addService("presentation", new PresentationResource(mWebserviceDispatcher));
    mWebserviceDispatcher->start();

    // Schedule server connection request
    mConnectionTimer = new QTimer(this);
    connect(mConnectionTimer, SIGNAL(timeout()), this, SLOT(_onConnectionTimeout()));
    mConnectionTimer->start(0);

    // Schedule heartbeat messages
    mHeartbeatTimer = new QTimer(this);
    connect(mHeartbeatTimer, SIGNAL(timeout()), this, SLOT(_onHeartbeatTimeout()));
    mHeartbeatTimer->start(mSettings->value("heartbeat", 30*1000).toInt());
}

NetworkInterface::~NetworkInterface()
{
    mLogger->trace() << Q_FUNC_INFO;
}


//
// Private signal handlers
//

void NetworkInterface::_onConnectionTimeout()
{

}

void NetworkInterface::_onHeartbeatTimeout()
{

}
