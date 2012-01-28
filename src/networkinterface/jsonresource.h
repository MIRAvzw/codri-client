//
// Configuration
//

// Include guard
#ifndef JSONRESOURCE_H
#define JSONRESOURCE_H

// Local includes
#include "resource.h"

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
        // Service methods
        virtual QVariant doJsonGET(int iSessionId, int iRequestId);
        virtual QVariant doJsonPUT(int iSessionId, int iRequestId, QVariant& iData);
        virtual QVariant doJsonPOST(int iSessionId, int iRequestId, QVariant& iData);
        virtual QVariant doJsonDELETE(int iSessionId, int iRequestId);

        // Helper methods
        void postInvalidSyntax(int iSessionId, int iRequestId);
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
