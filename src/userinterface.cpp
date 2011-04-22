//
// Configuration
//

// Includes
#include "userinterface.h"
#include <QStringList>
#include "mainapplication.h"
#include "webpage/messagepage.h"

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
    mWebPage = new MessagePage(mWebView);
    mWebView->setPage(mWebPage);
}
