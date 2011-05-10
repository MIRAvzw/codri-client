//
// Configuration
//

// Include guard
#ifndef KIOSKDEVICE_H
#define KIOSKDEVICE_H

// Library includes
#include <BrisaUpnp/BrisaDevice>
#include <Log4Qt/Logger>
#include <QtCore/QUuid>
#include <QtCore/QObject>

// Local includes
#include "networkinterface/services/deviceservice.h"
#include "networkinterface/services/applicationservice.h"

// Definitions
#define DEVICE_TYPE "urn:mira-be:device:Kiosk:1"
#define DEVICE_FRIENDLY_NAME "Multimedia kiosk"
#define DEVICE_MANUFACTURER "Volkssterrenwacht MIRA vzw"
#define DEVICE_MANUFACTURER_URL "www.mira.be"
#define DEVICE_MODEL_DESCRIPTION "Flexible network-enabled multimedia kiosk"
#define DEVICE_MODEL_NAME "Ad-Astra"
#define DEVICE_MODEL_NUMBER "3.0"
#define DEVICE_MODEL_URL "https://sites.google.com/site/miraadastraiii/"
#define DEVICE_SERIAL_NUMBER "1.0"

namespace MIRA
{
    class KioskDevice : public Brisa::BrisaDevice
    {
    public:
        KioskDevice(QObject* iParent = 0);
        virtual ~KioskDevice();

    public slots:
        void stateChanged(Brisa::BrisaStateVariable* iVariable);

    private:
        // State variables
        Brisa::BrisaStateVariable* mVolume;
        Brisa::BrisaStateVariable* mInterfaceLocation;
        Brisa::BrisaStateVariable* mInterfaceRevision;
        Brisa::BrisaStateVariable* mMediaLocation;
        Brisa::BrisaStateVariable* mMediaRevision;

        // Services
        DeviceService* mKioskService;
        ApplicationService* mMediaKiosk;

        // Data members
        Log4Qt::Logger *mLogger;

        // Auxiliary
        QUuid getHardwareUuid() const;

    };
}

#endif // KIOSKDEVICE_H
