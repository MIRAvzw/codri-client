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
#include "networkinterface/services/configurationservice.h"
#include "networkinterface/services/presentationservice.h"

// Definitions
#define DEVICE_TYPE "urn:mira-be:device:Kiosk:1"
#define DEVICE_FRIENDLY_NAME "Multimedia kiosk"
#define DEVICE_MANUFACTURER "Volkssterrenwacht MIRA vzw"
#define DEVICE_MANUFACTURER_URL "www.mira.be"
#define DEVICE_MODEL_DESCRIPTION "Flexible network-enabled multimedia kiosk"
#define DEVICE_MODEL_NAME "Ad-Astra Kiosk"
#define DEVICE_MODEL_NUMBER "3.0"
#define DEVICE_MODEL_URL "https://sites.google.com/site/miraadastraiii/"
#define DEVICE_SERIAL_NUMBER "1.0"

namespace MIRA
{
    class KioskDevice : public Brisa::BrisaDevice
    {
    public:
        KioskDevice(QObject *iParent = 0);
        virtual ~KioskDevice();

        // Getters and setters
        ConfigurationService *configurationService();
        PresentationService *presentationService();

    public slots:
        void stateChanged(Brisa::BrisaStateVariable *iVariable);

    private:
        // State variables
        Brisa::BrisaStateVariable *mConfigurationRevision;
        Brisa::BrisaStateVariable *mConfigurationVolume;
        Brisa::BrisaStateVariable *mPresentationRevision;
        Brisa::BrisaStateVariable *mPresentationLocation;

        // Services
        ConfigurationService *mConfigurationService;
        PresentationService *mPresentationService;

        // Data members
        Log4Qt::Logger *mLogger;

        // Auxiliary
        QUuid getHardwareUuid() const;
        QString getUPNPUuid() const;

    };
}

#endif // KIOSKDEVICE_H
