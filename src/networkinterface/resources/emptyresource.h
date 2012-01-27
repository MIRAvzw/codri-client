//
// Configuration
//

// Include guard
#ifndef EMPTYRESOURCE_H
#define EMPTYRESOURCE_H

// Local includes
#include "networkinterface/resource.h"

namespace MIRA
{
    class EmptyResource : public Resource
    {
    public:
        // Construction and destruction
        EmptyResource(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent = 0)
            : Resource(iSessionManager, iParent)
        {

        }

    protected:
        // Resource implementation
        void doGET(QxtWebRequestEvent *iEvent)
        {
            postEvent(new QxtWebPageEvent(iEvent->sessionID, iEvent->requestID, "root"));
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

#endif // EMPTYRESOURCE_H
