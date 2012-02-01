//
// Configuration
//

// Include guard
#ifndef PRESENTATIONRESOURCE_H
#define PRESENTATIONRESOURCE_H

// Local includes
#include "networkinterface/jsonresource.h"

// Library includes
#include <QtCore/QVariant>

namespace MIRA
{
    class PresentationResource : public JsonResource
    {
    public:
        // Construction and destruction
        PresentationResource(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent = 0);

    private:
        // JsonResource implementation
        Result doJsonGET(QVariant& iReply);

        // Location resource
        class Location : public JsonResource {
        public:
            Location(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent = 0)
                : JsonResource(iSessionManager, iParent)
            { }
            Result doJsonGET(QVariant& iReply);
            Result doJsonPUT(QVariant &iRequest, QVariant &iReply);
        };
        Location *mLocation;

        // Revision resource
        class Revision : public JsonResource {
        public:
            Revision(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent = 0)
                : JsonResource(iSessionManager, iParent)
            { }
            Result doJsonGET(QVariant& iReply);
        };
        Revision *mRevision;
    };
}

#endif // PRESENTATIONRESOURCE_H
