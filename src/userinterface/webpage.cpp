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

    // Setup logging
    mLogger =  Log4Qt::Logger::logger("WebPage");
    mLogger->trace() << Q_FUNC_INFO;

    // Load the contents
    mainFrame()->load(iURL);
}

WebPage::~WebPage()
{
}


//
// QWebPage interface
//

void WebPage::javaScriptConsoleMessage(const QString &iMessage, int iLineNumber, const QString &iSourceId)
{
    mLogger->debug() << "Javascript console message at line " << iLineNumber << " of " << iSourceId << ": " << iMessage;
}
