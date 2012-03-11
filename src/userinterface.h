/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

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
        void showLog();
        void showStatus();
        void showError(const QString& iError);
        void showPresentation(const QDir &iLocation);

        // Slots
    private slots:
        void _loadFinished(bool iOk);
        void _loadProgress(int iProgress);

        // Signals
    signals:
        void presentationError(QString iError);

    private:
        // Member objects
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;
        QWebView *mWebView;
    };
}

#endif // USERINTERFACE_H
