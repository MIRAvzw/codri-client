//
// Configuration
//

// Local includes
#include "resource.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

Resource::Resource(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent)
    : QxtWebServiceDirectory(iSessionManager, iParent)
{
}
Resource::~Resource()
{
}


//
// Service methods
//

void Resource::doGET(const int iSessionId, int iRequestId)
{
    postUnsupportedMethod(iSessionId, iRequestId);
}

void Resource::doPUT(int iSessionId, int iRequestId, QIODevice*)
{
    postUnsupportedMethod(iSessionId, iRequestId);
}

void Resource::doPOST(int iSessionId, int iRequestId, QIODevice*)
{
    postUnsupportedMethod(iSessionId, iRequestId);
}

void Resource::doDELETE(int iSessionId, int iRequestId)
{
    postUnsupportedMethod(iSessionId, iRequestId);
}


//
// Helper methods
//


void Resource::postError(int iSessionId, int iRequestId, int iErrorCode, QString iErrorMessage)
{
    postEvent(new QxtWebErrorEvent(iSessionId, iRequestId, iErrorCode, iErrorMessage.toUtf8()));
}

void Resource::postUnsupportedMethod(int iSessionId, int iRequestId)
{
    // TODO: check if this error code conforms the Java
    postError(iSessionId, iRequestId, 405, "Method Not Allowed");
}


//
// QxtWebServiceDirectory implementation
//

void Resource::indexRequested(QxtWebRequestEvent *iEvent)
{
    // Prepare the data
    // FIXME: this essentially makes the processing single-threadedly
    // http://libqxt.bitbucket.org/doc/tip/qxtwebcontent.html#waitForAllContent
    // http://dev.libqxt.org/libqxt/src/a79d60a66a86/src/web/qxtwebjsonrpcservice.cpp#cl-495
    if (iEvent->content) {
        iEvent->content->waitForAllContent();
    }
    handleCompleteEvent(iEvent);
}


//
// Auxiliary
//

void Resource::handleCompleteEvent(QxtWebRequestEvent *iEvent)
{
    // Process all requests
    if (iEvent->method == "GET")
    {
        doGET(iEvent->sessionID, iEvent->requestID);
    }
    else if (iEvent->method == "DELETE")
    {
        doDELETE(iEvent->sessionID, iEvent->requestID);
    }
    else if (iEvent->method == "POST")
    {
        doPOST(iEvent->sessionID, iEvent->requestID, iEvent->content);
    }
    else if (iEvent->method == "PUT")
    {
        doPUT(iEvent->sessionID, iEvent->requestID, iEvent->content);
    }
    else
    {
        postUnsupportedMethod(iEvent->sessionID, iEvent->requestID);
    }
}

