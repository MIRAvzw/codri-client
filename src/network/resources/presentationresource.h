/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
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

        // Path resource
        class Path : public JsonResource {
        public:
            Path(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent)
                : JsonResource(iSessionManager, iParent) { }
            Result doJsonGET(QVariant& iReply);
            Result doJsonPUT(const QVariant &iRequest);
        };
        Path *mPath;
    };
}

#endif  // NETWORK_RESOURCES_PRESENTATIONRESOURCE_H_
