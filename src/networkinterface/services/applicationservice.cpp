//
// Configuration
//

// Local includes
#include "applicationservice.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

ApplicationService::ApplicationService() : Brisa::BrisaService( APP_SERVICE_TYPE,
                                                                APP_SERVICE_ID,
                                                                APP_SERVICE_SCPD_URL,
                                                                APP_SERVICE_CONTROL_URL,
                                                                APP_SERVICE_EVENT_URL )
{
    // Setup logging
    mLogger =  Log4Qt::Logger::logger("ApplicationService");
    mLogger->trace() << Q_FUNC_INFO;

    // Provide the SCPT file path
    setDescriptionFile(APP_SERVICE_SCPD_FILE);
}


//
// Service methods
//

BrisaOutArgument* ApplicationService::shutdown(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    Q_UNUSED(iAction)
    Q_UNUSED(iArguments)

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* ApplicationService::reboot(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    Q_UNUSED(iArguments)
    Q_UNUSED(iAction)

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* ApplicationService::setvolume(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    iAction->getStateVariable("Volume")->setAttribute(Brisa::BrisaStateVariable::Value, iArguments->value("iVolumeValue"));

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* ApplicationService::getvolume(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    Q_UNUSED(iArguments)

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    oArguments->insert("oVolumeValue", iAction->getStateVariable("Volume")->getAttribute(Brisa::BrisaStateVariable::Value));
    return oArguments;
}
