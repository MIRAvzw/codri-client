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
    MainApplication::instance()->kiosk()->setPort(tPort);

    // Start the webservice dispatcher
    // TODO: fix memory
    mLogger->debug() << "Starting webservice dispatcher";
    mWebserviceDispatcher = new WebserviceDispatcher(QHostAddress("127.0.0.1"), tPort);
    mWebserviceDispatcher->addService("kiosk", new KioskResource(mWebserviceDispatcher));
    mWebserviceDispatcher->addService("configuration", new ConfigurationResource(mWebserviceDispatcher));
    mWebserviceDispatcher->addService("presentation", new PresentationResource(mWebserviceDispatcher));
    mWebserviceDispatcher->start();

    // Instantiate server client
    mServerClient = new ServerClient("http://codri.local:8080/codri", this);
    connect(mServerClient, SIGNAL(connectionPerformed(bool,uint)), this, SLOT(_onConnectionPerformed(bool,uint)));
    connect(mServerClient, SIGNAL(heartbeatUpdated(bool,uint)), this, SLOT(_onHeartbeatUpdated(bool,uint)));

    // Create reconnection timer
    mConnectionTimer = new QTimer(this);
    mConnectionTimer->setSingleShot(false);
    mConnectionTimer->setInterval(mSettings->value("reconnect", 60*1000).toInt());
    connect(mConnectionTimer, SIGNAL(timeout()), this, SLOT(_onConnectionTimeout()));

    // Create heartbeat timer
    mHeartbeatTimer = new QTimer(this);
    mHeartbeatTimer->setSingleShot(false);
    mHeartbeatTimer->setInterval(mSettings->value("heartbeat", 30*1000).toInt());
    connect(mHeartbeatTimer, SIGNAL(timeout()), this, SLOT(_onHeartbeatTimeout()));

    // Schedule server connection request
    QTimer::singleShot(0, this, SLOT(_onConnectionTimeout()));
}

NetworkInterface::~NetworkInterface()
{
    mLogger->trace() << Q_FUNC_INFO;
}


//
// Private signal handlers
//

// TODO: fsm?

void NetworkInterface::_onConnectionTimeout()
{
    mServerClient->postKiosk();
}

void NetworkInterface::_onConnectionPerformed(bool iSuccess, unsigned int iErrorCode)
{
    if (iSuccess)
    {
        mLogger->info() << "Successfully connected to the server";
        mConnectionTimer->stop();
        mHeartbeatTimer->start();
    }
    else if (iErrorCode == 409)
    {
        mLogger->warn() << "Kiosk was already registered";
        mConnectionTimer->stop();
        QTimer::singleShot(0, this, SLOT(_onHeartbeatTimeout()));
    }
    else
    {
        mLogger->warn() << "Error connection to the server";
        mConnectionTimer->start();
    }
}

void NetworkInterface::_onHeartbeatTimeout()
{
    mServerClient->putKiosk();
}

void NetworkInterface::_onHeartbeatUpdated(bool iSuccess, unsigned int iErrorCode)
{
    if (iSuccess)
    {
        mLogger->debug() << "Successfully sent heartbeat to the server";
        mHeartbeatTimer->start();
    }
    else if (iErrorCode == 404)
    {
        mLogger->warn() << "Kiosk isn't registered";
        mHeartbeatTimer->stop();
        QTimer::singleShot(0, this, SLOT(_onConnectionTimeout()));
    }
    else
    {
        mLogger->warn() << "Error connection to the server";
        mHeartbeatTimer->stop();
        QTimer::singleShot(0, this, SLOT(_onConnectionTimeout()));
    }
}
