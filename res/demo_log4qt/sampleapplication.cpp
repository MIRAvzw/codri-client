#include "sampleapplication.h"

#include "log4qt/consoleappender.h"
#include "log4qt/logger.h"
#include "log4qt/ttcclayout.h"
#include "log4qt/logmanager.h"

SampleApplication::SampleApplication(QObject *parent) : QObject(parent)
{
    //
    // Global logger configuration
    //

    Log4Qt::LogManager::rootLogger();
    Log4Qt::TTCCLayout *p_layout = new Log4Qt::TTCCLayout();
    p_layout->setName(QString("My layout"));
    p_layout->activateOptions();
    p_layout->setDateFormat(Log4Qt::TTCCLayout::ISO8601);

    Log4Qt::ConsoleAppender *p_appender = new Log4Qt::ConsoleAppender(p_layout, Log4Qt::ConsoleAppender::STDOUT_TARGET);
    p_appender->setName(QString("My Appender"));
    p_appender->activateOptions();

    Log4Qt::Logger::rootLogger()->addAppender(p_appender);
}

void SampleApplication::run()
{    
    Log4Qt::Logger::logger(QString("main"))->info("Hello World!");
    emit done();
}
