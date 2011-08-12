//
// Configuration
//

// Local includes
#include "applicationservice.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

ApplicationService::ApplicationService(QObject *iParent) : Brisa::BrisaService(
        APPLICATION_SERVICE_TYPE,
        APPLICATION_SERVICE_ID,
        APPLICATION_SERVICE_SCPD_URL,
        APPLICATION_SERVICE_CONTROL_URL,
        APPLICATION_SERVICE_EVENT_URL,
        QString(),
        iParent)
{
    // Setup logging
    mLogger =  Log4Qt::Logger::logger("ApplicationService");
    mLogger->trace() << Q_FUNC_INFO;

    // Provide the SCPD file path
    setDescriptionFile(APPLICATION_SERVICE_SCPD_FILE);
}


//
// Service methods
//

BrisaOutArgument *ApplicationService::loadmedia(BrisaInArgument *const iArguments, Brisa::BrisaAction *const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;

    iAction->getStateVariable("MediaIdentifier")->setAttribute(Brisa::BrisaStateVariable::Value, iArguments->value("iMediaIdentifierValue"));
    iAction->getStateVariable("MediaLocation")->setAttribute(Brisa::BrisaStateVariable::Value, iArguments->value("iMediaLocationValue"));
    emit loadMedia(iArguments->value("iMediaIdentifierValue"), iArguments->value("iMediaLocationValue"));

    BrisaOutArgument *oArguments = new BrisaOutArgument();
    return oArguments;
}
