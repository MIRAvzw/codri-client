/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef NETWORK_RESOURCES_CONFIGURATIONRESOURCE_H_
#define NETWORK_RESOURCES_CONFIGURATIONRESOURCE_H_

// Library includes
#include <QtCore/QVariant>

// Local includes
#include "network/jsonresource.h"

namespace Codri {
    class ConfigurationResource : public JsonResource {
        Q_OBJECT
    public:
        // Construction and destruction
        ConfigurationResource(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent);

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

        // Volume resource
        class Volume : public JsonResource {
        public:
            Volume(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent)
                : JsonResource(iSessionManager, iParent) { }
            Result doJsonGET(QVariant& iReply);
            Result doJsonPUT(const QVariant& iRequest);
        };
        Volume *mVolume;
    };
}

#endif  // NETWORK_RESOURCES_CONFIGURATIONRESOURCE_H_
