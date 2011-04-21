//
// Configuration
//

// Includes
#include "debugpage.h"
#include <QtWebKit/QWebFrame>
#include "simplelayout.h"
#include "mainapplication.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

DebugPage::DebugPage(QObject *parent) : QWebPage(parent)
{
    // Setup the webpage
    mainFrame()->addToJavaScriptWindowObject("DebugInterface", this);
    mainFrame()->load(QUrl("qrc:/webpages/debug.html"));

    // Setup logging
    mLogger =  Log4Qt::Logger::logger("DebugPage");
    mLogger->trace() << Q_FUNC_INFO;

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
    return MainApplication::instance()->id();
}


//
// QWebPage interface
//

void DebugPage::javaScriptConsoleMessage(const QString& iMessage, int iLineNumber, const QString& iSourceId)
{
    mLogger->debug() << "Javascript console message at line " << iLineNumber << " of " << iSourceId << ": " << iMessage;
}
