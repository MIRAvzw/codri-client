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

ApplicationService::ApplicationService() : Brisa::BrisaService( APPLICATION_SERVICE_TYPE,
                                                                APPLICATION_SERVICE_ID,
                                                                APPLICATION_SERVICE_SCPD_URL,
                                                                APPLICATION_SERVICE_CONTROL_URL,
                                                                APPLICATION_SERVICE_EVENT_URL )
{
    // Setup logging
    mLogger =  Log4Qt::Logger::logger("ApplicationService");
    mLogger->trace() << Q_FUNC_INFO;

    // Provide the SCPD file path
    setDescriptionFile(APPLICATION_SERVICE_SCPD_FILE);
}


//
// Service methods
//

BrisaOutArgument* ApplicationService::downloadinterface(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;

    iAction->getStateVariable("Interface")->setAttribute(Brisa::BrisaStateVariable::Value, iArguments->value("iInterfaceValue"));
    emit interfaceAdded(iArguments->value("iInterfaceValue"));

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* ApplicationService::loadinterface(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;
    Q_UNUSED(iArguments)
    Q_UNUSED(iAction)

    emit interfaceLoad();

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* ApplicationService::downloadmedia(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;

    iAction->getStateVariable("Media")->setAttribute(Brisa::BrisaStateVariable::Value, iArguments->value("iMediaValue"));
    emit mediaAdded(iArguments->value("iMediaValue"));

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* ApplicationService::loadmedia(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;
    Q_UNUSED(iArguments)
    Q_UNUSED(iAction)

    emit mediaLoad();

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

