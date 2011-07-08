//
// Configuration
//

// Local includes
#include "deviceservice.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

DeviceService::DeviceService() : Brisa::BrisaService(   DEVICE_SERVICE_TYPE,
                                                        DEVICE_SERVICE_ID,
                                                        DEVICE_SERVICE_SCPD_URL,
                                                        DEVICE_SERVICE_CONTROL_URL,
                                                        DEVICE_SERVICE_EVENT_URL )
{
    // Setup logging
    mLogger =  Log4Qt::Logger::logger("DeviceService");
    mLogger->trace() << Q_FUNC_INFO;

    // Provide the SCPD file path
    setDescriptionFile(DEVICE_SERVICE_SCPD_FILE);
}


//
// Service methods
//

BrisaOutArgument* DeviceService::shutdown(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;
    Q_UNUSED(iAction)
    Q_UNUSED(iArguments)

    emit shutdown();

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* DeviceService::reboot(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;
    Q_UNUSED(iArguments)
    Q_UNUSED(iAction)

    emit reboot();

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* DeviceService::setvolume(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;

    iAction->getStateVariable("Volume")->setAttribute(Brisa::BrisaStateVariable::Value, iArguments->value("iVolumeValue"));
    emit changeVolume(iArguments->value("iVolumeValue").toInt());

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument* DeviceService::getvolume(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;
    Q_UNUSED(iArguments)

    BrisaOutArgument* oArguments = new BrisaOutArgument();
    oArguments->insert("oVolumeValue", iAction->getStateVariable("Volume")->getAttribute(Brisa::BrisaStateVariable::Value));
    return oArguments;
}
