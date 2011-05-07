#include "kioskcreator.h"
#include "kiosk.h"
#include <HUpnpCore/HDeviceInfo>
#include <HUpnpCore/HServiceInfo>


Herqq::Upnp::HServerDevice* KioskCreator::createDevice(const Herqq::Upnp::HDeviceInfo& info) const
{
    if (info.deviceType().toString() == "urn:mira-be:device:Kiosk:1")
    {
        return new KioskDevice();
    }

    return 0;
}

Herqq::Upnp::HServerService* KioskCreator::createService(const Herqq::Upnp::HServiceInfo& serviceInfo, const Herqq::Upnp::HDeviceInfo&) const
{
    if (serviceInfo.serviceType().toString() == "urn:mira-be:service:Hardware:1")
    {
        return new HardwareService();
    }
    else if (serviceInfo.serviceType().toString() == "urn:mira-be:service:Software:1")
    {
        return new SoftwareService();
    }

    return 0;
}
