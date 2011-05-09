//
// Configuration
//

// Local includes
#include "kioskservice.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

KioskService::KioskService() : Brisa::BrisaService( KIOSK_SERVICE_TYPE,
                                                                KIOSK_SERVICE_ID,
                                                                KIOSK_SERVICE_SCPD_URL,
                                                                KIOSK_SERVICE_CONTROL_URL,
                                                                KIOSK_SERVICE_EVENT_URL )
{
    // Setup logging
    mLogger =  Log4Qt::Logger::logger("ApplicationService");
    mLogger->trace() << Q_FUNC_INFO;

    // Provide the SCPT file path
    setDescriptionFile(KIOSK_SERVICE_SCPD_FILE);
}


//
// Service methods
//

BrisaOutArgument* KioskService::shutdown(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    Q_UNUSED(iAction)
    Q_UNUSED(iArguments)

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* KioskService::reboot(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    Q_UNUSED(iArguments)
    Q_UNUSED(iAction)

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* KioskService::setvolume(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    iAction->getStateVariable("Volume")->setAttribute(Brisa::BrisaStateVariable::Value, iArguments->value("iVolumeValue"));

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* KioskService::getvolume(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    Q_UNUSED(iArguments)

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    oArguments->insert("oVolumeValue", iAction->getStateVariable("Volume")->getAttribute(Brisa::BrisaStateVariable::Value));
    return oArguments;
}
