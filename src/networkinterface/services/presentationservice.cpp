//
// Configuration
//

// Local includes
#include "presentationservice.h"
#include "mainapplication.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

PresentationService::PresentationService(QObject *iParent) : Brisa::BrisaService(
        PRESENTATION_SERVICE_TYPE,
        PRESENTATION_SERVICE_ID,
        PRESENTATION_SERVICE_SCPD_URL,
        PRESENTATION_SERVICE_CONTROL_URL,
        PRESENTATION_SERVICE_EVENT_URL,
        QString(),
        iParent)
{
    // Setup logging
    mLogger =  Log4Qt::Logger::logger("PresentationService");
    mLogger->trace() << Q_FUNC_INFO;

    // Provide the SCPD file path
    setDescriptionFile(PRESENTATION_SERVICE_SCPD_FILE);
}


//
// Service methods
//

BrisaOutArgument *PresentationService::getrevision(BrisaInArgument *const iArguments, Brisa::BrisaAction *const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;
    Q_UNUSED(iArguments)
    Q_UNUSED(iAction)

    BrisaOutArgument *oArguments = new BrisaOutArgument();
    oArguments->insert("oRevisionValue", QString::number(MainApplication::instance()->controller()->presentation().Revision));
    return oArguments;
}

BrisaOutArgument *PresentationService::getlocation(BrisaInArgument *const iArguments, Brisa::BrisaAction *const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;
    Q_UNUSED(iArguments)
    Q_UNUSED(iAction)

    BrisaOutArgument *oArguments = new BrisaOutArgument();
    oArguments->insert("oLocationValue", MainApplication::instance()->controller()->presentation().Location.toString());
    return oArguments;
}

BrisaOutArgument *PresentationService::setlocation(BrisaInArgument *const iArguments, Brisa::BrisaAction *const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;

    iAction->getStateVariable("Location")->setAttribute(Brisa::BrisaStateVariable::Value, iArguments->value("iLocationValue"));
    emit setLocation(iArguments->value("iLocationValue"));

    BrisaOutArgument *oArguments = new BrisaOutArgument();
    return oArguments;
}
