//
// Configuration
//

// Includes
#include "userinterface.h"
#include <QStringList>
#include "mainapplication.h"
#include "webpage/initpage.h"

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

    // Load debug page
    mWebPage = new InitPage(mWebView);
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
