//
// Configuration
//

// Local includes
#include "userinterface.h"
#include "mainapplication.h"
#include "userinterface/webpages/logpage.h"
#include "userinterface/webpages/mediapage.h"
#include "userinterface/webpages/statuspage.h"

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
    mWebView->installEventFilter(this);
    setCentralWidget(mWebView);
    showFullScreen();

    // Load the pages (child of the mainwindow, because QWebView::setPage deletes its previous childs)
    mPageMedia = new MediaPage(this);
    mPageLog = new LogPage(this);
    mPageStatus = new StatusPage(this);
    mWebView->setPage(mPageMedia);
}


//
// Functionality
//

void UserInterface::showMedia(const QDir &iMedia) throw(QException)
{
    QFile tFile(iMedia.absolutePath() + "/index.html");
    if (!tFile.exists())
        throw new QException("invalid media format");

    mPageMedia->load("file://" + iMedia.absolutePath() + "/index.html");
}


//
// UI events
//

bool UserInterface::eventFilter(QObject* iObject, QEvent* iEvent)
{
    if (iEvent->type() == QEvent::KeyPress) {
        QKeyEvent *iKeyEvent = static_cast<QKeyEvent *>(iEvent);
        switch (iKeyEvent->key())
        {
        // Default passthrough keys
        case Qt::Key_Left:
        case Qt::Key_Right:
        case Qt::Key_Return:
        case Qt::Key_Backspace:
            return true;
            break;

        // Status page
        case Qt::Key_1:
            mWebView->setPage( mWebView->page() != mPageStatus ? mPageStatus : mPageMedia );
            return false;
            break;

        // Log page
        case Qt::Key_2:
            mWebView->setPage( mWebView->page() != mPageLog ? mPageLog : mPageMedia );
            return false;
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
    } else {
        // standard event processing
        return QObject::eventFilter(iObject, iEvent);
    }
}
