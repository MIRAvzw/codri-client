/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Local includes
#include "userinterface.h"
#include "userinterface/webpages/initpage.h"
#include "userinterface/webpages/errorpage.h"
#include "userinterface/webpages/logpage.h"
#include "userinterface/webpages/presentationpage.h"
#include "userinterface/webpages/statuspage.h"

// Library includes
#include <QtCore/QStringList>


//
// Construction and destruction
//

Codri::UserInterface::UserInterface(QWidget *iParent) throw(QException) : QMainWindow(iParent)
{
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup("UserInterface");

    // Setup logging
    mLogger =  Log4Qt::Logger::logger(metaObject()->className());

    // Setup UI
    mWebView = new QWebView(this);
    mWebView->installEventFilter(this);
    setCentralWidget(mWebView);
    setWindowState(windowState() | Qt::WindowFullScreen);

    // Configure the webview
    mLogger->debug() << "Showing initialization page";
    showInit();
    connect(mWebView, SIGNAL(loadFinished(bool)), this, SLOT(_loadFinished(bool)));
    connect(mWebView, SIGNAL(loadProgress(int)), this, SLOT(_loadProgress(int)));
}


//
// Functionality
//

// TODO: track current page, do or do not reload (yes on media, no on log)?

void Codri::UserInterface::showInit()
{
    QWebPage *tPageInit = new InitPage(mWebView);
    mWebView->setPage(tPageInit);
}

void Codri::UserInterface::showLog()
{
    QWebPage *tPageLog = new LogPage(mWebView);
    mWebView->setPage(tPageLog);
}

void Codri::UserInterface::showStatus()
{
    QWebPage *tPageStatus = new StatusPage(mWebView);
    mWebView->setPage(tPageStatus);
}

void Codri::UserInterface::showError(const QString& iError)
{
    // TODO: load the error in the page

    QWebPage *tPageError = new ErrorPage(mWebView);
    mWebView->setPage(tPageError);
}

void Codri::UserInterface::showPresentation(const QDir& iLocation)
{
    // TODO: is webview specification necessary? Doesn't setpage properly configure the parent?
    QWebPage *tPagetPresentation = new PresentationPage(iLocation, mWebView);
    mWebView->setPage(tPagetPresentation);
}


//
// UI events
//

bool Codri::UserInterface::eventFilter(QObject *iObject, QEvent *iEvent)
{
    if (iEvent->type() == QEvent::KeyPress) {
        QKeyEvent *iKeyEvent = static_cast<QKeyEvent*>(iEvent);
        switch (iKeyEvent->key()) {
        // Default passthrough keys
        case Qt::Key_Left:
        case Qt::Key_Right:
        case Qt::Key_Return:
        case Qt::Key_Backspace:
            return false;
            break;

        // Status page
        case Qt::Key_1:
            showStatus();
            return true;
            break;

        // Log page
        case Qt::Key_2:
            showLog();
            return true;
            break;

        // Default case
        default:
            return QObject::eventFilter(iObject, iEvent);
            break;
        }

        return false;
    } else {
        // standard event processing
        return QObject::eventFilter(iObject, iEvent);
    }
}


//
// Slots
//

void Codri::UserInterface::_loadFinished(bool iOk)
{
    if (iOk)
        return;

    // Media page handling
    if (mWebView->page() == 0) {  // TODO: track
        showError("unknown error");
        emit presentationError("unknown error");
    } else {
        // TODO: emit fatal error (we can't trust on loading the error page)
        mLogger->error("WebView error on internal webpage");
    }
}

void Codri::UserInterface::_loadProgress(int iProgress)
{
    // TODO: relay to initpage
}
