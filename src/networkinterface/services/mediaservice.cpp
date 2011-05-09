//
// Configuration
//

// Local includes
#include "mediaservice.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

MediaService::MediaService() : Brisa::BrisaService(   MEDIA_SERVICE_TYPE,
                                                    MEDIA_SERVICE_ID,
                                                    MEDIA_SERVICE_SCPD_URL,
                                                    MEDIA_SERVICE_CONTROL_URL,
                                                    MEDIA_SERVICE_EVENT_URL )
{
    // Setup logging
    mLogger =  Log4Qt::Logger::logger("ApplicationService");
    mLogger->trace() << Q_FUNC_INFO;

    // Provide the SCPT file path
    setDescriptionFile(MEDIA_SERVICE_SCPD_FILE);
}


//
// Service methods
//

BrisaOutArgument* MediaService::setinterfacelocation(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    iAction->getStateVariable("InterfaceLocation")->setAttribute(Brisa::BrisaStateVariable::Value, iArguments->value("iInterfaceLocationValue"));

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* MediaService::loadinterface(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    Q_UNUSED(iArguments)

    iAction->getStateVariable("InterfaceRevision")->setAttribute(Brisa::BrisaStateVariable::Value, iAction->getStateVariable("InterfaceRevision")->getValue().toInt()+1);

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* MediaService::getinterfacerevision(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    Q_UNUSED(iArguments)

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    oArguments->insert("oInterfaceRevisionValue", iAction->getStateVariable("InterfaceRevision")->getAttribute(Brisa::BrisaStateVariable::Value));
    return oArguments;
}

BrisaOutArgument* MediaService::setmedialocation(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    iAction->getStateVariable("MediaLocation")->setAttribute(Brisa::BrisaStateVariable::Value, iArguments->value("iMediaLocationValue"));

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* MediaService::loadmedia(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    Q_UNUSED(iArguments)

    iAction->getStateVariable("MediaRevision")->setAttribute(Brisa::BrisaStateVariable::Value, iAction->getStateVariable("MediaRevision")->getValue().toInt()+1);

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* MediaService::getmediarevision(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    Q_UNUSED(iArguments)

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    oArguments->insert("oMediaRevisionValue", iAction->getStateVariable("MediaRevision")->getAttribute(Brisa::BrisaStateVariable::Value));
    return oArguments;
}
