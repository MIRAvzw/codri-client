/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Local includes
#include "webpage.h"

// Library includes
#include <QtWebKit/QWebFrame>


//
// Construction and destruction
//

Codri::WebPage::WebPage(const QUrl &iURL, QObject *iParent) : QWebPage(iParent)
{
    // Setup the webpage
    mainFrame()->addToJavaScriptWindowObject("application", this);

    // Setup logging
    mLogger =  Log4Qt::Logger::logger(metaObject()->className());

    // Load the contents
    mainFrame()->load(iURL);
}

Codri::WebPage::~WebPage()
{
}


//
// QWebPage interface
//

void Codri::WebPage::javaScriptConsoleMessage(const QString &iMessage, int iLineNumber, const QString &iSourceId)
{
    mLogger->debug() << "Javascript console message at line " << iLineNumber << " of " << iSourceId << ": " << iMessage;
}
