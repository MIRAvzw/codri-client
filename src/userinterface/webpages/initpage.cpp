//
// Configuration
//

// Local includes
#include "initpage.h"
#include "mainapplication.h"

// Library includes
#include <Log4Qt/SimpleLayout>

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

InitPage::InitPage(QObject *parent) : WebPage(QUrl("qrc:/webpages/initpage.html"), parent)
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

InitPage::~InitPage()
{
    qDebug() << "DESTROY";
    Log4Qt::Logger::rootLogger()->removeAppender(mLogAppender);
}


//
// Basic I/O
//

QString InitPage::id() const
{
    return MainApplication::instance()->uuid();
}
