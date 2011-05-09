//
// Configuration
//

// Local includes
#include "dataservice.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

DataService::DataService() : Brisa::BrisaService(   DATA_SERVICE_TYPE,
                                                    DATA_SERVICE_ID,
                                                    DATA_SERVICE_SCPD_URL,
                                                    DATA_SERVICE_CONTROL_URL,
                                                    DATA_SERVICE_EVENT_URL )
{
    // Setup logging
    mLogger =  Log4Qt::Logger::logger("ApplicationService");
    mLogger->trace() << Q_FUNC_INFO;

    // Provide the SCPT file path
    setDescriptionFile(DATA_SERVICE_SCPD_FILE);
}


//
// Service methods
//

BrisaOutArgument* DataService::setinterfacelocation(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    iAction->getStateVariable("InterfaceLocation")->setAttribute(Brisa::BrisaStateVariable::Value, iArguments->value("iInterfaceLocationValue"));

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* DataService::loadinterface(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    Q_UNUSED(iArguments)

    iAction->getStateVariable("InterfaceRevision")->setAttribute(Brisa::BrisaStateVariable::Value, iAction->getStateVariable("InterfaceRevision")->getValue().toInt()+1);

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* DataService::getinterfacerevision(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    Q_UNUSED(iArguments)

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    oArguments->insert("oInterfaceRevisionValue", iAction->getStateVariable("InterfaceRevision")->getAttribute(Brisa::BrisaStateVariable::Value));
    return oArguments;
}

BrisaOutArgument* DataService::setmedialocation(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    iAction->getStateVariable("MediaLocation")->setAttribute(Brisa::BrisaStateVariable::Value, iArguments->value("iMediaLocationValue"));

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* DataService::loadmedia(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    Q_UNUSED(iArguments)

    iAction->getStateVariable("MediaRevision")->setAttribute(Brisa::BrisaStateVariable::Value, iAction->getStateVariable("MediaRevision")->getValue().toInt()+1);

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* DataService::getmediarevision(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    Q_UNUSED(iArguments)

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    oArguments->insert("oMediaRevisionValue", iAction->getStateVariable("MediaRevision")->getAttribute(Brisa::BrisaStateVariable::Value));
    return oArguments;
}
