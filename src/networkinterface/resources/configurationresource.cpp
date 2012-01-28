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
}


//
// JsonResource implementation
//


void ConfigurationResource::doJsonGET(int iSessionId, int iRequestId)
{
    QVariantMap tReply;

    tReply["foo"] = "bar";

    postReply(iSessionId, iRequestId, tReply);
}
