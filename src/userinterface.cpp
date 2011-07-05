//
// Configuration
//

// Local includes
#include "userinterface.h"
#include "mainapplication.h"
#include "userinterface/webpages/logpage.h"

// Library includes
#include <QtCore/QStringList>

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

UserInterface::UserInterface(QWidget *parent) throw(QException) : QMainWindow(parent)
{
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup("UserInterface");

    // Setup logging
    mLogger =  Log4Qt::Logger::logger("UserInterface");
    mLogger->trace() << Q_FUNC_INFO;

    // Setup UI
    mWebView = new QWebView(this);
    setCentralWidget(mWebView);
    showFullScreen();

    // Load debug page
    mWebPage = new LogPage(mWebView);
    mWebView->setPage(mWebPage);
}


//
// Messaging methods
//

void UserInterface::showNotice(const QString& iMessage) const
{
    mWebPage->showNotice(iMessage);
}

void UserInterface::showAlert(const QString& iMessage) const
{
    mWebPage->showAlert(iMessage);
}
