/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "userinterface.h"

// Library includes
#include <QtCore/QStringList>

// Local includes
#include "user/webpages/initpage.h"
#include "user/webpages/errorpage.h"
#include "user/webpages/logpage.h"
#include "user/webpages/presentationpage.h"
#include "user/webpages/statuspage.h"


//
// Construction and destruction
//

Codri::UserInterface::UserInterface(QWidget *iParent) throw(QException)
    : QMainWindow(iParent) {
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup(metaObject()->className());

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
}


//
// Public interface
//

// TODO: track current page, do or do not reload (yes on media, no on log)?

void Codri::UserInterface::showInit() {
    QWebPage *tPageInit = new InitPage(mWebView);
    mWebView->setPage(tPageInit);
}

void Codri::UserInterface::showLog() {
    QWebPage *tPageLog = new LogPage(mWebView);
    mWebView->setPage(tPageLog);
}

void Codri::UserInterface::showStatus() {
    QWebPage *tPageStatus = new StatusPage(mWebView);
    mWebView->setPage(tPageStatus);
}

void Codri::UserInterface::showError() {
    QWebPage *tPageError = new ErrorPage(mWebView);
    mWebView->setPage(tPageError);
}

void Codri::UserInterface::showPresentation(const QDir& iLocation) {
    // TODO: is webview specification necessary? Doesn't setpage properly configure the parent?
    QWebPage *tPagetPresentation = new PresentationPage(iLocation, mWebView);
    mWebView->setPage(tPagetPresentation);
}


//
// UI events
//

bool Codri::UserInterface::eventFilter(QObject *iObject, QEvent *iEvent) {
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
        // Standard event processing
        return QObject::eventFilter(iObject, iEvent);
    }
}


//
// Internal slots
//

void Codri::UserInterface::_loadFinished(bool iOk) {
    if (iOk)
        return;

    // Media page handling
    if (mWebView->page() == 0) {
        mLogger->error() << "Unable to load the webpage";
        showError();
        emit runtimeFailure();
    } else {
        mLogger->warn() << "Errors detected while loading the webpage";
    }
}

