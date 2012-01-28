//
// Configuration
//

// Local includes
#include "kioskresource.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

KioskResource::KioskResource(QxtAbstractWebSessionManager* iSessionManager, QObject *iParent)
    : JsonResource(iSessionManager, iParent)
{
    // Power resource
    mPower = new Power(iSessionManager, this);
    addService("power", mPower);
}


//
// JsonResource implementation
//

JsonResource::Result KioskResource::doJsonGET(QVariant& iReply)
{
    QVariantMap tObject;
    Result tResult = VALID;

    aggregateResult(tResult, mPower->doJsonGET(tObject["power"]));

    iReply = tObject;
    return tResult;
}

JsonResource::Result KioskResource::Power::doJsonGET(QVariant& iReply)
{
    iReply = "on";
    return VALID;
}
