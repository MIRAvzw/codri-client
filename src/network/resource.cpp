/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "resource.h"


//
// Construction and destruction
//

Codri::Resource::Resource(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent, const QVariant& iClassName)
    : QxtWebServiceDirectory(iSessionManager, iParent)
{
    // Setup logging
    // FIXME: get a hold of the derived classname without it having to be passed
    //        (metaObject() results in Resource's metaobject).
    //        http://stackoverflow.com/questions/5105667/behaviour-of-qmetaobject-within-a-base-class-constructor
    mLogger =  Log4Qt::Logger::logger(iClassName.isNull()?metaObject()->className():iClassName.toString());
}

Codri::Resource::~Resource()
{
}


//
// Service methods
//

void Codri::Resource::doGET(const int iSessionId, int iRequestId)
{
    postUnsupportedMethod(iSessionId, iRequestId);
}

void Codri::Resource::doPUT(int iSessionId, int iRequestId, QIODevice*)
{
    postUnsupportedMethod(iSessionId, iRequestId);
}

void Codri::Resource::doPOST(int iSessionId, int iRequestId, QIODevice*)
{
    postUnsupportedMethod(iSessionId, iRequestId);
}

void Codri::Resource::doDELETE(int iSessionId, int iRequestId)
{
    postUnsupportedMethod(iSessionId, iRequestId);
}


//
// Helper methods
//


void Codri::Resource::postError(int iSessionId, int iRequestId, int iErrorCode, QString iErrorMessage)
{
    postEvent(new QxtWebErrorEvent(iSessionId, iRequestId, iErrorCode, iErrorMessage.toUtf8()));
}

void Codri::Resource::postUnsupportedMethod(int iSessionId, int iRequestId)
{
    // TODO: check if this error code conforms the Java
    postError(iSessionId, iRequestId, 405, "Method Not Allowed");
}


//
// QxtWebServiceDirectory implementation
//

void Codri::Resource::indexRequested(QxtWebRequestEvent *iEvent)
{
    // Prepare the data
    // FIXME: this essentially makes the processing single-threadedly
    // http://libqxt.bitbucket.org/doc/tip/qxtwebcontent.html#waitForAllContent
    // http://dev.libqxt.org/libqxt/src/a79d60a66a86/src/web/qxtwebjsonrpcservice.cpp#cl-495
    if (iEvent->content)
        iEvent->content->waitForAllContent();
    handleCompleteEvent(iEvent);
}


//
// Auxiliary
//

void Codri::Resource::handleCompleteEvent(QxtWebRequestEvent *iEvent)
{
    // Process all requests
    if (iEvent->method == "GET") {
        doGET(iEvent->sessionID, iEvent->requestID);
    } else if (iEvent->method == "DELETE") {
        doDELETE(iEvent->sessionID, iEvent->requestID);
    } else if (iEvent->method == "POST") {
        doPOST(iEvent->sessionID, iEvent->requestID, iEvent->content);
    } else if (iEvent->method == "PUT") {
        doPUT(iEvent->sessionID, iEvent->requestID, iEvent->content);
    } else {
        postUnsupportedMethod(iEvent->sessionID, iEvent->requestID);
    }
}
