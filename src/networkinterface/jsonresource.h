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
        JsonResource(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent = 0)
            : Resource(iSessionManager, iParent)
        {
        }
        virtual ~JsonResource()
        {
        }

    protected:
        // Service methods
        virtual QVariant doJsonGET(int iSessionId, int iRequestId) {
            postUnsupportedMethod(iSessionId, iRequestId);
        }
        virtual QVariant doJsonPUT(int iSessionId, int iRequestId, QVariant& iData) {
            postUnsupportedMethod(iSessionId, iRequestId);
        }
        virtual QVariant doJsonPOST(int iSessionId, int iRequestId, QVariant& iData) {
            postUnsupportedMethod(iSessionId, iRequestId);
        }
        virtual QVariant doJsonDELETE(int iSessionId, int iRequestId) {
            postUnsupportedMethod(iSessionId, iRequestId);
        }

        // Helper methods
        void postInvalidSyntax(int iSessionId, int iRequestId)
        {
            // TODO: check if this error code conforms the Java one
            postEvent(new QxtWebErrorEvent(iSessionId, iRequestId, 400, "Bad Request"));
        }
        void postReply(int iSessionId, int iRequestId, QVariant &iData)
        {
            QString tDataString = QxtJSON::stringify(iData);
            postEvent(new QxtWebPageEvent(iSessionId, iRequestId, tDataString.toUtf8()));
        }

    private:
        // Resource implementation
        void doGET(int iSessionId, int iRequestId)
        {
            QVariant tReply = doJsonGET(iSessionId, iRequestId);
            postReply(iSessionId, iRequestId, tReply);

        }
        void doPUT(int iSessionId, int iRequestId, QString& iDataString)
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
        void doPOST(int iSessionId, int iRequestId, QString& iDataString)
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
        void doDELETE(int iSessionId, int iRequestId)
        {
            QVariant tReply = doJsonDELETE(iSessionId, iRequestId);
            postReply(iSessionId, iRequestId, tReply);
        }
    };
}

#endif // JSONRESOURCE_H
