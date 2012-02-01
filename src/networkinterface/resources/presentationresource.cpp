//
// Configuration
//

// Local includes
#include "presentationresource.h"
#include "mainapplication.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

PresentationResource::PresentationResource(QxtAbstractWebSessionManager* iSessionManager, QObject *iParent)
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

JsonResource::Result PresentationResource::doJsonGET(QVariant& iReply)
{
    QVariantMap tObject;
    Result tResult = VALID;

    aggregateResult(tResult, mRevision->doJsonGET(tObject["revision"]));
    aggregateResult(tResult, mLocation->doJsonGET(tObject["location"]));

    iReply = tObject;
    return tResult;
}

JsonResource::Result PresentationResource::Revision::doJsonGET(QVariant& iReply)
{
    iReply = (unsigned long long) MainApplication::instance()->controller()->presentation()->getRevision();
    return VALID;
}

JsonResource::Result PresentationResource::Location::doJsonGET(QVariant& iReply)
{
    iReply = MainApplication::instance()->controller()->presentation()->getLocation();
    return VALID;
}

JsonResource::Result PresentationResource::Location::doJsonPUT(QVariant &iRequest, QVariant&)
{
    if (iRequest.canConvert(QVariant::String))
        MainApplication::instance()->controller()->presentation()->setLocation(iRequest.toString());
    else
        return INVALID;

    return VALID;
}
