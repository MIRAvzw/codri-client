//
// Configuration
//

// Local includes
#include "applicationservice.h"


//
// Construction and destruction
//

ApplicationService::ApplicationService() : Brisa::BrisaService( APP_SERVICE_TYPE,
                                                                APP_SERVICE_ID,
                                                                APP_SERVICE_XML_PATH,
                                                                APP_SERVICE_CONTROL,
                                                                APP_SERVICE_EVENT_SUB )
{
    // Setup logging
    mLogger =  Log4Qt::Logger::logger("ApplicationService");
    mLogger->trace() << Q_FUNC_INFO;

}

ApplicationService::~ApplicationService()
{

}


//
// Service methods
//

BrisaOutArgument* SetVolume(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    iAction->getStateVariable("Volume")->setAttribute(Brisa::BrisaStateVariable::Value, iArguments->value("iVolumeValue"));

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* GetVolume(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    Q_UNUSED(iArguments)

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    oArguments->insert("oVolumeValue", iAction->getStateVariable("Volume")->getAttribute(Brisa::BrisaStateVariable::Value));
    return oArguments;
}

BrisaOutArgument* Reboot(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    Q_UNUSED(iArguments)
    Q_UNUSED(iAction)

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* Shutdown(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    Q_UNUSED(iAction)
    Q_UNUSED(iArguments)

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}
