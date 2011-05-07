#include "kiosk.h"

#include <HUpnpCore/HServerAction>
#include <HUpnpCore/HServerStateVariable>

KioskDevice::KioskDevice()
{

}

KioskDevice::~KioskDevice()
{

}

HardwareService::~HardwareService()
{

}

HardwareService::HardwareService()
{

}

SoftwareService::~SoftwareService()
{

}

SoftwareService::SoftwareService()
{

}

qint32 HardwareService::SetVolume(
    const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs)
{
    Herqq::Upnp::HActionArgument iVolumeValue = inArgs.get("iVolumeValue");

    stateVariables().value("Volume")->setValue(iVolumeValue.value().toInt());

    return Herqq::Upnp::UpnpSuccess;
}

qint32 HardwareService::GetVolume(
    const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs)
{
    int oVolumeValue = stateVariables().value("Volume")->value().toInt();
    outArgs->setValue("oVolumeValue", oVolumeValue);

    return Herqq::Upnp::UpnpSuccess;
}

qint32 HardwareService::Reboot(
    const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs)
{

    return Herqq::Upnp::UpnpSuccess;
}

qint32 HardwareService::Shutdown(
    const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs)
{

    return Herqq::Upnp::UpnpSuccess;
}

qint32 SoftwareService::LoadInterface(
    const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs)
{
    Herqq::Upnp::HActionArgument iInterfaceLocationValue = inArgs.get("iInterfaceLocationValue");

    return Herqq::Upnp::UpnpSuccess;
}

qint32 SoftwareService::LoadMedia(
    const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs)
{
    Herqq::Upnp::HActionArgument iMediaLocationValue = inArgs.get("iMediaLocationValue");

    return Herqq::Upnp::UpnpSuccess;
}
