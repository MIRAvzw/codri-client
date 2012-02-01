//
// Configuration
//

// Include guard
#ifndef PRESENTATIONRESOURCE_H
#define PRESENTATIONRESOURCE_H

// Local includes
#include "networkinterface/jsonresource.h"

// Library includes
#include <QtCore/QVariant>

namespace MIRA
{
    class PresentationResource : public JsonResource
    {
    public:
        // Construction and destruction
        PresentationResource(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent = 0);

    private:
        // JsonResource implementation
        Result doJsonGET(QVariant& iReply);
    };
}

#endif // PRESENTATIONRESOURCE_H
