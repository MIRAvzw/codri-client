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
#include "auxiliary/fileutils.h"

// Stringification macro
#define QUOTE(str) #str
#define EXPAND_AND_QUOTE(str) QUOTE(str)


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

    // Use data directory
    mUserData = QDir(mSettings->value("datadir", "/tmp/chromium").toString());
    if (!mUserData.exists())
        mUserData.mkpath(mUserData.absolutePath());

    // Configure the instance
    mApplication = 0;
    mLogger->info() << "Displaying initialization page";
    showInit();
}

void Codri::UserInterface::start() {
}


//
// Public interface
//

void Codri::UserInterface::showInit() {
    if (mApplication != 0) {
        mApplication->kill();
        delete mApplication;
        mApplication = 0;
    }

    load(QString("file://%1/initpage.html").arg(EXPAND_AND_QUOTE(DATADIR)));
}

void Codri::UserInterface::showError() {
    if (mApplication != 0) {
        mApplication->kill();
        delete mApplication;
        mApplication = 0;
    }

    load(QString("file://%1/errorpage.html").arg(EXPAND_AND_QUOTE(DATADIR)));
}

void Codri::UserInterface::showPresentation(const QDir& iLocation) {
    if (mApplication != 0) {
        mApplication->kill();
        delete mApplication;
        mApplication = 0;
    }

    mLogger->info() << "Loading presentation from " << iLocation.absolutePath();
    load("file://" + iLocation.absoluteFilePath("index.html"));
}


//
// Auxiliary
//

void Codri::UserInterface::load(const QString& iUrl) {
    // Clean user data dir
    FileUtils::removeDirectory(mUserData);
    mUserData.mkdir(mUserData.absolutePath());
    
    // Start executable
    mApplication = new QProcess(this);
    QString tExecutable("/usr/bin/chromium");
    QStringList tArguments;
    tArguments << "--kiosk"
               << "--disable-web-security"
               << "--auto-launch-at-startup"
               << "--disable-session-storage"
               << "--no-first-run"
               << "--no-default-browser-check"
               << "--disable-restore-background-contents"
               << "--disable-restore-session-state"
               << QString("--user-data-dir=%1").arg(mUserData.absolutePath())
               << iUrl;
    mApplication->start(tExecutable, tArguments);

}
