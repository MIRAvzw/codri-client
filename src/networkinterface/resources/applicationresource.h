//
// Configuration
//

// Include guard
#ifndef APPLICATIONRESOURCE_H
#define APPLICATIONRESOURCE_H

// Local includes
#include "networkinterface/jsonresource.h"

// Library includes
#include <QtCore/QVariant>

namespace MIRA
{
    class ApplicationResource : public JsonResource
    {
    public:
        // Construction and destruction
        ApplicationResource(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent = 0);

    protected:
        // JsonResource implementation
        QVariant doJsonGET(int iSessionId, int iRequestId) {
            QVariantMap tReply;
            tReply["method"] = "GET";
            return tReply;
        }
        QVariant doJsonPUT(int iSessionId, int iRequestId, QVariant& iData) {
            QVariantMap tReply;
            tReply["method"] = "PUT";
            return tReply;
        }
        QVariant doJsonPOST(int iSessionId, int iRequestId, QVariant& iData) {
            QVariantMap tReply;
            tReply["method"] = "POST";
            return tReply;
        }
        QVariant doJsonDELETE(int iSessionId, int iRequestId) {
            QVariantMap tReply;
            tReply["method"] = "DELETE";
            return tReply;
        }
    };
}

#endif // APPLICATIONRESOURCE_H
