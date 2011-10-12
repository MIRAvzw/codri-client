//
// Configuration
//

// Local includes
#include "userinterface.h"
#include "userinterface/webpages/initpage.h"
#include "userinterface/webpages/errorpage.h"
#include "userinterface/webpages/logpage.h"
#include "userinterface/webpages/presentationpage.h"
#include "userinterface/webpages/statuspage.h"

// Library includes
#include <QtCore/QStringList>

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

UserInterface::UserInterface(QWidget *iParent) throw(QException) : QMainWindow(iParent)
{
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup("UserInterface");

    // Setup logging
    mLogger =  Log4Qt::Logger::logger("UserInterface");
    mLogger->trace() << Q_FUNC_INFO;

    // Setup UI
    mWebView = new QWebView(this);
    mWebView->installEventFilter(this);
    setCentralWidget(mWebView);
    setWindowState(windowState() | Qt::WindowFullScreen);

    // Configure the webview
    showInit();
    connect(mWebView, SIGNAL(loadFinished(bool)), this, SLOT(_loadFinished(bool)));
    connect(mWebView, SIGNAL(loadProgress(int)), this, SLOT(_loadProgress(int)));
}


//
// Functionality
//

// TODO: track current page, do or do not reload (yes on media, no on log)?

void UserInterface::showInit()
{
    mLogger->trace() << Q_FUNC_INFO;

    QWebPage *tPageInit = new InitPage(mWebView);
    mWebView->setPage(tPageInit);
}

void UserInterface::showLog()
{
    mLogger->trace() << Q_FUNC_INFO;

    QWebPage *tPageLog = new LogPage(mWebView);
    mWebView->setPage(tPageLog);
}

void UserInterface::showStatus()
{
    mLogger->trace() << Q_FUNC_INFO;

    QWebPage *tPageStatus = new StatusPage(mWebView);
    mWebView->setPage(tPageStatus);
}

void UserInterface::showError(const QString& iError)
{
    mLogger->trace() << Q_FUNC_INFO;

    // TODO: load the error in the page

    QWebPage *tPageError = new ErrorPage(mWebView);
    mWebView->setPage(tPageError);
}

void UserInterface::showPresentation(const QDir& iLocation)
{
    mLogger->trace() << Q_FUNC_INFO;

    // TODO: is webview specification necessary? Does'tn setpage properly configure the parent?
    QWebPage *tPagetPresentation = new PresentationPage(iLocation, mWebView);
    mWebView->setPage(tPagetPresentation);
}


//
// UI events
//

bool UserInterface::eventFilter(QObject *iObject, QEvent *iEvent)
{
    if (iEvent->type() == QEvent::KeyPress)
    {
        QKeyEvent *iKeyEvent = static_cast<QKeyEvent*>(iEvent);
        switch (iKeyEvent->key())
        {
        // Default passthrough keys
        case Qt::Key_Left:
        case Qt::Key_Right:
        case Qt::Key_Return:
        case Qt::Key_Backspace:
            return false;
            break;

        // Status page
        case Qt::Key_1:
            showStatus();
            return true;
            break;

        // Log page
        case Qt::Key_2:
            showLog();
            return true;
            break;

        // Quit the application
        case Qt::Key_Q:
            emit quit();
            break;

        // Default case
        default:
            return QObject::eventFilter(iObject, iEvent);
            break;
        }

        return false;
    }
    else
    {
        // standard event processing
        return QObject::eventFilter(iObject, iEvent);
    }
}


//
// Slots
//

void UserInterface::_loadFinished(bool iOk)
{
    mLogger->trace() << Q_FUNC_INFO;

    if (iOk)
        return;

    // Media page handling
    if (mWebView->page() == 0)  // TODO: track
    {
        showError("unknown error");
        emit presentationError("unknown error");
    }
    else
    {
        // TODO: emit fatal error (we can't trust on loading the error page)
        mLogger->error("WebView error on internal webpage");
    }
}

void UserInterface::_loadProgress(int iProgress)
{
    // TODO: relay to initpage
}
