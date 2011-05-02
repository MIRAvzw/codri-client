//
// Configuration
//

// Include guard
#ifndef KIOSK_H
#define KIOSK_H

// Library includes
#include <HUpnpCore/HServerDevice>

class KioskDevice : public Herqq::Upnp::HServerDevice
{
public:
    KioskDevice();
    virtual ~KioskDevice();
};

#endif // KIOSK_H
