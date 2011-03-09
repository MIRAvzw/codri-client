#ifndef LOGSTREAM_H
//
// Configuration
//

// Include guard
#define LOGSTREAM_H

// System includes
#include <QtCore/QTextStream>
#include <QtCore/QString>

// Local includes
#include "logger.h"

namespace MIRA
{
    class LogStream
    {
    private:
        // Auxiliary structs
        struct Stream {
            Stream() : ts(&buffer, QIODevice::WriteOnly), ref(1) {}
            QTextStream ts;
            QString buffer;
            int ref;
        } *stream;

    public:
        // Public enum
        enum Level {
            TRACE,
            DEBUG,
            INFO,
            WARN,
            ERROR,
            FATAL
        };

        // Construction and destruction
        inline LogStream(Log4Qt::Logger& iLogger, LogStream::Level iLevel = INFO) : stream(new Stream()),  mLogger(iLogger), mLevel(iLevel)
        {
        }
        inline LogStream(const LogStream &o):stream(o.stream),mLogger(o.mLogger),mLevel(o.mLevel)
        {
            ++stream->ref;
        }
        ~LogStream()
        {
            if (!--stream->ref) {
                switch (mLevel)
                {
                case TRACE:
                    mLogger.trace(stream->buffer);
                    break;
                case DEBUG:
                    mLogger.debug(stream->buffer);
                    break;
                case INFO:
                    mLogger.info(stream->buffer);
                    break;
                case WARN:
                    mLogger.warn(stream->buffer);
                    break;
                case ERROR:
                    mLogger.error(stream->buffer);
                    break;
                case FATAL:
                    mLogger.fatal(stream->buffer);
                    break;
                }
                delete stream;
            }
        }

        // Stream operators
        inline LogStream &operator<<(QChar t) { stream->ts << '\'' << t << '\''; return *this; }
        inline LogStream &operator<<(QBool t) { stream->ts << (bool(t != 0) ? "true" : "false"); return *this; }
        inline LogStream &operator<<(bool t) { stream->ts << (t ? "true" : "false"); return *this; }
        inline LogStream &operator<<(char t) { stream->ts << t; return *this; }
        inline LogStream &operator<<(signed short t) { stream->ts << t; return *this; }
        inline LogStream &operator<<(unsigned short t) { stream->ts << t; return *this; }
        inline LogStream &operator<<(signed int t) { stream->ts << t; return *this; }
        inline LogStream &operator<<(unsigned int t) { stream->ts << t; return *this; }
        inline LogStream &operator<<(signed long t) { stream->ts << t; return *this; }
        inline LogStream &operator<<(unsigned long t) { stream->ts << t; return *this; }
        inline LogStream &operator<<(qint64 t) { stream->ts << QString::number(t); return *this; }
        inline LogStream &operator<<(quint64 t) { stream->ts << QString::number(t); return *this; }
        inline LogStream &operator<<(float t) { stream->ts << t; return *this; }
        inline LogStream &operator<<(double t) { stream->ts << t; return *this; }
        inline LogStream &operator<<(const char* t) { stream->ts << QString::fromAscii(t); return *this; }
        inline LogStream &operator<<(const QString & t) { stream->ts << '\"' << t  << '\"'; return *this; }
        inline LogStream &operator<<(const QStringRef & t) { return operator<<(t.toString()); }
        inline LogStream &operator<<(const QLatin1String &t) { stream->ts << '\"'  << t.latin1() << '\"'; return *this; }
        inline LogStream &operator<<(const QByteArray & t) { stream->ts  << '\"' << t << '\"'; return *this; }
        inline LogStream &operator<<(const void * t) { stream->ts << t; return *this; }
        inline LogStream &operator<<(QTextStreamFunction f) { stream->ts << f; return *this; }
        inline LogStream &operator<<(QTextStreamManipulator m) { stream->ts << m; return *this; }

    private:
        // Data members
        Log4Qt::Logger& mLogger;
        Level mLevel;
    };
}

#endif // LOGSTREAM_H
