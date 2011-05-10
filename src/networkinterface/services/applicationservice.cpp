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

    // Provide the SCPT file path
    setDescriptionFile(APPLICATION_SERVICE_SCPD_FILE);
}


//
// Service methods
//

BrisaOutArgument* ApplicationService::setinterfacelocation(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;
    iAction->getStateVariable("InterfaceLocation")->setAttribute(Brisa::BrisaStateVariable::Value, iArguments->value("iInterfaceLocationValue"));

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* ApplicationService::loadinterface(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;
    Q_UNUSED(iArguments)

    iAction->getStateVariable("InterfaceRevision")->setAttribute(Brisa::BrisaStateVariable::Value, iAction->getStateVariable("InterfaceRevision")->getValue().toInt()+1);

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* ApplicationService::getinterfacerevision(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;
    Q_UNUSED(iArguments)

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    oArguments->insert("oInterfaceRevisionValue", iAction->getStateVariable("InterfaceRevision")->getAttribute(Brisa::BrisaStateVariable::Value));
    return oArguments;
}

BrisaOutArgument* ApplicationService::setmedialocation(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;

    iAction->getStateVariable("MediaLocation")->setAttribute(Brisa::BrisaStateVariable::Value, iArguments->value("iMediaLocationValue"));

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* ApplicationService::loadmedia(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;
    Q_UNUSED(iArguments)

    iAction->getStateVariable("MediaRevision")->setAttribute(Brisa::BrisaStateVariable::Value, iAction->getStateVariable("MediaRevision")->getValue().toInt()+1);

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* ApplicationService::getmediarevision(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;
    Q_UNUSED(iArguments)

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    oArguments->insert("oMediaRevisionValue", iAction->getStateVariable("MediaRevision")->getAttribute(Brisa::BrisaStateVariable::Value));
    return oArguments;
}

