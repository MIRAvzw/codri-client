/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "network/jsonresource.h"


//
// Construction and destruction
//

Codri::JsonResource::JsonResource(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent, const QVariant& iClassName)
    : Resource(iSessionManager, iParent, (iClassName.isNull()?"Codri::JsonResource":iClassName)) {
    // QJson objects
    mParser = new QJson::Parser();
    mSerializer = new QJson::Serializer();
}

Codri::JsonResource::~JsonResource() {
    // QJson objects
    delete mParser;
    delete mSerializer;
}


//
// Service methods
//

Codri::JsonResource::Result Codri::JsonResource::doJsonGET(QVariant&) {
    return UNSUPPORTED;
}

Codri::JsonResource::Result Codri::JsonResource::doJsonPUT(const QVariant&) {
    return UNSUPPORTED;
}

Codri::JsonResource::Result Codri::JsonResource::doJsonPOST(const QVariant&) {
    return UNSUPPORTED;
}

Codri::JsonResource::Result Codri::JsonResource::doJsonDELETE() {
    return UNSUPPORTED;
}


//
// Resource implementation
//

void Codri::JsonResource::doGET(int iSessionId, int iRequestId) {
    QVariant tReply;
    Result tResult = doJsonGET(tReply);
    doJsonReply(iSessionId, iRequestId, tReply, tResult);
}

void Codri::JsonResource::doPUT(int iSessionId, int iRequestId, QIODevice *iContent) {
    bool tRequestValid;
    // FIXME: why doesn't QJson work on the QIODevice? tRequest is null if we try
    QVariant tRequest = mParser->parse(iContent->readAll(), &tRequestValid);
    if (tRequestValid) {
        QVariant tReply;
        Result tResult = doJsonPUT(tRequest);
        doJsonReply(iSessionId, iRequestId, tReply, tResult);
        return;
    } else
        mLogger->warn() << "Could not parse JSon payload: " << mParser->errorString();
    postInvalidPayload(iSessionId, iRequestId, "Unparseable Payload");
}

void Codri::JsonResource::doPOST(int iSessionId, int iRequestId, QIODevice *iContent) {
    bool tRequestValid;
    QVariant tRequest = mParser->parse(iContent, &tRequestValid);
    if (tRequestValid) {
        QVariant tReply;
        Result tResult = doJsonPOST(tRequest);
        doJsonReply(iSessionId, iRequestId, tReply, tResult);
        return;
    }
    postInvalidPayload(iSessionId, iRequestId, "Unparseable Payload");
}

void Codri::JsonResource::doDELETE(int iSessionId, int iRequestId) {
    QVariant tReply;
    Result tResult = doJsonDELETE();
    doJsonReply(iSessionId, iRequestId, tReply, tResult);
}



//
// Helper methods
//

void Codri::JsonResource::doJsonReply(int iSessionId, int iRequestId, QVariant& iReply, Result iResult) {
    switch (iResult) {
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

void Codri::JsonResource::postInvalidPayload(int iSessionId, int iRequestId, QString iErrorMessage) {
    postError(iSessionId, iRequestId, 400, iErrorMessage);
}

void Codri::JsonResource::postConflictingPayload(int iSessionId, int iRequestId) {
    postError(iSessionId, iRequestId, 409, "Conflicting Payload");
}

void Codri::JsonResource::postReply(int iSessionId, int iRequestId, QVariant &iData) {
    QString tDataString = mSerializer->serialize(iData);
    QxtWebPageEvent *tReply = new QxtWebPageEvent(iSessionId, iRequestId, tDataString.toUtf8());
    tReply->contentType = "application/json";
    postEvent(tReply);
}
