/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef NETWORK_RESOURCES_PRESENTATIONRESOURCE_H_
#define NETWORK_RESOURCES_PRESENTATIONRESOURCE_H_

// Library includes
#include <QtCore/QVariant>

// Local includes
#include "network/jsonresource.h"

namespace Codri {
    class PresentationResource : public JsonResource {
    Q_OBJECT
    public:
        // Construction and destruction
        PresentationResource(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent);

    private:
        // JsonResource implementation
        Result doJsonGET(QVariant& iReply);
        Result doJsonPUT(const QVariant& iRequest);

        // Revision resource
        class Revision : public JsonResource {
        public:
            Revision(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent)
                : JsonResource(iSessionManager, iParent) { }
            Result doJsonGET(QVariant& iReply);
            Result doJsonPUT(const QVariant& iRequest);
        };
        Revision *mRevision;

        // Location resource
        class Location : public JsonResource {
        public:
            Location(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent)
                : JsonResource(iSessionManager, iParent) { }
            Result doJsonGET(QVariant& iReply);
            Result doJsonPUT(const QVariant &iRequest);
        };
        Location *mLocation;
    };
}

#endif  // NETWORK_RESOURCES_PRESENTATIONRESOURCE_H_
