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
    // Set-up the root logger
    mSubsystem = iSubsystem;
    if (mSubsystem == "main")
    {
        // Create objects
        Log4Qt::ConsoleAppender *tLogAppender = new Log4Qt::ConsoleAppender(this);
        Log4Qt::TTCCLayout *tLogLayout = new Log4Qt::TTCCLayout(this);

        // Configure layout
        tLogLayout->setDateFormat(Log4Qt::TTCCLayout::ISO8601);

        // Configure appender
        tLogAppender->setTarget(Log4Qt::ConsoleAppender::STDOUT_TARGET);
        tLogAppender->setLayout(tLogLayout);
        tLogAppender->activateOptions();

        // Configure root logger
        Log4Qt::LogManager::rootLogger()->addAppender(tLogAppender);
    }

    // Create a new Log4Qt logger
    mLogger = Log4Qt::Logger::logger(iSubsystem);
}

LogFacility::~LogFacility()
{
    if (mSubsystem == "main")
    {
        Log4Qt::LogManager::rootLogger()->removeAllAppenders();
    }
}
