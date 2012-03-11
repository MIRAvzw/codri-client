/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef PRESENTATIONRESOURCE_H_
#define PRESENTATIONRESOURCE_H_

// Local includes
#include "networkinterface/jsonresource.h"

// Library includes
#include <QtCore/QVariant>

namespace Codri
{
    class PresentationResource : public JsonResource
    {
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

#endif  // PRESENTATIONRESOURCE_H_
