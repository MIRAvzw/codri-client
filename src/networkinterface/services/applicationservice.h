//
// Configuration
//

// Include guard
#ifndef APPLICATIONSERVICE_H
#define APPLICATIONSERVICE_H

// Library includes
#include <QtCore/QObject>
#include <BrisaUpnp/BrisaAction>
#include <BrisaUpnp/BrisaService>
#include <Log4Qt/Logger>

// Definitions
#define APP_SERVICE_TYPE "urn:mira-be:service:Application:1"
#define APP_SERVICE_ID "urn:mira-be:serviceId:Application:1"
#define APP_SERVICE_SCPD_FILE ":/descriptions/application_scpd.xml"
#define APP_SERVICE_SCPD_URL "/urn:mira-be:serviceId:Application:1/scpd.xml"
#define APP_SERVICE_CONTROL_URL "/urn:mira-be:serviceId:Application:1/control"
#define APP_SERVICE_EVENT_URL "/urn:mira-be:serviceId:Application:1/eventing"

// Namespaces
using namespace Brisa;  // to prevent the MOC from being confused

namespace MIRA
{
    class ApplicationService : public Brisa::BrisaService
    {
    Q_OBJECT
    public:
        // Construction and destruction
        ApplicationService();

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

#endif // APPLICATIONSERVICE_H
