/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef USER_WEBPAGES_LOGPAGE_H_
#define USER_WEBPAGES_LOGPAGE_H_

// Library includes
#include <QtCore/QObject>
#include <log4qt/SignalAppender>
#include <log4qt/Layout>

// Local incudes
#include "user/webpage.h"

namespace Codri {
    class LogPage : public WebPage {
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

#endif  // USER_WEBPAGES_LOGPAGE_H_
