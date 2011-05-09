//
// Configuration
//

// Include guard
#ifndef MEDIASERVICE_H
#define MEDIASERVICE_H

// Library includes
#include <QtCore/QObject>
#include <BrisaUpnp/BrisaAction>
#include <BrisaUpnp/BrisaService>
#include <Log4Qt/Logger>

// Definitions
#define MEDIA_SERVICE_TYPE "urn:mira-be:service:Media:1"
#define MEDIA_SERVICE_ID "urn:mira-be:serviceId:Media:1"
#define MEDIA_SERVICE_SCPD_FILE ":/descriptions/media_scpd.xml"
#define MEDIA_SERVICE_SCPD_URL "/urn:mira-be:serviceId:Media:1/scpd.xml"
#define MEDIA_SERVICE_CONTROL_URL "/urn:mira-be:serviceId:Media:1/control"
#define MEDIA_SERVICE_EVENT_URL "/urn:mira-be:serviceId:Media:1/eventing"

// Namespaces
using namespace Brisa;  // to prevent the MOC from being confused

namespace MIRA
{
    class MediaService : public Brisa::BrisaService
    {
    Q_OBJECT
    public:
        // Construction and destruction
        MediaService();

        // Service actions
    private slots:
        BrisaOutArgument* loadinterface(BrisaInArgument* const iArguments, BrisaAction* const iAction);
        BrisaOutArgument* setinterfacelocation(BrisaInArgument* const iArguments, BrisaAction* const iAction);
        BrisaOutArgument* getinterfacerevision(BrisaInArgument* const iArguments, BrisaAction* const iAction);
        BrisaOutArgument* loadmedia(BrisaInArgument* const iArguments, BrisaAction* const iAction);
        BrisaOutArgument* setmedialocation(BrisaInArgument* const iArguments, BrisaAction* const iAction);
        BrisaOutArgument* getmediarevision(BrisaInArgument* const iArguments, BrisaAction* const iAction);

    private:
        // Data members
        Log4Qt::Logger *mLogger;
    };
}

#endif // MEDIASERVICE_H
