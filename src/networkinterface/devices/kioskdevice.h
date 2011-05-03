//
// Configuration
//

// Include guard
#ifndef KIOSKDEVICE_H
#define KIOSKDEVICE_H

// Library includes
#include <HUpnpCore/HServerDevice>

class KioskDevice : public Herqq::Upnp::HServerDevice
{
public:
    KioskDevice();
    virtual ~KioskDevice();
};

#endif // KIOSKDEVICE_H
