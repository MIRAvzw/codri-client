//
// Configuration
//

// Include guard
#ifndef DEBUGPAGE_H
#define DEBUGPAGE_H

// Library includes
#include <QtCore/QObject>
#include <Log4Qt/SignalAppender>
#include <Log4Qt/Layout>

// Local incudes
#include "userinterface/webpage.h"

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
