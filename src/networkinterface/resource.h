//
// Configuration
//

// Include guard
#ifndef RESOURCE_H
#define RESOURCE_H

// Library includes
#include <QtCore/QString>
#include <QxtWeb/QxtWebServiceDirectory>
#include <QxtWeb/QxtWebRequestEvent>
#include <QxtWeb/QxtWebContent>

namespace MIRA
{
    class Resource : public QxtWebServiceDirectory
    {
        Q_OBJECT

    public:
        // Construction and destruction
        Resource(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent = 0)
            : QxtWebServiceDirectory(iSessionManager, iParent)
        {
        }
        virtual ~Resource()
        {
        }

    protected:
        // Service methods
        virtual void doGET(const int iSessionId, int iRequestId)
        {
            postUnsupportedMethod(iSessionId, iRequestId);
        }
        virtual void doPUT(int iSessionId, int iRequestId, QString& iDataString)
        {
            postUnsupportedMethod(iSessionId, iRequestId);
        }
        virtual void doPOST(int iSessionId, int iRequestId, QString& iDataString)
        {
            postUnsupportedMethod(iSessionId, iRequestId);
        }
        virtual void doDELETE(int iSessionId, int iRequestId)
        {
            postUnsupportedMethod(iSessionId, iRequestId);
        }

        // Helper methods
        void postUnsupportedMethod(int iSessionId, int iRequestId)
        {
            // TODO: check if this error code conforms the Java one
            postEvent(new QxtWebErrorEvent(iSessionId, iRequestId, 405, "Method Not Allowed"));
        }

    private:
        // QxtWebServiceDirectory implementation
        void indexRequested(QxtWebRequestEvent *iEvent)
        {
            // Prepare the data
            // FIXME: this essentially makes the processing single-threadedly
            // http://libqxt.bitbucket.org/doc/tip/qxtwebcontent.html#waitForAllContent
            // http://dev.libqxt.org/libqxt/src/a79d60a66a86/src/web/qxtwebjsonrpcservice.cpp#cl-495
            if (iEvent->content) {
                iEvent->content->waitForAllContent();
            }
            handleCompleteEvent(iEvent);
        }

        // Event handlers
        void handleCompleteEvent(QxtWebRequestEvent *iEvent) {
            // Process all requests
            if (iEvent->method == "GET")
            {
                doGET(iEvent->sessionID, iEvent->requestID);
            }
            else if (iEvent->method == "DELETE")
            {
                doDELETE(iEvent->sessionID, iEvent->requestID);
            }
            else if (iEvent->method == "POST")
            {
                QString tDataString = readBody(iEvent);
                doPOST(iEvent->sessionID, iEvent->requestID, tDataString);
            }
            else if (iEvent->method == "PUT")
            {
                QString tDataString = readBody(iEvent);
                doPUT(iEvent->sessionID, iEvent->requestID, tDataString);
            }
            else
            {
                postUnsupportedMethod(iEvent->sessionID, iEvent->requestID);
            }
        }

        // Data handling
        QString readBody(QxtWebRequestEvent *iEvent) {
            if (iEvent->content)
            {
                return QString::fromUtf8(iEvent->content->readAll());
            }
            else
            {
                return QString();
            }
        }
    };
}

#endif // RESOURCE_H
