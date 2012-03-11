/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Local includes
#include "kioskresource.h"
#include "mainapplication.h"


//
// Construction and destruction
//

MIRA::KioskResource::KioskResource(QxtAbstractWebSessionManager* iSessionManager, QObject *iParent)
    : JsonResource(iSessionManager, iParent)
{
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

MIRA::JsonResource::Result MIRA::KioskResource::doJsonGET(QVariant& iReply)
{
    QVariantMap tObject;
    Result tResult = VALID;

    aggregateResult(tResult, mPower->doJsonGET(tObject["power"]));
    aggregateResult(tResult, mUuid->doJsonGET(tObject["uuid"]));

    iReply = tObject;
    return tResult;
}

MIRA::JsonResource::Result MIRA::KioskResource::Power::doJsonGET(QVariant& iReply)
{
    switch (MainApplication::instance()->kiosk()->getPower())
    {
    case Kiosk::ON:
        iReply = "on";
        break;
    case Kiosk::OFF:
        iReply = "off";
        break;
    }

    return VALID;
}

MIRA::JsonResource::Result MIRA::KioskResource::Power::doJsonPUT(const QVariant &iRequest)
{
    if (iRequest.toString() == "on")
        MainApplication::instance()->kiosk()->setPower(Kiosk::ON);
    else if (iRequest.toString() == "off")
        MainApplication::instance()->kiosk()->setPower(Kiosk::OFF);
    else
        return INVALID;

    return VALID;
}

MIRA::JsonResource::Result MIRA::KioskResource::Uuid::doJsonGET(QVariant& iReply)
{
    iReply = MainApplication::instance()->kiosk()->getUuid().toString();
    return VALID;
}
