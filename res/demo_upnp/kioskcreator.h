#include <HUpnpCore/HDeviceModelCreator>

#ifndef KIOSKCREATOR_H
#define KIOSKCREATOR_H

class KioskCreator : public Herqq::Upnp::HDeviceModelCreator
{
protected:
    virtual KioskCreator* newInstance() const
    {
        return new KioskCreator();
    }


public:
    virtual Herqq::Upnp::HServerDevice* createDevice(const Herqq::Upnp::HDeviceInfo& info) const;
    virtual Herqq::Upnp::HServerService* createService(const Herqq::Upnp::HServiceInfo& serviceInfo, const Herqq::Upnp::HDeviceInfo&) const;
};
#endif // KIOSKCREATOR_H
