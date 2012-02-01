//
// Configuration
//

// Local includes
#include "presentationresource.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

PresentationResource::PresentationResource(QxtAbstractWebSessionManager* iSessionManager, QObject *iParent)
    : JsonResource(iSessionManager, iParent)
{
}


//
// JsonResource implementation
//

JsonResource::Result PresentationResource::doJsonGET(QVariant& iReply)
{
    QVariantMap tObject;
    Result tResult = VALID;

    iReply = tObject;
    return tResult;
}
