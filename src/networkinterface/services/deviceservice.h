//
// Configuration
//

// Include guard
#ifndef KIOSKSERVICE_H
#define KIOSKSERVICE_H

// Library includes
#include <QtCore/QObject>
#include <BrisaUpnp/BrisaAction>
#include <BrisaUpnp/BrisaService>
#include <Log4Qt/Logger>

// Definitions
#define DEVICE_SERVICE_TYPE "urn:mira-be:service:Device:1"
#define DEVICE_SERVICE_ID "urn:mira-be:serviceId:Device:1"
#define DEVICE_SERVICE_SCPD_FILE ":/descriptions/device_scpd.xml"
#define DEVICE_SERVICE_SCPD_URL "/urn:mira-be:serviceId:Device:1/scpd.xml"
#define DEVICE_SERVICE_CONTROL_URL "/urn:mira-be:serviceId:Device:1/control"
#define DEVICE_SERVICE_EVENT_URL "/urn:mira-be:serviceId:Device:1/eventing"

// Namespaces
using namespace Brisa;  // to prevent the MOC from being confused

namespace MIRA
{
    class DeviceService : public Brisa::BrisaService
    {
    Q_OBJECT
    public:
        // Construction and destruction
        DeviceService(QObject *iParent = 0);

        // Signals
    signals:
        void shutdown();
        void reboot();
        void changeVolume(unsigned int iVolume);

        // Service action
    private slots:
         BrisaOutArgument *shutdown(BrisaInArgument *const iArguments, BrisaAction *const iAction);
         BrisaOutArgument *reboot(BrisaInArgument *const iArguments, BrisaAction *const iAction);
         BrisaOutArgument *getvolume(BrisaInArgument *const iArguments, BrisaAction *const iAction);
         BrisaOutArgument *setvolume(BrisaInArgument *const iArguments, BrisaAction *const iAction);

    private:
        // Data members
        Log4Qt::Logger *mLogger;
    };
}

#endif // KIOSKSERVICE_H
