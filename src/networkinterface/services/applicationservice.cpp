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

BrisaOutArgument* ApplicationService::setinterface(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;

    mLogger->debug() << "Loading the interface from " << iArguments->value("iInterfaceValue");
    iAction->getStateVariable("Interface")->setAttribute(Brisa::BrisaStateVariable::Value, iArguments->value("iInterfaceValue"));

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

BrisaOutArgument* ApplicationService::setmedia(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;

    mLogger->debug() << "Loading the media from " << iArguments->value("iInterfaceValue");
    iAction->getStateVariable("Media")->setAttribute(Brisa::BrisaStateVariable::Value, iArguments->value("iMediaValue"));

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

