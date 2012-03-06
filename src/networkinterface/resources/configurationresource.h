//
// Configuration
//

// Include guard
#ifndef APPLICATIONRESOURCE_H
#define APPLICATIONRESOURCE_H

// Local includes
#include "networkinterface/jsonresource.h"

// Library includes
#include <QtCore/QVariant>

namespace MIRA
{
    class ConfigurationResource : public JsonResource
    {
    public:
        // Construction and destruction
        ConfigurationResource(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent = 0);

    private:
        // JsonResource implementation
        Result doJsonGET(QVariant& iReply);

        // Revision resource
        class Revision : public JsonResource {
        public:
            Revision(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent = 0)
                : JsonResource(iSessionManager, iParent)
            { }
            Result doJsonGET(QVariant& iReply);
        };
        Revision *mRevision;

        // Volume resource
        class Volume : public JsonResource {
        public:
            Volume(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent = 0)
                : JsonResource(iSessionManager, iParent)
            { }
            Result doJsonGET(QVariant& iReply);
        };
        Volume *mVolume;
    };
}

#endif // APPLICATIONRESOURCE_H
