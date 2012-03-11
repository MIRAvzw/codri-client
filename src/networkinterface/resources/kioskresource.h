/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef KIOSKRESOURCE_H_
#define KIOSKRESOURCE_H_

// Local includes
#include "networkinterface/jsonresource.h"

// Library includes
#include <QtCore/QVariant>

namespace Codri
{
    class KioskResource : public JsonResource
    {
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
                : JsonResource(iSessionManager, iParent)
            { }
            Result doJsonGET(QVariant& iReply);
        };
        Uuid *mUuid;
    };
}

#endif  // KIOSKRESOURCE_H_
