//
// Configuration
//

// Include guard
#ifndef JSONRESOURCE_H
#define JSONRESOURCE_H

// Local includes
#include "resource.h"
#include "qexception.h"

// Library includes
#include <QtCore/QString>
#include <QxtCore/QxtJSON>

namespace MIRA
{
    class JsonResource : public Resource
    {
        Q_OBJECT

    public:
        // Construction and destruction
        JsonResource(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent = 0);
        virtual ~JsonResource();

    protected:
        // Result enum
        // TODO: similar way in Resource? Passing ByteArray?
        enum Result {
            VALID,
            INVALID,
            CONFLICT,
            UNSUPPORTED
        };
        void aggregateResult(Result& a, const Result& b) {
            if (b != VALID)
                a = b;
        }

        // Service methods
        virtual Result doJsonGET(QVariant& iReply);
        virtual Result doJsonPUT(QVariant& iRequest, QVariant& iReply);
        virtual Result doJsonPOST(QVariant& iRequest, QVariant& iReply);
        virtual Result doJsonDELETE(QVariant& iReply);

        // Helper methods
        void doJsonReply(int iSessionId, int iRequestId, QVariant& iReply, Result iResult);
        void postInvalidPayload(int iSessionId, int iRequestId, QString iMessage);
        void postConflictingPayload(int iSessionId, int iRequestId);
        void postReply(int iSessionId, int iRequestId, QVariant &iData);

    private:
        // Resource implementation
        void doGET(int iSessionId, int iRequestId);
        void doPUT(int iSessionId, int iRequestId, QString& iDataString);
        void doPOST(int iSessionId, int iRequestId, QString& iDataString);
        void doDELETE(int iSessionId, int iRequestId);
    };
}

#endif // JSONRESOURCE_H
