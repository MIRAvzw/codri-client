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
}


//
// JsonResource implementation
//

Codri::JsonResource::Result Codri::PresentationResource::doJsonGET(QVariant& iReply) {
    QVariantMap tObject;

    tObject["revision"] = MainApplication::instance()->presentation()->getRevision();
    tObject["path"] = MainApplication::instance()->presentation()->getPath();

    iReply = tObject;
    return VALID;
}

Codri::JsonResource::Result Codri::PresentationResource::doJsonPUT(const QVariant& iRequest) {
    if (iRequest.canConvert(QVariant::Map)) {
        const QVariantMap& iRequestMap = iRequest.toMap();

        // Mandatory: revision
        const QVariant& tRevision = iRequestMap["revision"];
        if (tRevision.canConvert(QVariant::LongLong)) {
            MainApplication::instance()->presentation()->setRevision(tRevision.toLongLong());
        } else {
            mLogger->warn("Missing (or invalid) revision in PUT request");
            return INVALID;
        }

        // Mandatory: path
        const QVariant& tPath = iRequestMap["path"];
        if (tPath.canConvert(QVariant::String)) {
            MainApplication::instance()->presentation()->setPath(tPath.toString());
        } else {
            mLogger->warn("Missing (or invalid) revision in PUT request");
            return INVALID;
        }
    } else {
        mLogger->warn() << "Couldn't convert payload of collection PUT request to a map";
        return INVALID;
    }

    return VALID;
}

