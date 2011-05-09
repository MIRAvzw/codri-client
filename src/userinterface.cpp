//
// Configuration
//

// Local includes
#include "userinterface.h"
#include "mainapplication.h"
#include "userinterface/webpages/initpage.h"

// Library includes
#include <QtCore/QStringList>

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

UserInterface::UserInterface(QWidget *parent) : QMainWindow(parent)
{
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup("UserInterface");

    // Setup logging
    mLogger =  Log4Qt::Logger::logger("UserInterface");
    mLogger->trace() << Q_FUNC_INFO;

    // Set member data pointers
    mWebView = 0;
    mWebPage = 0;
}


//
// Subsystem interface
//

void UserInterface::init() throw(QException)
{
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
