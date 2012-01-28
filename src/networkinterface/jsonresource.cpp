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

void JsonResource::doJsonGET(int iSessionId, int iRequestId)
{
    postUnsupportedMethod(iSessionId, iRequestId);
}

void JsonResource::doJsonPUT(int iSessionId, int iRequestId, QVariant&)
{
    postUnsupportedMethod(iSessionId, iRequestId);
}

void JsonResource::doJsonPOST(int iSessionId, int iRequestId, QVariant&)
{
    postUnsupportedMethod(iSessionId, iRequestId);
}

void JsonResource::doJsonDELETE(int iSessionId, int iRequestId)
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

void JsonResource::postReply(int iSessionId, int iRequestId, QVariantMap &iData)
{
    QString tDataString = QxtJSON::stringify(iData);
    postEvent(new QxtWebPageEvent(iSessionId, iRequestId, tDataString.toUtf8()));
}


//
// Resource implementation
//

void JsonResource::doGET(int iSessionId, int iRequestId)
{
    doJsonGET(iSessionId, iRequestId);

}

void JsonResource::doPUT(int iSessionId, int iRequestId, QString& iDataString)
{
    if (iDataString.length() > 0) {
        QVariant tData = QxtJSON::parse(iDataString);
        if (! tData.isNull()) {
            doJsonPUT(iSessionId, iRequestId, tData);
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
            doJsonPOST(iSessionId, iRequestId, tData);
        } else {
            postInvalidSyntax(iSessionId, iRequestId);
        }
    } else {
        postInvalidSyntax(iSessionId, iRequestId);
    }
}

void JsonResource::doDELETE(int iSessionId, int iRequestId)
{
    doJsonDELETE(iSessionId, iRequestId);
}
