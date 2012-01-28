//
// Configuration
//

// Include guard
#ifndef APPLICATIONRESOURCE_H
#define APPLICATIONRESOURCE_H

// Local includes
#include "networkinterface/jsonresource.h"

// Library includes
#include <QtCore/QVariant>

namespace MIRA
{
    class ConfigurationResource : public JsonResource
    {
    public:
        // Construction and destruction
        ConfigurationResource(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent = 0);

    private:
        // JsonResource implementation
        Result doJsonGET(QVariant& iReply);
    };
}

#endif // APPLICATIONRESOURCE_H
