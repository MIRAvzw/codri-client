//
// Configuration
//

// Local includes
#include "webservicedispatcher.h"
#include "resources/emptyresource.h"

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
    mRootService = new EmptyResource(this, this);
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


//
// QxtHttpSessionManager implementation
//


void WebserviceDispatcher::incomingRequest(quint32 iRequestId, const QHttpRequestHeader &iHeader, QxtWebContent *iDeviceContent)
{
    QxtHttpSessionManager::incomingRequest(iRequestId, iHeader, iDeviceContent);
    qDebug() << "Request: "<< iRequestId;
    qDebug() << "Method: " << iHeader.method();
    qDebug() << "URI: " << iHeader.path();
}
