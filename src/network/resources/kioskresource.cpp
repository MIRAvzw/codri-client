/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
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
    // Power resource
    mPower = new Power(iSessionManager, this);
    addService("power", mPower);

    // Uuid resource
    mUuid = new Uuid(iSessionManager, this);
    addService("uuid", mUuid);
}


//
// JsonResource implementation
//

Codri::JsonResource::Result Codri::KioskResource::doJsonGET(QVariant& iReply) {
    QVariantMap tObject;
    Result tResult = VALID;

    aggregateResult(tResult, mPower->doJsonGET(tObject["power"]));
    aggregateResult(tResult, mUuid->doJsonGET(tObject["uuid"]));

    iReply = tObject;
    return tResult;
}

Codri::JsonResource::Result Codri::KioskResource::Power::doJsonGET(QVariant& iReply) {
    switch (MainApplication::instance()->kiosk()->getStatus()) {
    case Kiosk::ON:
        iReply = "on";
        break;
    case Kiosk::OFF:
        iReply = "off";
        break;
    }

    return VALID;
}

Codri::JsonResource::Result Codri::KioskResource::Power::doJsonPUT(const QVariant &iRequest) {
    if (iRequest.canConvert(QVariant::String)) {
        if (iRequest.toString() == "on") {
            MainApplication::instance()->kiosk()->setStatus(Kiosk::ON);
        } else if (iRequest.toString() == "off") {
            MainApplication::instance()->kiosk()->setStatus(Kiosk::OFF);
        } else {
            mLogger->warn() << "Invalid power state in PUT request";
            return INVALID;
        }
    } else {
        mLogger->warn() << "Missing (or invalid) power state in PUT request";
        return INVALID;
    }

    return VALID;
}

Codri::JsonResource::Result Codri::KioskResource::Uuid::doJsonGET(QVariant& iReply) {
    iReply = MainApplication::instance()->kiosk()->getUuid().toString();
    return VALID;
}
