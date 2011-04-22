//
// Configuration
//

// Includes
#include "webpage.h"
#include <QtWebKit/QWebFrame>

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

WebPage::WebPage(QUrl iURL, QObject *parent) : QWebPage(parent)
{
    // Setup the webpage
    mainFrame()->addToJavaScriptWindowObject("application", this);
    mainFrame()->load(iURL);

    // Setup logging
    mLogger =  Log4Qt::Logger::logger("WebPage");
    mLogger->trace() << Q_FUNC_INFO;
}

WebPage::~WebPage()
{
}

//
// QWebPage interface
//

void WebPage::javaScriptConsoleMessage(const QString& iMessage, int iLineNumber, const QString& iSourceId)
{
    mLogger->debug() << "Javascript console message at line " << iLineNumber << " of " << iSourceId << ": " << iMessage;
}
