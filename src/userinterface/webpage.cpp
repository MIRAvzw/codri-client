//
// Configuration
//

// Local includes
#include "webpage.h"

// Library includes
#include <QtWebKit/QWebFrame>

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

WebPage::WebPage(const QUrl &iURL, QObject *iParent) : QWebPage(iParent)
{
    // Setup the webpage
    mainFrame()->addToJavaScriptWindowObject("application", this);
    mFallback = iURL;
    loadFallback();

    // Setup logging
    mLogger =  Log4Qt::Logger::logger("WebPage");
    mLogger->trace() << Q_FUNC_INFO;
}

WebPage::~WebPage()
{
}


//
// Functionality
//

void WebPage::load(const QUrl &iUrl)
{
    mainFrame()->load(iUrl);
}

void WebPage::loadFallback()
{
    load(mFallback);
}

//
// QWebPage interface
//

void WebPage::javaScriptConsoleMessage(const QString &iMessage, int iLineNumber, const QString &iSourceId)
{
    mLogger->debug() << "Javascript console message at line " << iLineNumber << " of " << iSourceId << ": " << iMessage;
}
