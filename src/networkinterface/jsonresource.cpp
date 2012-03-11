/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Local includes
#include "jsonresource.h"


//
// Construction and destruction
//

MIRA::JsonResource::JsonResource(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent)
    : Resource(iSessionManager, iParent)
{
    // QJson objects
    mParser = new QJson::Parser();
    mSerializer = new QJson::Serializer();
}

MIRA::JsonResource::~JsonResource()
{
    // QJson objects
    delete mParser;
    delete mSerializer;
}


//
// Service methods
//

MIRA::JsonResource::Result MIRA::JsonResource::doJsonGET(QVariant&)
{
    return UNSUPPORTED;
}

MIRA::JsonResource::Result MIRA::JsonResource::doJsonPUT(const QVariant&)
{
    return UNSUPPORTED;
}

MIRA::JsonResource::Result MIRA::JsonResource::doJsonPOST(const QVariant&)
{
    return UNSUPPORTED;
}

MIRA::JsonResource::Result MIRA::JsonResource::doJsonDELETE()
{
    return UNSUPPORTED;
}


//
// Resource implementation
//

void MIRA::JsonResource::doGET(int iSessionId, int iRequestId)
{
    QVariant tReply;
    Result tResult = doJsonGET(tReply);
    doJsonReply(iSessionId, iRequestId, tReply, tResult);
}

void MIRA::JsonResource::doPUT(int iSessionId, int iRequestId, QIODevice *iContent)
{
    bool tRequestValid;
    QVariant tRequest = mParser->parse(iContent, &tRequestValid);
    if (tRequestValid)
    {
        QVariant tReply;
        Result tResult = doJsonPUT(tRequest);
        doJsonReply(iSessionId, iRequestId, tReply, tResult);
        return;
    }
    postInvalidPayload(iSessionId, iRequestId, "Unparseable Payload");
}

void MIRA::JsonResource::doPOST(int iSessionId, int iRequestId, QIODevice *iContent)
{
    bool tRequestValid;
    QVariant tRequest = mParser->parse(iContent, &tRequestValid);
    if (tRequestValid)
    {
        QVariant tReply;
        Result tResult = doJsonPOST(tRequest);
        doJsonReply(iSessionId, iRequestId, tReply, tResult);
        return;
    }
    postInvalidPayload(iSessionId, iRequestId, "Unparseable Payload");
}

void MIRA::JsonResource::doDELETE(int iSessionId, int iRequestId)
{
    QVariant tReply;
    Result tResult = doJsonDELETE();
    doJsonReply(iSessionId, iRequestId, tReply, tResult);
}



//
// Helper methods
//

void MIRA::JsonResource::doJsonReply(int iSessionId, int iRequestId, QVariant& iReply, Result iResult)
{
    switch (iResult)
    {
    case VALID:
        postReply(iSessionId, iRequestId, iReply);
        break;
    case CONFLICT:
        postConflictingPayload(iSessionId, iRequestId);
        break;
    case INVALID:
        postInvalidPayload(iSessionId, iRequestId, "Invalid Payload");
        break;
    case UNSUPPORTED:
        postUnsupportedMethod(iSessionId, iRequestId);
        break;
    }
}

void MIRA::JsonResource::postInvalidPayload(int iSessionId, int iRequestId, QString iErrorMessage)
{
    postError(iSessionId, iRequestId, 400, iErrorMessage);
}

void MIRA::JsonResource::postConflictingPayload(int iSessionId, int iRequestId)
{
    postError(iSessionId, iRequestId, 409, "Conflicting Payload");
}

void MIRA::JsonResource::postReply(int iSessionId, int iRequestId, QVariant &iData)
{
    QString tDataString = mSerializer->serialize(iData);
    QxtWebPageEvent *tReply = new QxtWebPageEvent(iSessionId, iRequestId, tDataString.toUtf8());
    tReply->contentType = "application/json";
    postEvent(tReply);
}
