//
// Configuration
//

// Local includes
#include "configurationresource.h"
#include "mainapplication.h"

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

JsonResource::Result ConfigurationResource::Revision::doJsonGET(QVariant& iReply)
{
    iReply = (unsigned long long) MainApplication::instance()->configuration()->getRevision();
    return VALID;
}

JsonResource::Result ConfigurationResource::Volume::doJsonGET(QVariant& iReply)
{
    iReply = (unsigned long long) MainApplication::instance()->configuration()->getVolume();
    return VALID;
}
