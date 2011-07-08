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

    iAction->getStateVariable("InterfaceIdentifier")->setAttribute(Brisa::BrisaStateVariable::Value, iArguments->value("iInterfaceIdentifierValue"));
    iAction->getStateVariable("InterfaceLocation")->setAttribute(Brisa::BrisaStateVariable::Value, iArguments->value("iInterfaceLocationValue"));
    emit downloadInterface(iArguments->value("iInterfaceIdentifierValue"), iArguments->value("iInterfaceLocationValue"));

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* ApplicationService::loadinterface(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;
    Q_UNUSED(iArguments)
    Q_UNUSED(iAction)

    emit loadInterface();

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* ApplicationService::downloadmedia(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;

    iAction->getStateVariable("MediaIdentifier")->setAttribute(Brisa::BrisaStateVariable::Value, iArguments->value("iMediaIdentifierValue"));
    iAction->getStateVariable("MediaLocation")->setAttribute(Brisa::BrisaStateVariable::Value, iArguments->value("iMediaLocationValue"));
    emit downloadMedia(iArguments->value("iMediaIdentifierValue"), iArguments->value("iMediaLocationValue"));

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* ApplicationService::loadmedia(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;
    Q_UNUSED(iArguments)
    Q_UNUSED(iAction)

    emit loadMedia();

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

