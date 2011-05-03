//
// Configuration
//

// Local includes
#include "debugpage.h"
#include "mainapplication.h"

// Library includes
#include <Log4Qt/SimpleLayout>

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

DebugPage::DebugPage(QObject *parent) : WebPage(QUrl("qrc:/webpages/debug.html"), parent)
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

DebugPage::~DebugPage()
{
    Log4Qt::Logger::rootLogger()->removeAppender(mLogAppender);
}


//
// Basic I/O
//

QString DebugPage::id() const
{
    return MainApplication::instance()->uuid();
}

QDateTime DebugPage::startup() const
{
    return MainApplication::instance()->startup();
}
