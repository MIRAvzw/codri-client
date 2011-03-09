//
// Configuration
//

// Include guard
#ifndef LOGFACILITY_H
#define LOGFACILITY_H

// System includes
#include <QtCore/QObject>

// Local includes
#include "logger.h"
#include "logstream.h"

namespace MIRA
{
    class LogFacility : public QObject
    {
    public:
        // Construction and destruction
        LogFacility(QString iSubsystem, QObject* parent = 0) : QObject(parent)
        {
            mLogger = Log4Qt::Logger::logger(iSubsystem);
        }

        // GettersLog4Qt::Logger::logger(iSubsystem)
        inline LogStream trace() {
            return LogStream(*mLogger, LogStream::TRACE);
        }
        inline LogStream debug() {
            return LogStream(*mLogger, LogStream::DEBUG);
        }
        inline LogStream info() {
            return LogStream(*mLogger, LogStream::INFO);
        }
        inline LogStream warn() {
            return LogStream(*mLogger, LogStream::WARN);
        }
        inline LogStream error() {
            return LogStream(*mLogger, LogStream::ERROR);
        }
        inline LogStream fatal() {
            return LogStream(*mLogger, LogStream::FATAL);
        }
    private:
        Log4Qt::Logger *mLogger;
    };
}

#endif // LOGFACILITY_H
