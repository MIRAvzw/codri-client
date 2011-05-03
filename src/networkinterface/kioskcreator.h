//
// Configuration
//

// Include guard
#ifndef KIOSKCREATOR_H
#define KIOSKCREATOR_H

// Library includes
#include <HUpnpCore/HDeviceModelCreator>
#include <HUpnpCore/HDeviceInfo>
#include <QtCore/QUuid>

// Local includes
#include "networkinterface.h"

namespace MIRA
{
    class KioskCreator : public Herqq::Upnp::HDeviceModelCreator
    {
    protected:
        virtual KioskCreator* newInstance() const
        {
            return new KioskCreator();
        }

    public:
        // Model creator interface
        virtual Herqq::Upnp::HServerDevice* createDevice(const Herqq::Upnp::HDeviceInfo& info) const;
        virtual Herqq::Upnp::HServerService* createService(const Herqq::Upnp::HServiceInfo& serviceInfo, const Herqq::Upnp::HDeviceInfo&) const;
    };
}
#endif // KIOSKCREATOR_H
