/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef NETWORKINTERFACE_RESOURCES_PRESENTATIONRESOURCE_H_
#define NETWORKINTERFACE_RESOURCES_PRESENTATIONRESOURCE_H_

// Library includes
#include <QtCore/QVariant>

// Local includes
#include "networkinterface/jsonresource.h"

namespace Codri
{
    class PresentationResource : public JsonResource
    {
        Q_OBJECT
    public:
        // Construction and destruction
        PresentationResource(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent);

    private:
        // JsonResource implementation
        Result doJsonGET(QVariant& iReply);

        // Revision resource
        class Revision : public JsonResource {
        public:
            Revision(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent)
                : JsonResource(iSessionManager, iParent)
            { }
            Result doJsonGET(QVariant& iReply);
        };
        Revision *mRevision;

        // Location resource
        class Location : public JsonResource {
        public:
            Location(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent)
                : JsonResource(iSessionManager, iParent)
            { }
            Result doJsonGET(QVariant& iReply);
            Result doJsonPUT(const QVariant &iRequest);
        };
        Location *mLocation;
    };
}

#endif  // NETWORKINTERFACE_RESOURCES_PRESENTATIONRESOURCE_H_
