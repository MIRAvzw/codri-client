/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef USERINTERFACE_WEBPAGES_LOGPAGE_H_
#define USERINTERFACE_WEBPAGES_LOGPAGE_H_

// Library includes
#include <QtCore/QObject>
#include <Log4Qt/SignalAppender>
#include <Log4Qt/Layout>

// Local incudes
#include "user/webpage.h"

namespace Codri
{
    class LogPage : public WebPage
    {
    Q_OBJECT
    Q_PROPERTY(QString id READ id CONSTANT)
    public:
        // Construction and destruction
        explicit LogPage(QObject *iParent);
        ~LogPage();

        // Basic I/O
    public:
        QString id() const;

    signals:
        void newMessage(const QString &iMessage);

    private:
        Log4Qt::Layout *mLogLayout;
        Log4Qt::SignalAppender *mLogAppender;
    };
}

#endif  // USERINTERFACE_WEBPAGES_LOGPAGE_H_
