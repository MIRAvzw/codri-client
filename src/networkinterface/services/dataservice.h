//
// Configuration
//

// Include guard
#ifndef DATASERVICE_H
#define DATASERVICE_H

// Library includes
#include <BrisaUpnp/BrisaAction>
#include <BrisaUpnp/BrisaService>
#include <BrisaUpnp/brisaargument.h>
#include <Log4Qt/Logger>

// Definitions
#define DATA_SERVICE_TYPE "urn:mira-be:service:Data:1"
#define DATA_SERVICE_ID "urn:mira-be:serviceId:Data:1"
#define DATA_SERVICE_XML_PATH "descriptions/data_scpd.xml"
#define DATA_SERVICE_CONTROL "/data/control"
#define DATA_SERVICE_EVENT_SUB "/data/eventing"

class DataService : public Brisa::BrisaService
{
public:
    // Construction and destruction
    DataService();
    virtual ~DataService();

private slots:
    // Service actions
    BrisaOutArgument* LoadInterface(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction);
    BrisaOutArgument* SetInterfaceLocation(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction);
    BrisaOutArgument* GetInterfaceRevision(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction);
    BrisaOutArgument* LoadMedia(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction);
    BrisaOutArgument* SetMediaLocation(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction);
    BrisaOutArgument* GetMediaRevision(BrisaInArgument* const iArguments, Brisa::BrisaAction* const iAction);

    // Data members
    Log4Qt::Logger *mLogger;
};

#endif // DATASERVICE_H
