//
// Configuration
//

// Local includes
#include "kioskcreator.h"
#include "devices/kioskdevice.h"
#include "services/applicationservice.h"
#include "services/dataservice.h"

// Library includes
#include <HUpnpCore/HDeviceInfo>
#include <HUpnpCore/HServiceInfo>


//
// Model creator interface
//

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
    if (serviceInfo.serviceType().toString() == "urn:mira-be:service:Application:1")
    {
        return new ApplicationService();
    }
    else if (serviceInfo.serviceType().toString() == "urn:mira-be:service:Data:1")
    {
        return new DataService();
    }

    return 0;
}
