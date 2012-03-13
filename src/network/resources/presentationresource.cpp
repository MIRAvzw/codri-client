/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "presentationresource.h"

// Local includes
#include "mainapplication.h"


//
// Construction and destruction
//

Codri::PresentationResource::PresentationResource(QxtAbstractWebSessionManager* iSessionManager, QObject *iParent)
    : JsonResource(iSessionManager, iParent, "Codri::PresentationResource") {
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

Codri::JsonResource::Result Codri::PresentationResource::doJsonGET(QVariant& iReply) {
    QVariantMap tObject;
    Result tResult = VALID;

    aggregateResult(tResult, mRevision->doJsonGET(tObject["revision"]));
    aggregateResult(tResult, mLocation->doJsonGET(tObject["location"]));

    iReply = tObject;
    return tResult;
}

Codri::JsonResource::Result Codri::PresentationResource::doJsonPUT(const QVariant& iRequest) {
    Result tResult = INVALID;

    if (iRequest.canConvert(QVariant::Map)) {
        tResult = VALID;
        const QVariantMap& iRequestMap = iRequest.toMap();

        aggregateResult(tResult, mRevision->doJsonPUT(iRequestMap["revision"]));
        aggregateResult(tResult, mLocation->doJsonPUT(iRequestMap["location"]));
    } else {
        mLogger->warn() << "Couldn't convert payload of collection PUT request to a map";
    }

    return tResult;
}

Codri::JsonResource::Result Codri::PresentationResource::Revision::doJsonGET(QVariant& iReply) {
    iReply = (unsigned long long) MainApplication::instance()->presentation()->getRevision();
    return VALID;
}

Codri::JsonResource::Result Codri::PresentationResource::Revision::doJsonPUT(const QVariant& iRequest) {
    if (iRequest.canConvert(QVariant::LongLong)) {
        MainApplication::instance()->presentation()->setRevision(iRequest.toLongLong());
        return VALID;
    } else {
        mLogger->warn() << "Missing (or invalid) revision in PUT request";
        return INVALID;
    }
}

Codri::JsonResource::Result Codri::PresentationResource::Location::doJsonGET(QVariant& iReply) {
    iReply = MainApplication::instance()->presentation()->getLocation();
    return VALID;
}

Codri::JsonResource::Result Codri::PresentationResource::Location::doJsonPUT(const QVariant &iRequest) {
    if (iRequest.canConvert(QVariant::String)) {
        MainApplication::instance()->presentation()->setLocation(iRequest.toString());
    } else {
        mLogger->warn() << "Missing (or invalid) location in PUT request";
        return INVALID;
    }

    return VALID;
}
