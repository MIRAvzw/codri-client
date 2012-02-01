//
// Configuration
//

// Local includes
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

    // Start the wbeservice dispatcher
    // TODO: fix memory
    mLogger->debug() << "Starting webservice dispatcher";
    mWebserviceDispatcher = new WebserviceDispatcher(QHostAddress("127.0.0.1"), 8080);
    mWebserviceDispatcher->addService("kiosk", new KioskResource(mWebserviceDispatcher));
    mWebserviceDispatcher->addService("configuration", new ConfigurationResource(mWebserviceDispatcher));
    mWebserviceDispatcher->addService("presentation", new PresentationResource(mWebserviceDispatcher));
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

