/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "network/resources/configurationresource.h"

// Library includes
#include <QtCore/QMap>

// Local includes
#include "mainapplication.h"


//
// Construction and destruction
//

Codri::ConfigurationResource::ConfigurationResource(QxtAbstractWebSessionManager* iSessionManager, QObject *iParent)
    : JsonResource(iSessionManager, iParent, "Codri::ConfigurationResource") {
    // Revision resource
    mRevision = new Revision(iSessionManager, this);
    addService("revision", mRevision);

    // Volume resource
    mVolume = new Volume(iSessionManager, this);
    addService("volume", mVolume);
}


//
// JsonResource implementation
//


Codri::JsonResource::Result Codri::ConfigurationResource::doJsonGET(QVariant& iReply) {
    QVariantMap tObject;
    Result tResult = VALID;

    aggregateResult(tResult, mRevision->doJsonGET(tObject["revision"]));
    aggregateResult(tResult, mVolume->doJsonGET(tObject["volume"]));

    iReply = tObject;
    return tResult;
}

Codri::JsonResource::Result Codri::ConfigurationResource::doJsonPUT(const QVariant& iRequest) {
    Result tResult = INVALID;

    if (iRequest.canConvert(QVariant::Map)) {
        tResult = VALID;
        const QVariantMap& iRequestMap = iRequest.toMap();

        // Mandatory fields
        aggregateResult(tResult, mRevision->doJsonPUT(iRequestMap["revision"]));

        // Optional fields
        if (iRequestMap.contains("volume") && !iRequestMap["volume"].isNull())
            aggregateResult(tResult, mVolume->doJsonPUT(iRequestMap["volume"]));
    } else {
        mLogger->warn() << "Couldn't convert payload of collection PUT request to a map";
    }

    return tResult;
}

Codri::JsonResource::Result Codri::ConfigurationResource::Revision::doJsonGET(QVariant& iReply) {
    iReply = MainApplication::instance()->configuration()->getRevision();
    return VALID;
}

Codri::JsonResource::Result Codri::ConfigurationResource::Revision::doJsonPUT(const QVariant& iRequest) {
    if (iRequest.canConvert(QVariant::LongLong)) {
        MainApplication::instance()->configuration()->setRevision(iRequest.toLongLong());
        return VALID;
    } else {
        mLogger->warn("Missing (or invalid) revision in PUT request");
        return INVALID;
    }
}

Codri::JsonResource::Result Codri::ConfigurationResource::Volume::doJsonGET(QVariant& iReply) {
    iReply = MainApplication::instance()->configuration()->getVolume();
    return VALID;
}

Codri::JsonResource::Result Codri::ConfigurationResource::Volume::doJsonPUT(const QVariant& iRequest) {
    if (iRequest.canConvert(QVariant::Int)) {
        MainApplication::instance()->configuration()->setVolume(iRequest.toInt());
        return VALID;
    } else {
        mLogger->warn("Missing (or invalid) volume in PUT request");
        return INVALID;
    }
}
