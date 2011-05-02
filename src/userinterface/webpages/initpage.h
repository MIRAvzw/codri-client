//
// Configuration
//

// Include guard
#ifndef INITPAGE_H
#define INITPAGE_H

// Library includes
#include <QtCore/QObject>
#include <Log4Qt/SignalAppender>
#include <Log4Qt/Layout>

// Local incudes
#include "userinterface/webpage.h"

namespace MIRA
{
    class InitPage : public WebPage
    {
    Q_OBJECT
    Q_PROPERTY(QString id READ id CONSTANT)
    public:
        // Construction and destruction
        InitPage(QObject* parent = 0);
        ~InitPage();

        // Basic I/O
    public:
        QString id() const;

    signals:
        void newMessage(const QString& iMessage);

    private:
        Log4Qt::Layout* mLogLayout;
        Log4Qt::SignalAppender* mLogAppender;
    };
}

#endif // INITPAGE_H
