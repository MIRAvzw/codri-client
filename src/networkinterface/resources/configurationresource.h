/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

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

namespace Codri
{
    class ConfigurationResource : public JsonResource
    {
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
                : JsonResource(iSessionManager, iParent)
            { }
            Result doJsonGET(QVariant& iReply);
            Result doJsonPUT(const QVariant& iRequest);
        };
        Revision *mRevision;

        // Volume resource
        class Volume : public JsonResource {
        public:
            Volume(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent)
                : JsonResource(iSessionManager, iParent)
            { }
            Result doJsonGET(QVariant& iReply);
            Result doJsonPUT(const QVariant& iRequest);
        };
        Volume *mVolume;
    };
}

#endif // APPLICATIONRESOURCE_H
