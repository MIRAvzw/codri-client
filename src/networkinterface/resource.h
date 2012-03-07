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
#include <Log4Qt/Logger>

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
        virtual void doPUT(int iSessionId, int iRequestId, QIODevice *iContent);
        virtual void doPOST(int iSessionId, int iRequestId, QIODevice *iContent);
        virtual void doDELETE(int iSessionId, int iRequestId);

        // Helper methods
        void postError(int iSessionId, int iRequestId, int iErrorCode, QString iErrorMessage);
        void postUnsupportedMethod(int iSessionId, int iRequestId);

    private:
        // QxtWebServiceDirectory implementation
        void indexRequested(QxtWebRequestEvent *iEvent);

        // Auxiliary
        void handleCompleteEvent(QxtWebRequestEvent *iEvent);

    protected:
        // Subsystem objects
        Log4Qt::Logger *mLogger;
    };
}

#endif // RESOURCE_H
