/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "network/resources/kioskresource.h"

// Local includes
#include "mainapplication.h"


//
// Construction and destruction
//

Codri::KioskResource::KioskResource(QxtAbstractWebSessionManager* iSessionManager, QObject *iParent)
    : JsonResource(iSessionManager, iParent, "Codri::KioskResource") {
}


//
// JsonResource implementation
//

Codri::JsonResource::Result Codri::KioskResource::doJsonGET(QVariant& iReply) {
    QVariantMap tObject;

    switch (MainApplication::instance()->kiosk()->getPower()) {
    case Kiosk::ON:
        tObject["power"] = "on";
        break;
    case Kiosk::OFF:
        tObject["power"] = "off";
        break;
    }

    iReply = tObject;
    return VALID;
}

Codri::JsonResource::Result Codri::KioskResource::doJsonPUT(const QVariant& iRequest) {
    if (iRequest.canConvert(QVariant::Map)) {
        const QVariantMap& iRequestMap = iRequest.toMap();

        // Optional: power state
        const QVariant& tPower = iRequestMap["power"];
        if (tPower.isValid() && !tPower.isNull()) {
            if (tPower.canConvert(QVariant::String)) {
                if (tPower.toString() == "on") {
                    MainApplication::instance()->kiosk()->setPower(Kiosk::ON);
                } else if (tPower.toString() == "off") {
                    MainApplication::instance()->kiosk()->setPower(Kiosk::OFF);
                } else {
                    mLogger->warn() << "Invalid power state in PUT request";
                    return INVALID;
                }
            } else {
                mLogger->warn() << "Missing (or invalid) power state in PUT request";
                return INVALID;
            }
        }
    } else {
        mLogger->warn() << "Couldn't convert payload of collection PUT request to a map";
        return INVALID;
    }

    return VALID;
}

