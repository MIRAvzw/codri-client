//
// Configuration
//

// Includes
#include "logfacility.h"
#include "consoleappender.h"
#include "ttcclayout.h"
#include "logmanager.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//


LogFacility::LogFacility(QString iSubsystem, QObject* parent) : QObject(parent)
{
    // Create a new Log4Qt logger
    mLogger = Log4Qt::Logger::logger(iSubsystem);
}

LogFacility::~LogFacility()
{
}
