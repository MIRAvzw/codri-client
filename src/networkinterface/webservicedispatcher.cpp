//
// Configuration
//

// Local includes
#include "webservicedispatcher.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

WebserviceDispatcher::WebserviceDispatcher(const QHostAddress &iHost, quint16 iPort)
{
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup("WebserviceDispatcher");

    // Setup logging
    mLogger =  Log4Qt::Logger::logger("WebserviceDispatcher");
    mLogger->trace() << Q_FUNC_INFO;

    QxtHttpSessionManager(this);
    mRootService = new Resource(this, this);
    setPort(iPort);
    setListenInterface(iHost);
    setConnector(HttpServer);
    setStaticContentService(mRootService);
}

WebserviceDispatcher::~WebserviceDispatcher()
{
    delete mRootService;
}


//
// Functionality
//


void WebserviceDispatcher::addService(QString iUri, Resource* iSubService)
{
    mRootService->addService(iUri, iSubService);
}

