//
// Configuration
//

// Local includes
#include "jsonresource.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

JsonResource::JsonResource(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent)
    : Resource(iSessionManager, iParent)
{
}
JsonResource::~JsonResource()
{
}


//
// Service methods
//

JsonResource::Result JsonResource::doJsonGET(QVariant&)
{
    return UNSUPPORTED;
}

JsonResource::Result JsonResource::doJsonPUT(QVariant&, QVariant&)
{
    return UNSUPPORTED;
}

JsonResource::Result JsonResource::doJsonPOST(QVariant&, QVariant&)
{
    return UNSUPPORTED;
}

JsonResource::Result JsonResource::doJsonDELETE(QVariant&)
{
    return UNSUPPORTED;
}


//
// Resource implementation
//

void JsonResource::doGET(int iSessionId, int iRequestId)
{
    QVariant tReply;
    Result tResult = doJsonGET(tReply);
    doJsonReply(iSessionId, iRequestId, tReply, tResult);
}

void JsonResource::doPUT(int iSessionId, int iRequestId, QString& iDataString)
{
    if (iDataString.length() > 0) {
        QVariant tRequest = QxtJSON::parse(iDataString);
        if (!tRequest.isNull())
        {
            QVariant tReply;
            Result tResult = doJsonPUT(tRequest, tReply);
            doJsonReply(iSessionId, iRequestId, tReply, tResult);
            return;
        }
    }
    postInvalidPayload(iSessionId, iRequestId, "Unparseable Payload");
}

void JsonResource::doPOST(int iSessionId, int iRequestId, QString& iDataString)
{
    if (iDataString.length() > 0) {
        QVariant tRequest = QxtJSON::parse(iDataString);
        if (!tRequest.isNull())
        {
            QVariant tReply;
            Result tResult = doJsonPOST(tRequest, tReply);
            doJsonReply(iSessionId, iRequestId, tReply, tResult);
            return;
        }
    }
    postInvalidPayload(iSessionId, iRequestId, "Unparseable Payload");
}

void JsonResource::doDELETE(int iSessionId, int iRequestId)
{
    QVariant tReply;
    Result tResult = doJsonDELETE(tReply);
    doJsonReply(iSessionId, iRequestId, tReply, tResult);
}



//
// Helper methods
//

void JsonResource::doJsonReply(int iSessionId, int iRequestId, QVariant& iReply, Result iResult)
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

void JsonResource::postInvalidPayload(int iSessionId, int iRequestId, QString iErrorMessage)
{
    postError(iSessionId, iRequestId, 400, iErrorMessage);
}

void JsonResource::postConflictingPayload(int iSessionId, int iRequestId)
{
    postError(iSessionId, iRequestId, 409, "Conflicting Payload");
}

void JsonResource::postReply(int iSessionId, int iRequestId, QVariant &iData)
{
    QString tDataString = QxtJSON::stringify(iData);
    postEvent(new QxtWebPageEvent(iSessionId, iRequestId, tDataString.toUtf8()));
}
