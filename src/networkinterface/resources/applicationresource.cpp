//
// Configuration
//

// Local includes
#include "applicationresource.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

ApplicationResource::ApplicationResource(QxtAbstractWebSessionManager* iSessionManager, QObject *iParent)
    : Resource(iSessionManager, iParent)
{
}
