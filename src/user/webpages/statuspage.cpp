/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "statuspage.h"

// Library includes
#include <Log4Qt/SimpleLayout>

// Local includes
#include "mainapplication.h"


//
// Construction and destruction
//

Codri::StatusPage::StatusPage(QObject *iParent)
    : WebPage(QUrl("qrc:/webpages/statuspage.html"), iParent)
{
    // Create log layout
    mLogLayout = new Log4Qt::SimpleLayout(this);
    mLogLayout->activateOptions();

    // Create log appender
    mLogAppender = new Log4Qt::SignalAppender(this);
    mLogAppender->setLayout(mLogLayout);
    connect(mLogAppender, SIGNAL(appended(QString)), this, SIGNAL(newMessage(QString)));

    // Register log appender
    Log4Qt::Logger::rootLogger()->addAppender(mLogAppender);
}

Codri::StatusPage::~StatusPage()
{
    Log4Qt::Logger::rootLogger()->removeAppender(mLogAppender);
}


//
// Basic I/O
//

QString Codri::StatusPage::id() const
{
    return MainApplication::instance()->kiosk()->getUuid();
}

QDateTime Codri::StatusPage::startup() const
{
    return MainApplication::instance()->controller()->startup();
}
