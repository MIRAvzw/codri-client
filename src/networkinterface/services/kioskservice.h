//
// Configuration
//

// Include guard
#ifndef KIOSKSERVICE_H
#define KIOSKSERVICE_H

// Library includes
#include <QtCore/QObject>
#include <BrisaUpnp/BrisaAction>
#include <BrisaUpnp/BrisaService>
#include <Log4Qt/Logger>

// Definitions
#define KIOSK_SERVICE_TYPE "urn:mira-be:service:Kiosk:1"
#define KIOSK_SERVICE_ID "urn:mira-be:serviceId:Kiosk:1"
#define KIOSK_SERVICE_SCPD_FILE ":/descriptions/kiosk_scpd.xml"
#define KIOSK_SERVICE_SCPD_URL "/urn:mira-be:serviceId:Kiosk:1/scpd.xml"
#define KIOSK_SERVICE_CONTROL_URL "/urn:mira-be:serviceId:Kiosk:1/control"
#define KIOSK_SERVICE_EVENT_URL "/urn:mira-be:serviceId:Kiosk:1/eventing"

// Namespaces
using namespace Brisa;  // to prevent the MOC from being confused

namespace MIRA
{
    class KioskService : public Brisa::BrisaService
    {
    Q_OBJECT
    public:
        // Construction and destruction
        KioskService();

        // Service actions
    private slots:
         BrisaOutArgument* shutdown(BrisaInArgument* const iArguments, BrisaAction* const iAction);
         BrisaOutArgument* reboot(BrisaInArgument* const iArguments, BrisaAction* const iAction);
         BrisaOutArgument* getvolume(BrisaInArgument* const iArguments, BrisaAction* const iAction);
         BrisaOutArgument* setvolume(BrisaInArgument* const iArguments, BrisaAction* const iAction);

    private:
        // Data members
        Log4Qt::Logger *mLogger;
    };
}

#endif // KIOSKSERVICE_H
