//
// Configuration
//

// Include guard
#ifndef APPLICATIONSERVICE_H
#define APPLICATIONSERVICE_H

// Library includes
#include <BrisaUpnp/BrisaAction>
#include <BrisaUpnp/BrisaService>
#include <Log4Qt/Logger>

// Definitions
#define APP_SERVICE_TYPE "urn:mira-be:service:Application:1"
#define APP_SERVICE_ID "urn:mira-be:serviceId:Application:1"
#define APP_SERVICE_XML_PATH "descriptions/application_scpd.xml"
#define APP_SERVICE_CONTROL "/application/control"
#define APP_SERVICE_EVENT_SUB "/application/eventing"

class ApplicationService : public Brisa::BrisaService
{
public:
    // Construction and destruction
    ApplicationService();
    virtual ~ApplicationService();

private slots:
    // Service actions
    BrisaOutArgument* Shutdown(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction);
    BrisaOutArgument* Reboot(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction);
    BrisaOutArgument* GetVolume(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction);
    BrisaOutArgument* SetVolume(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction);

    // Data members
    Log4Qt::Logger *mLogger;
};

#endif // APPLICATIONSERVICE_H
