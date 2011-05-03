//
// Configuration
//

// Include guard
#ifndef USERINTERFACE_H
#define USERINTERFACE_H

// Library includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtGui/QMainWindow>
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
        UserInterface(QWidget *parent = 0);

        // Subsystem interface
        void init() throw(QException);

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
