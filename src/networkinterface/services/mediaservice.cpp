//
// Configuration
//

// Local includes
#include "mediaservice.h"
#include "mainapplication.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

MediaService::MediaService(QObject *iParent) : Brisa::BrisaService(
        MEDIA_SERVICE_TYPE,
        MEDIA_SERVICE_ID,
        MEDIA_SERVICE_SCPD_URL,
        MEDIA_SERVICE_CONTROL_URL,
        MEDIA_SERVICE_EVENT_URL,
        QString(),
        iParent)
{
    // Setup logging
    mLogger =  Log4Qt::Logger::logger("MediaService");
    mLogger->trace() << Q_FUNC_INFO;

    // Provide the SCPD file path
    setDescriptionFile(MEDIA_SERVICE_SCPD_FILE);
}


//
// Service methods
//

BrisaOutArgument *MediaService::getrevision(BrisaInArgument *const iArguments, Brisa::BrisaAction *const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;
    Q_UNUSED(iArguments)
    Q_UNUSED(iAction)

    BrisaOutArgument *oArguments = new BrisaOutArgument();
    oArguments->insert("oRevisionValue", QString::number(MainApplication::instance()->controller()->media().Revision));
    return oArguments;
}

BrisaOutArgument *MediaService::getlocation(BrisaInArgument *const iArguments, Brisa::BrisaAction *const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;
    Q_UNUSED(iArguments)
    Q_UNUSED(iAction)

    BrisaOutArgument *oArguments = new BrisaOutArgument();
    oArguments->insert("oLocationValue", MainApplication::instance()->controller()->media().Location.toString());
    return oArguments;
}

BrisaOutArgument *MediaService::setlocation(BrisaInArgument *const iArguments, Brisa::BrisaAction *const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;

    iAction->getStateVariable("Location")->setAttribute(Brisa::BrisaStateVariable::Value, iArguments->value("iLocationValue"));
    emit setLocation(iArguments->value("iLocationValue"));

    BrisaOutArgument *oArguments = new BrisaOutArgument();
    return oArguments;
}
