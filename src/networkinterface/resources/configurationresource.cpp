/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Local includes
#include "configurationresource.h"
#include "mainapplication.h"

// Library includes
#include <QtCore/QMap>

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

ConfigurationResource::ConfigurationResource(QxtAbstractWebSessionManager* iSessionManager, QObject *iParent)
    : JsonResource(iSessionManager, iParent)
{
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


JsonResource::Result ConfigurationResource::doJsonGET(QVariant& iReply)
{
    QVariantMap tObject;
    Result tResult = VALID;

    aggregateResult(tResult, mRevision->doJsonGET(tObject["revision"]));
    aggregateResult(tResult, mVolume->doJsonGET(tObject["volume"]));

    iReply = tObject;
    return tResult;
}

JsonResource::Result ConfigurationResource::doJsonPUT(const QVariant& iRequest)
{
    Result tResult = INVALID;

    if (iRequest.canConvert(QVariant::Map)) {
        tResult = VALID;
        const QVariantMap& iRequestMap = iRequest.toMap();

        aggregateResult(tResult, mRevision->doJsonPUT(iRequestMap["revision"]));
        aggregateResult(tResult, mVolume->doJsonPUT(iRequestMap["volume"]));
    } else {
        mLogger->warn("Couldn't convert payload of collection PUT request to a map");
    }

    return tResult;
}

JsonResource::Result ConfigurationResource::Revision::doJsonGET(QVariant& iReply)
{
    iReply = (unsigned long long) MainApplication::instance()->configuration()->getRevision();
    return VALID;
}

JsonResource::Result ConfigurationResource::Revision::doJsonPUT(const QVariant& iRequest)
{
    if (iRequest.canConvert(QVariant::LongLong)) {
        MainApplication::instance()->configuration()->setRevision(iRequest.toLongLong());
        return VALID;
    } else {
        mLogger->warn("Missing (or invalid) revision in PUT request");
        return INVALID;
    }
}

JsonResource::Result ConfigurationResource::Volume::doJsonGET(QVariant& iReply)
{
    iReply = (unsigned long long) MainApplication::instance()->configuration()->getVolume();
    return VALID;
}

JsonResource::Result ConfigurationResource::Volume::doJsonPUT(const QVariant& iRequest)
{
    if (iRequest.canConvert(QVariant::Int)) {
        MainApplication::instance()->configuration()->setVolume(iRequest.toInt());
        return VALID;
    } else {
        mLogger->warn("Missing (or invalid) volume in PUT request");
        return INVALID;
    }
}
