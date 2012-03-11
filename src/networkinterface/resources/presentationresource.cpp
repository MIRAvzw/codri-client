/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Local includes
#include "presentationresource.h"
#include "mainapplication.h"


//
// Construction and destruction
//

Codri::PresentationResource::PresentationResource(QxtAbstractWebSessionManager* iSessionManager, QObject *iParent)
    : JsonResource(iSessionManager, iParent)
{    
    // Revision resource
    mRevision = new Revision(iSessionManager, this);
    addService("revision", mRevision);

    // Location resource
    mLocation = new Location(iSessionManager, this);
    addService("location", mLocation);
}


//
// JsonResource implementation
//

Codri::JsonResource::Result Codri::PresentationResource::doJsonGET(QVariant& iReply)
{
    QVariantMap tObject;
    Result tResult = VALID;

    aggregateResult(tResult, mRevision->doJsonGET(tObject["revision"]));
    aggregateResult(tResult, mLocation->doJsonGET(tObject["location"]));

    iReply = tObject;
    return tResult;
}

Codri::JsonResource::Result Codri::PresentationResource::Revision::doJsonGET(QVariant& iReply)
{
    iReply = (unsigned long long) MainApplication::instance()->presentation()->getRevision();
    return VALID;
}

Codri::JsonResource::Result Codri::PresentationResource::Location::doJsonGET(QVariant& iReply)
{
    iReply = MainApplication::instance()->presentation()->getLocation();
    return VALID;
}

Codri::JsonResource::Result Codri::PresentationResource::Location::doJsonPUT(const QVariant &iRequest)
{
    if (iRequest.canConvert(QVariant::String))
        MainApplication::instance()->presentation()->setLocation(iRequest.toString());
    else
        return INVALID;

    return VALID;
}
