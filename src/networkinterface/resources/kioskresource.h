//
// Configuration
//

// Include guard
#ifndef KIOSKRESOURCE_H
#define KIOSKRESOURCE_H

// Local includes
#include "networkinterface/jsonresource.h"

// Library includes
#include <QtCore/QVariant>

namespace MIRA
{
    class KioskResource : public JsonResource
    {
    public:
        // Construction and destruction
        KioskResource(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent = 0);

    private:
        // JsonResource implementation
        Result doJsonGET(QVariant& iReply);

        // Power resource
        class Power : public JsonResource {
        public:
            Power(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent = 0)
                : JsonResource(iSessionManager, iParent)
            { }
            Result doJsonGET(QVariant& iReply);
            Result doJsonPUT(const QVariant &iRequest);
        };
        Power *mPower;

        // Uuid resource
        class Uuid : public JsonResource {
        public:
            Uuid(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent = 0)
                : JsonResource(iSessionManager, iParent)
            { }
            Result doJsonGET(QVariant& iReply);
        };
        Uuid *mUuid;
    };
}

#endif // KIOSKRESOURCE_H
