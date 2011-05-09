//
// Configuration
//

// Include guard
#ifndef DATASERVICE_H
#define DATASERVICE_H

// Library includes
#include <QtCore/QObject>
#include <BrisaUpnp/BrisaAction>
#include <BrisaUpnp/BrisaService>
#include <Log4Qt/Logger>

// Definitions
#define DATA_SERVICE_TYPE "urn:mira-be:service:Data:1"
#define DATA_SERVICE_ID "urn:mira-be:serviceId:Data:1"
#define DATA_SERVICE_SCPD_FILE ":/descriptions/data_scpd.xml"
#define DATA_SERVICE_SCPD_URL "/urn:mira-be:serviceId:Data:1/scpd.xml"
#define DATA_SERVICE_CONTROL_URL "/urn:mira-be:serviceId:Data:1/control"
#define DATA_SERVICE_EVENT_URL "/urn:mira-be:serviceId:Data:1/eventing"

// Namespaces
using namespace Brisa;  // to prevent the MOC from being confused

namespace MIRA
{
    class DataService : public Brisa::BrisaService
    {
    Q_OBJECT
    public:
        // Construction and destruction
        DataService();

        // Service actions
    private slots:
        BrisaOutArgument* loadinterface(BrisaInArgument* const iArguments, BrisaAction* const iAction);
        BrisaOutArgument* setinterfacelocation(BrisaInArgument* const iArguments, BrisaAction* const iAction);
        BrisaOutArgument* getinterfacerevision(BrisaInArgument* const iArguments, BrisaAction* const iAction);
        BrisaOutArgument* loadmedia(BrisaInArgument* const iArguments, BrisaAction* const iAction);
        BrisaOutArgument* setmedialocation(BrisaInArgument* const iArguments, BrisaAction* const iAction);
        BrisaOutArgument* getmediarevision(BrisaInArgument* const iArguments, BrisaAction* const iAction);

    private:
        // Data members
        Log4Qt::Logger *mLogger;
    };
}

#endif // DATASERVICE_H
