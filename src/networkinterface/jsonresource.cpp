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

QVariant JsonResource::doJsonGET(int iSessionId, int iRequestId)
{
    postUnsupportedMethod(iSessionId, iRequestId);
}

QVariant JsonResource::doJsonPUT(int iSessionId, int iRequestId, QVariant& iData)
{
    postUnsupportedMethod(iSessionId, iRequestId);
}

QVariant JsonResource::doJsonPOST(int iSessionId, int iRequestId, QVariant& iData)
{
    postUnsupportedMethod(iSessionId, iRequestId);
}

QVariant JsonResource::doJsonDELETE(int iSessionId, int iRequestId)
{
    postUnsupportedMethod(iSessionId, iRequestId);
}


//
// Helper methods
//

void JsonResource::postInvalidSyntax(int iSessionId, int iRequestId)
{
    // TODO: check if this error code conforms the Java one
    postEvent(new QxtWebErrorEvent(iSessionId, iRequestId, 400, "Bad Request"));
}

void JsonResource::postReply(int iSessionId, int iRequestId, QVariant &iData)
{
    QString tDataString = QxtJSON::stringify(iData);
    postEvent(new QxtWebPageEvent(iSessionId, iRequestId, tDataString.toUtf8()));
}


//
// Resource implementation
//

void JsonResource::doGET(int iSessionId, int iRequestId)
{
    QVariant tReply = doJsonGET(iSessionId, iRequestId);
    postReply(iSessionId, iRequestId, tReply);

}

void JsonResource::doPUT(int iSessionId, int iRequestId, QString& iDataString)
{
    if (iDataString.length() > 0) {
        QVariant tData = QxtJSON::parse(iDataString);
        if (! tData.isNull()) {
            QVariant tReply = doJsonPUT(iSessionId, iRequestId, tData);
            postReply(iSessionId, iRequestId, tReply);
        } else {
            postInvalidSyntax(iSessionId, iRequestId);
        }
    } else {
        postInvalidSyntax(iSessionId, iRequestId);
    }
}

void JsonResource::doPOST(int iSessionId, int iRequestId, QString& iDataString)
{
    if (iDataString.length() > 0) {
        QVariant tData = QxtJSON::parse(iDataString);
        if (! tData.isNull()) {
            QVariant tReply = doJsonPOST(iSessionId, iRequestId, tData);
            postReply(iSessionId, iRequestId, tReply);
        } else {
            postInvalidSyntax(iSessionId, iRequestId);
        }
    } else {
        postInvalidSyntax(iSessionId, iRequestId);
    }
}

void JsonResource::doDELETE(int iSessionId, int iRequestId)
{
    QVariant tReply = doJsonDELETE(iSessionId, iRequestId);
    postReply(iSessionId, iRequestId, tReply);
}
