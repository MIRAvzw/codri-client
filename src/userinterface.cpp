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
    if (mBrowser != 0) {
        mBrowser->kill();
        delete mBrowser;
        mBrowser = 0;
    }

    //QWebPage *tPageInit = new InitPage(mWebView);
    //mWebView->setPage(tPageInit);
}

void Codri::UserInterface::showLog() {
    if (mBrowser != 0) {
        mBrowser->kill();
        delete mBrowser;
        mBrowser = 0;
    }

    //QWebPage *tPageLog = new LogPage(mWebView);
    //mWebView->setPage(tPageLog);
}

void Codri::UserInterface::showStatus() {
    if (mBrowser != 0) {
        mBrowser->kill();
        delete mBrowser;
        mBrowser = 0;
    }

    //QWebPage *tPageStatus = new StatusPage(mWebView);
    //mWebView->setPage(tPageStatus);
}

void Codri::UserInterface::showError() {
    if (mBrowser != 0) {
        mBrowser->kill();
        delete mBrowser;
        mBrowser = 0;
    }

    //QWebPage *tPageError = new ErrorPage(mWebView);
    //mWebView->setPage(tPageError);
}

void Codri::UserInterface::showPresentation(const QDir& iLocation) {
    if (mBrowser != 0) {
        mBrowser->kill();
        delete mBrowser;
        mBrowser = 0;
    }

    mLogger->info() << "Loading presentation from " << iLocation.absolutePath();
    mBrowser = new QProcess(this);
    QString tExecutable("/usr/bin/chromium");
    QStringList tArguments;
    tArguments << "--kiosk"
               << "--disable-web-security"
               << "--auto-launch-at-startup"
               << "--disable-session-storage"
               << "--no-first-run"
               << "--no-default-browser-check"
               << "--disable-restore-background-contents"
               << "file://" + iLocation.absoluteFilePath("index.html");
    mBrowser->start(tExecutable, tArguments);
}

