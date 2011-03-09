#include "logfacility.h"

using namespace MIRA;

LogFacility::LogFacility(QString iSubsystem)
{
    mLogger = Log4Qt::Logger::logger(iSubsystem);
}
