//
// Configuration
//

// Include guard
#ifndef USERINTERFACE_H
#define USERINTERFACE_H

// System includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtGui/QMainWindow>
#include <QtWebKit/QWebView>

// Local includes
#include "qexception.h"
#include "logger.h"
#include "webpage.h"

namespace MIRA
{
    class UserInterface : public QMainWindow
    {
    Q_OBJECT
    public:
        // Construction and destruction
        UserInterface(QWidget *parent = 0) throw(QException);

        // Messaging methods
        void showNotice(const QString& iMessage) const;
        void showAlert(const QString& iMessage) const;

    private:
        // Member objects
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;
        QWebView *mWebView;
        WebPage* mWebPage;
    };
}

#endif // USERINTERFACE_H
