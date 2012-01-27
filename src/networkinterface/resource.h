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
        // QxtWebServiceDirectory implementation
        void indexRequested(QxtWebRequestEvent *iEvent)
        {
            if (iEvent->method.compare("GET") == 0)
            {
                doGET(iEvent);
            }
            else if (iEvent->method.compare("PUT") == 0)
            {
                doPUT(iEvent);
            }
            else if (iEvent->method.compare("POST") == 0)
            {
                doPOST(iEvent);
            }
            else if (iEvent->method.compare("DELETE") == 0)
            {
                doDELETE(iEvent);
            }
            else
            {
                // not implemented - status code: 501
            }
        }

    private:
        // Resource service methods
        virtual void doGET(QxtWebRequestEvent *iEvent) = 0;
        virtual void doPUT(QxtWebRequestEvent *iEvent) = 0;
        virtual void doPOST(QxtWebRequestEvent *iEvent) = 0;
        virtual void doDELETE(QxtWebRequestEvent *iEvent) = 0;
    };
}

#endif // RESOURCE_H
