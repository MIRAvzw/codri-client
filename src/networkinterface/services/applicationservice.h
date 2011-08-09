//
// Configuration
//

// Include guard
#ifndef MEDIASERVICE_H
#define MEDIASERVICE_H

// Library includes
#include <QtCore/QObject>
#include <BrisaUpnp/BrisaAction>
#include <BrisaUpnp/BrisaService>
#include <Log4Qt/Logger>

// Definitions
#define APPLICATION_SERVICE_TYPE "urn:mira-be:service:Application:1"
#define APPLICATION_SERVICE_ID "urn:mira-be:serviceId:Application:1"
#define APPLICATION_SERVICE_SCPD_FILE ":/descriptions/application_scpd.xml"
#define APPLICATION_SERVICE_SCPD_URL "/urn:mira-be:serviceId:Application:1/scpd.xml"
#define APPLICATION_SERVICE_CONTROL_URL "/urn:mira-be:serviceId:Application:1/control"
#define APPLICATION_SERVICE_EVENT_URL "/urn:mira-be:serviceId:Application:1/eventing"

// Namespaces
using namespace Brisa;  // to prevent the MOC from being confused

namespace MIRA
{
    class ApplicationService : public Brisa::BrisaService
    {
    Q_OBJECT
    public:
        // Construction and destruction
        ApplicationService(QObject *iParent = 0);

        // Signals
    signals:
        void loadInterface(const QString &iInterfaceIdentifier, const QString &iInterfaceRole, const QString &iInterfaceLocation);
        void loadMedia(const QString &iMediaIdentifier, const QString &iMediaLocation);

        // Service actions
    private slots:
        BrisaOutArgument *loadinterface(BrisaInArgument *const iArguments, BrisaAction *const iAction);
        BrisaOutArgument *loadmedia(BrisaInArgument *const iArguments, BrisaAction *const iAction);

    private:
        // Data members
        Log4Qt::Logger *mLogger;
    };
}

#endif // MEDIASERVICE_H
