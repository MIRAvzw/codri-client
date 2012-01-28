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
        Resource(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent = 0);
        virtual ~Resource();

    protected:
        // Service methods
        virtual void doGET(const int iSessionId, int iRequestId);
        virtual void doPUT(int iSessionId, int iRequestId, QString& iDataString);
        virtual void doPOST(int iSessionId, int iRequestId, QString& iDataString);
        virtual void doDELETE(int iSessionId, int iRequestId);

        // Helper methods
        void postUnsupportedMethod(int iSessionId, int iRequestId);

    private:
        // QxtWebServiceDirectory implementation
        void indexRequested(QxtWebRequestEvent *iEvent);

        // Auxiliary
        void handleCompleteEvent(QxtWebRequestEvent *iEvent);
        QString readBody(QxtWebRequestEvent *iEvent);
    };
}

#endif // RESOURCE_H
