/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef USERINTERFACE_WEBPAGE_H_
#define USERINTERFACE_WEBPAGE_H_

// Library includes
#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtWebKit/QWebPage>
#include <Log4Qt/Logger>

namespace Codri
{
    class WebPage : public QWebPage
    {
    Q_OBJECT
    public:
        // Construction and destruction
        explicit WebPage(const QUrl &iURL, QObject *iParent);
        virtual ~WebPage();

        // Functionality
        void load(const QUrl &iUrl);

        // QWebPage interface
    protected:
        void javaScriptConsoleMessage(const QString &iMessage, int iLineNumber, const QString &iSourceId);

    protected:
        Log4Qt::Logger *mLogger;
    };
}

#endif  // USERINTERFACE_WEBPAGE_H_
