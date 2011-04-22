//
// Configuration
//

// Include guard
#ifndef DEBUGPAGE_H
#define DEBUGPAGE_H

// System includes
#include <QObject>

// Local incudes
#include "webpage.h"
#include "logger.h"
#include "signalappender.h"
#include "layout.h"

namespace MIRA
{
    class DebugPage : public WebPage
    {
    Q_OBJECT
    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(QDateTime startup READ startup CONSTANT)
    public:
        // Construction and destruction
        DebugPage(QObject* parent = 0);
        ~DebugPage();

        // Basic I/O
    public:
        QString id() const;
        QDateTime startup() const;

    signals:
        void newMessage(const QString& iMessage);

    private:
        Log4Qt::Layout* mLogLayout;
        Log4Qt::SignalAppender* mLogAppender;
    };
}

#endif // DEBUGPAGE_H
