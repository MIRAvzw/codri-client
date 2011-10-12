//
// Configuration
//

// Local includes
#include "configurationservice.h"
#include "mainapplication.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

ConfigurationService::ConfigurationService(QObject *iParent) : Brisa::BrisaService(
        CONFIGURATION_SERVICE_TYPE,
        CONFIGURATION_SERVICE_ID,
        CONFIGURATION_SERVICE_SCPD_URL,
        CONFIGURATION_SERVICE_CONTROL_URL,
        CONFIGURATION_SERVICE_EVENT_URL,
        QString(),
        iParent)
{
    // Setup logging
    mLogger =  Log4Qt::Logger::logger("ConfigurationService");
    mLogger->trace() << Q_FUNC_INFO;

    // Provide the SCPD file path
    setDescriptionFile(CONFIGURATION_SERVICE_SCPD_FILE);
}


//
// Service methods
//


BrisaOutArgument *ConfigurationService::getrevision(BrisaInArgument *const iArguments, BrisaAction *const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;
    Q_UNUSED(iArguments)
    Q_UNUSED(iAction)

    BrisaOutArgument *oArguments = new BrisaOutArgument();
    oArguments->insert("oRevisionValue", QString::number(MainApplication::instance()->controller()->configuration().Revision));
    return oArguments;
}

BrisaOutArgument *ConfigurationService::setrevision(BrisaInArgument *const iArguments, BrisaAction *const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;

    iAction->getStateVariable("Revision")->setAttribute(Brisa::BrisaStateVariable::Value, iArguments->value("iRevisionValue"));
    emit setRevision(atol(iArguments->value("iRevisionValue").toStdString().c_str()));

    BrisaOutArgument *oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument *ConfigurationService::shutdown(BrisaInArgument *const iArguments, Brisa::BrisaAction *const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;
    Q_UNUSED(iAction)
    Q_UNUSED(iArguments)

    emit shutdown();

    BrisaOutArgument *oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument *ConfigurationService::reboot(BrisaInArgument *const iArguments, Brisa::BrisaAction *const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;
    Q_UNUSED(iArguments)
    Q_UNUSED(iAction)

    emit reboot();

    BrisaOutArgument *oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument *ConfigurationService::echo(BrisaInArgument *const iArguments, Brisa::BrisaAction *const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;

    iAction->getStateVariable("Echo")->setAttribute(Brisa::BrisaStateVariable::Value, iArguments->value("iEchoValue"));
    emit echo(iArguments->value("iEchoValue"));

    BrisaOutArgument *oArguments = new BrisaOutArgument();
    oArguments->insert("oEchoValue", iAction->getStateVariable("Echo")->getAttribute(Brisa::BrisaStateVariable::Value));
    return oArguments;
}

BrisaOutArgument *ConfigurationService::setvolume(BrisaInArgument *const iArguments, Brisa::BrisaAction *const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;

    iAction->getStateVariable("Volume")->setAttribute(Brisa::BrisaStateVariable::Value, iArguments->value("iVolumeValue"));
    emit setVolume(iArguments->value("iVolumeValue").toInt());

    BrisaOutArgument *oArguments = new BrisaOutArgument();
    return oArguments;
}

BrisaOutArgument *ConfigurationService::getvolume(BrisaInArgument *const iArguments, Brisa::BrisaAction *const iAction)
{
    mLogger->trace() << Q_FUNC_INFO;
    Q_UNUSED(iArguments)

    BrisaOutArgument *oArguments = new BrisaOutArgument();
    oArguments->insert("oVolumeValue", iAction->getStateVariable("Volume")->getAttribute(Brisa::BrisaStateVariable::Value));
    return oArguments;
}
