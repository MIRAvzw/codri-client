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
#include <QtOpenGL/QGLWidget>

// Local includes
#include "user/webpages/initpage.h"
#include "user/webpages/errorpage.h"
#include "user/webpages/logpage.h"
#include "user/webpages/presentationpage.h"
#include "user/webpages/statuspage.h"


//
// Construction and destruction
//

Codri::UserInterface::UserInterface(QObject *iParent) throw(QException)
    : QObject(iParent) {
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup(metaObject()->className());

    // Setup logging
    mLogger =  Log4Qt::Logger::logger(metaObject()->className());

    // Configure the instance
    mBrowser = 0;
    mLogger->info() << "Displaying initialization page";
    showInit();
}

void Codri::UserInterface::start() {
}


//
// Public interface
//

// TODO: track current page, do or do not reload (yes on media, no on log)?

void Codri::UserInterface::showInit() {
    //QWebPage *tPageInit = new InitPage(mWebView);
    //mWebView->setPage(tPageInit);
}

void Codri::UserInterface::showLog() {
    //QWebPage *tPageLog = new LogPage(mWebView);
    //mWebView->setPage(tPageLog);
}

void Codri::UserInterface::showStatus() {
    //QWebPage *tPageStatus = new StatusPage(mWebView);
    //mWebView->setPage(tPageStatus);
}

void Codri::UserInterface::showError() {
    //QWebPage *tPageError = new ErrorPage(mWebView);
    //mWebView->setPage(tPageError);
}

void Codri::UserInterface::showPresentation(const QDir& iLocation) {
    mLogger->info() << "Loading presentation from " << iLocation.absolutePath();

    if (mBrowser != 0) {
        mBrowser->kill();
        delete mBrowser;
        mBrowser = 0;
    }

    mBrowser = new QProcess(this);
    QString tExecutable("/usr/bin/google-chrome");
    QStringList tArguments;
    tArguments << "--app=file://" + iLocation.absoluteFilePath("index.html");
    mBrowser->start(tExecutable, tArguments);

    // TODO: is webview specification necessary? Doesn't setpage properly configure the parent?
    //QWebPage *tPagetPresentation = new PresentationPage(iLocation, mWebView);
    //mWebView->setPage(tPagetPresentation);
}

