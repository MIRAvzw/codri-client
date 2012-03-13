/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef USERINTERFACE_WEBPAGES_STATUSPAGE_H_
#define USERINTERFACE_WEBPAGES_STATUSPAGE_H_

// Library includes
#include <QtCore/QObject>
#include <Log4Qt/SignalAppender>
#include <Log4Qt/Layout>

// Local incudes
#include "user/webpage.h"

namespace Codri {
    class StatusPage : public WebPage {
    Q_OBJECT
    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(QDateTime startup READ startup CONSTANT)
    public:
        // Construction and destruction
        explicit StatusPage(QObject *iParent);
        ~StatusPage();

        // Basic I/O
    public:
        QString id() const;
        QDateTime startup() const;

    signals:
        void newMessage(const QString &iMessage);

    private:
        Log4Qt::Layout *mLogLayout;
        Log4Qt::SignalAppender *mLogAppender;
    };
}

#endif  // USERINTERFACE_WEBPAGES_STATUSPAGE_H_