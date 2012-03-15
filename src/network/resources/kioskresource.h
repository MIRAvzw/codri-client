/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef NETWORK_RESOURCES_KIOSKRESOURCE_H_
#define NETWORK_RESOURCES_KIOSKRESOURCE_H_

// Library includes
#include <QtCore/QVariant>

// Local includes
#include "network/jsonresource.h"

namespace Codri {
    class KioskResource : public JsonResource {
    Q_OBJECT
    public:
        // Construction and destruction
        KioskResource(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent);

    private:
        // JsonResource implementation
        Result doJsonGET(QVariant& iReply);

        // Power resource
        class Power : public JsonResource {
        public:
            Power(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent)
                : JsonResource(iSessionManager, iParent)
            { }
            Result doJsonGET(QVariant& iReply);
            Result doJsonPUT(const QVariant &iRequest);
        };
        Power *mPower;

        // Uuid resource
        class Uuid : public JsonResource {
        public:
            Uuid(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent)
                : JsonResource(iSessionManager, iParent) { }
            Result doJsonGET(QVariant& iReply);
        };
        Uuid *mUuid;
    };
}

#endif  // NETWORK_RESOURCES_KIOSKRESOURCE_H_
