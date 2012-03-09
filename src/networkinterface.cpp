
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
    mLogger =  Log4Qt::Logger::logger(metaObject()->className());

    // Get webservice port
    unsigned int tPort = mSettings->value("port", 8080).toUInt();
    MainApplication::instance()->kiosk()->setPort(tPort);

    // Start the webservice dispatcher
    // TODO: fix memory
    mLogger->debug() << "Starting webservice";
    mWebserviceDispatcher = new WebserviceDispatcher(QHostAddress::Any, tPort);
    mWebserviceDispatcher->addService("kiosk", new KioskResource(mWebserviceDispatcher, mWebserviceDispatcher));
    mWebserviceDispatcher->addService("configuration", new ConfigurationResource(mWebserviceDispatcher, mWebserviceDispatcher));
    mWebserviceDispatcher->addService("presentation", new PresentationResource(mWebserviceDispatcher, mWebserviceDispatcher));
    mWebserviceDispatcher->start();

    // Instantiate server client
    mServerClient = new ServerClient("http://codri.local:8080/codri", this);

    // Registration controller
    mRegistrationController = new RegistrationController(mServerClient, this);
    mRegistrationController->start();
}

NetworkInterface::~NetworkInterface()
{
    mServerClient->unregisterKiosk();
}
