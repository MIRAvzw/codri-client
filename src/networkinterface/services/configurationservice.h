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
#define CONFIGURATION_SERVICE_TYPE "urn:mira-be:service:Configuration:1"
#define CONFIGURATION_SERVICE_ID "urn:mira-be:serviceId:Configuration:1"
#define CONFIGURATION_SERVICE_SCPD_FILE ":/descriptions/configuration_scpd.xml"
#define CONFIGURATION_SERVICE_SCPD_URL "/urn:mira-be:serviceId:Configuration:1/scpd.xml"
#define CONFIGURATION_SERVICE_CONTROL_URL "/urn:mira-be:serviceId:Configuration:1/control"
#define CONFIGURATION_SERVICE_EVENT_URL "/urn:mira-be:serviceId:Configuration:1/eventing"

// Namespaces
using namespace Brisa;  // to prevent the MOC from being confused

namespace MIRA
{
    class ConfigurationService : public Brisa::BrisaService
    {
    Q_OBJECT
    public:
        // Construction and destruction
        ConfigurationService(QObject *iParent = 0);

        // Signals
    signals:
        void setRevision(unsigned long iRevision);
        void shutdown();
        void reboot();
        void echo(const QString& iEcho);
        void setVolume(unsigned int iVolume);

        // Service action
    private slots:
        BrisaOutArgument *getrevision(BrisaInArgument *const iArguments, BrisaAction *const iAction);
        BrisaOutArgument *setrevision(BrisaInArgument *const iArguments, BrisaAction *const iAction);
        BrisaOutArgument *shutdown(BrisaInArgument *const iArguments, BrisaAction *const iAction);
        BrisaOutArgument *reboot(BrisaInArgument *const iArguments, BrisaAction *const iAction);
        BrisaOutArgument *echo(BrisaInArgument *const iArguments, BrisaAction *const iAction);
        BrisaOutArgument *getvolume(BrisaInArgument *const iArguments, BrisaAction *const iAction);
        BrisaOutArgument *setvolume(BrisaInArgument *const iArguments, BrisaAction *const iAction);

    private:
        // Data members
        Log4Qt::Logger *mLogger;
    };
}

#endif // KIOSKSERVICE_H
