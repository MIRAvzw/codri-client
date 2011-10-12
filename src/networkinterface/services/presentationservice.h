//
// Configuration
//

// Include guard
#ifndef PRESENTATIONSERVICE_H
#define PRESENTATIONSERVICE_H

// Library includes
#include <QtCore/QObject>
#include <BrisaUpnp/BrisaAction>
#include <BrisaUpnp/BrisaService>
#include <Log4Qt/Logger>

// Definitions
#define PRESENTATION_SERVICE_TYPE "urn:mira-be:service:Presentation:1"
#define PRESENTATION_SERVICE_ID "urn:mira-be:serviceId:Presentation:1"
#define PRESENTATION_SERVICE_SCPD_FILE ":/descriptions/presentation_scpd.xml"
#define PRESENTATION_SERVICE_SCPD_URL "/urn:mira-be:serviceId:Presentation:1/scpd.xml"
#define PRESENTATION_SERVICE_CONTROL_URL "/urn:mira-be:serviceId:Presentation:1/control"
#define PRESENTATION_SERVICE_EVENT_URL "/urn:mira-be:serviceId:Presentation:1/eventing"

// Namespaces
using namespace Brisa;  // to prevent the MOC from being confused

namespace MIRA
{
    class PresentationService : public Brisa::BrisaService
    {
    Q_OBJECT
    public:
        // Construction and destruction
        PresentationService(QObject *iParent = 0);

        // Signals
    signals:
        void setLocation(const QString &iLocation);

        // Service actions
    private slots:
        BrisaOutArgument *getrevision(BrisaInArgument *const iArguments, BrisaAction *const iAction);
        BrisaOutArgument *getlocation(BrisaInArgument *const iArguments, BrisaAction *const iAction);
        BrisaOutArgument *setlocation(BrisaInArgument *const iArguments, BrisaAction *const iAction);

    private:
        // Data members
        Log4Qt::Logger *mLogger;
    };
}

#endif // PRESENTATIONSERVICE_H
