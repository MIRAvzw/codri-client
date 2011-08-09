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
    Q_OBJECT
    public:
        // Construction and destruction
        explicit LogFacility(QString iSubsystem, QObject* parent = 0);
        ~LogFacility();

        // Specialised loggers
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
        QString mSubsystem;
    };
}

#endif // LOGFACILITY_H
