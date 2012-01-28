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
        void doJsonGET(int iSessionId, int iRequestId) {
            QVariantMap tReply;
            tReply["method"] = "GET";
            postReply(iSessionId, iRequestId, tReply);
        }
        void doJsonPUT(int iSessionId, int iRequestId, QVariant& iData) {
            QVariantMap tReply;
            tReply["method"] = "PUT";
            postReply(iSessionId, iRequestId, tReply);
        }
        void doJsonPOST(int iSessionId, int iRequestId, QVariant& iData) {
            QVariantMap tReply;
            tReply["method"] = "POST";
            postReply(iSessionId, iRequestId, tReply);
        }
        void doJsonDELETE(int iSessionId, int iRequestId) {
            QVariantMap tReply;
            tReply["method"] = "DELETE";
            postReply(iSessionId, iRequestId, tReply);
        }
    };
}

#endif // APPLICATIONRESOURCE_H
