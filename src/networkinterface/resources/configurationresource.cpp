//
// Configuration
//

// Local includes
#include "configurationresource.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

ConfigurationResource::ConfigurationResource(QxtAbstractWebSessionManager* iSessionManager, QObject *iParent)
    : JsonResource(iSessionManager, iParent)
{
}


//
// JsonResource implementation
//


JsonResource::Result ConfigurationResource::doJsonGET(QVariant& iReply)
{
    QVariantMap tObject;
    Result tResult = VALID;

    tObject["foo"] = "bar";

    iReply = tObject;
    return tResult;
}
