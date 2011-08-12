//
// Configuration
//

// Include guard
#ifndef USERINTERFACE_H
#define USERINTERFACE_H

// Library includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtCore/QDir>
#include <QtGui/QMainWindow>
#include <QtGui/QKeyEvent>
#include <QtWebKit/QWebView>
#include <Log4Qt/Logger>

// Local includes
#include "qexception.h"
#include "userinterface/webpage.h"

namespace MIRA
{
    class UserInterface : public QMainWindow
    {
    Q_OBJECT
    public:
        // Construction and destruction
        UserInterface(QWidget *iParent = 0) throw(QException);

        // UI events
        bool eventFilter(QObject *iObject, QEvent *iEvent);

        // Functionality
        void showInit();
        void showError(const QString& iError);
        void showMedia(const QDir &iMedia) throw(QException);
        void hideMedia() throw(QException);

        // Signals
    signals:
        void quit();

    private:
        // Member objects
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;
        QWebView *mWebView;

        // Webpages
        WebPage *mPageInit, *mPageError, *mPageMedia, *mPageLog, *mPageStatus;
    };
}

#endif // USERINTERFACE_H
