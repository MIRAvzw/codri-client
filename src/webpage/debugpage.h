//
// Configuration
//

// Include guard
#ifndef DEBUGPAGE_H
#define DEBUGPAGE_H

// System includes
#include <QObject>
#include <QtWebKit/QWebPage>

// Local incudes
#include "logger.h"
#include "signalappender.h"
#include "layout.h"

namespace MIRA
{
    class DebugPage : public QWebPage
    {
    Q_OBJECT
    Q_PROPERTY(QString id READ id CONSTANT)
    public:
        // Construction and destruction
        DebugPage(QObject* parent = 0);
        ~DebugPage();

        // Basic I/O
    public:
        QString id() const;

    signals:
        void newMessage(const QString& iMessage);

        // QWebPage interface
    protected:
        void javaScriptConsoleMessage(const QString& iMessage, int iLineNumber, const QString& iSourceId);

    private:
        Log4Qt::Logger *mLogger;
        Log4Qt::Layout* mLogLayout;
        Log4Qt::SignalAppender* mLogAppender;
    };
}

#endif // DEBUGPAGE_H
