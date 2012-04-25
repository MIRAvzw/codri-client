/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "network/resources/presentationresource.h"

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

    // Path resource
    mPath = new Path(iSessionManager, this);
    addService("path", mPath);
}


//
// JsonResource implementation
//

Codri::JsonResource::Result Codri::PresentationResource::doJsonGET(QVariant& iReply) {
    QVariantMap tObject;
    Result tResult = VALID;

    aggregateResult(tResult, mRevision->doJsonGET(tObject["revision"]));
    aggregateResult(tResult, mPath->doJsonGET(tObject["path"]));

    iReply = tObject;
    return tResult;
}

Codri::JsonResource::Result Codri::PresentationResource::doJsonPUT(const QVariant& iRequest) {
    Result tResult = INVALID;

    if (iRequest.canConvert(QVariant::Map)) {
        tResult = VALID;
        const QVariantMap& iRequestMap = iRequest.toMap();

        // Mandatory fields
        aggregateResult(tResult, mRevision->doJsonPUT(iRequestMap["revision"]));
        aggregateResult(tResult, mPath->doJsonPUT(iRequestMap["path"]));
    } else {
        mLogger->warn() << "Couldn't convert payload of collection PUT request to a map";
    }

    return tResult;
}

Codri::JsonResource::Result Codri::PresentationResource::Revision::doJsonGET(QVariant& iReply) {
    iReply = MainApplication::instance()->presentation()->getRevision();
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

Codri::JsonResource::Result Codri::PresentationResource::Path::doJsonGET(QVariant& iReply) {
    iReply = MainApplication::instance()->presentation()->getPath();
    return VALID;
}

Codri::JsonResource::Result Codri::PresentationResource::Path::doJsonPUT(const QVariant &iRequest) {
    if (iRequest.canConvert(QVariant::String)) {
        MainApplication::instance()->presentation()->setPath(iRequest.toString());
    } else {
        mLogger->warn() << "Missing (or invalid) path in PUT request";
        return INVALID;
    }

    return VALID;
}
