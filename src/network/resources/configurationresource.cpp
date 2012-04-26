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
}


//
// JsonResource implementation
//


Codri::JsonResource::Result Codri::ConfigurationResource::doJsonGET(QVariant& iReply) {
    QVariantMap tObject;

    tObject["revision"] = MainApplication::instance()->configuration()->getRevision();
    tObject["volume"] = MainApplication::instance()->configuration()->getVolume();

    iReply = tObject;
    return VALID;
}

Codri::JsonResource::Result Codri::ConfigurationResource::doJsonPUT(const QVariant& iRequest) {
    if (iRequest.canConvert(QVariant::Map)) {
        const QVariantMap& iRequestMap = iRequest.toMap();

        // Mandatory: revision
        const QVariant& tRevision = iRequestMap["revision"];
        if (tRevision.canConvert(QVariant::LongLong)) {
            MainApplication::instance()->configuration()->setRevision(tRevision.toLongLong());
        } else {
            mLogger->warn("Missing (or invalid) revision in PUT request");
            return INVALID;
        }

        // Optional: volume
        const QVariant& tVolume = iRequestMap["volume"];
        if (tVolume.isValid() && !tVolume.isNull()) {
            if (tVolume.canConvert(QVariant::Int)) {
                MainApplication::instance()->configuration()->setVolume(tVolume.toInt());
            } else {
                mLogger->warn("Missing (or invalid) volume in PUT request");
                return INVALID;
            }
        }
    } else {
        mLogger->warn() << "Couldn't convert payload of collection PUT request to a map";
        return INVALID;
    }

    return VALID;
}
