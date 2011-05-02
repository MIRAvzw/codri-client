//
// Configuration
//

// Local includes
#include "applicationservice.h"

// Library includes
#include <HUpnpCore/HServerAction>
#include <HUpnpCore/HServerStateVariable>


//
// Construction and destruction
//

ApplicationService::ApplicationService()
{

}

ApplicationService::~ApplicationService()
{

}


//
// Service interface
//

Herqq::Upnp::HServerService::HActionInvokes ApplicationService::createActionInvokes()
{
    Herqq::Upnp::HServerService::HActionInvokes retVal;

    retVal.insert("Shutdown", Herqq::Upnp::HActionInvoke(this, &ApplicationService::Shutdown));
    retVal.insert("Reboot", Herqq::Upnp::HActionInvoke(this, &ApplicationService::Reboot));
    retVal.insert("GetVolume", Herqq::Upnp::HActionInvoke(this, &ApplicationService::GetVolume));
    retVal.insert("SetVolume", Herqq::Upnp::HActionInvoke(this, &ApplicationService::SetVolume));

    return retVal;
}


//
// Service methods
//

qint32 ApplicationService::SetVolume(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs)
{
    Herqq::Upnp::HActionArgument iVolumeValue = inArgs.get("iVolumeValue");

    stateVariables().value("Volume")->setValue(iVolumeValue.value().toInt());

    return Herqq::Upnp::UpnpSuccess;
}

qint32 ApplicationService::GetVolume(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs)
{
    int tVolumeValue = stateVariables().value("Volume")->value().toInt();
    outArgs->setValue("oVolumeValue", tVolumeValue);

    return Herqq::Upnp::UpnpSuccess;
}

qint32 ApplicationService::Reboot(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs)
{
    return Herqq::Upnp::UpnpSuccess;
}

qint32 ApplicationService::Shutdown(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs)
{
    return Herqq::Upnp::UpnpSuccess;
}
