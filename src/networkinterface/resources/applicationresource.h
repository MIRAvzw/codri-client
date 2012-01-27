//
// Configuration
//

// Include guard
#ifndef APPLICATIONRESOURCE_H
#define APPLICATIONRESOURCE_H

// Local includes
#include "networkinterface/resource.h"

namespace MIRA
{
    class ApplicationResource : public Resource
    {
    public:
        // Construction and destruction
        ApplicationResource(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent = 0);

    protected:
        // Resource implementation
        void doGET(QxtWebRequestEvent *iEvent)
        {
            postEvent(new QxtWebPageEvent(iEvent->sessionID, iEvent->requestID, "foobar"));
        }

        void doPUT(QxtWebRequestEvent *iEvent)
        {
        }

        void doPOST(QxtWebRequestEvent *iEvent)
        {
        }

        void doDELETE(QxtWebRequestEvent *iEvent)
        {
        }
    };
}

#endif // APPLICATIONRESOURCE_H
