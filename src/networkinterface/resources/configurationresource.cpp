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
}


//
// JsonResource implementation
//


JsonResource::Result ConfigurationResource::doJsonGET(QVariant& iReply)
{
    QVariantMap tObject;
    Result tResult = VALID;

    aggregateResult(tResult, mRevision->doJsonGET(tObject["revision"]));

    iReply = tObject;
    return tResult;
}

JsonResource::Result ConfigurationResource::Revision::doJsonGET(QVariant& iReply)
{
    iReply = (unsigned long long) MainApplication::instance()->controller()->presentation()->getRevision();
    return VALID;
}
