/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

// Library includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtCore/QDir>
#include <QtGui/QMainWindow>
#include <QtGui/QKeyEvent>
#include <QtWebKit/QWebView>
#include <Log4Qt/Logger>

// Local includes
#include "auxiliary/qexception.h"
#include "user/webpage.h"

namespace Codri {
    class UserInterface : public QMainWindow {
    Q_OBJECT
    public:
        // Construction and destruction
        explicit UserInterface(QWidget *iParent = 0) throw(QException);

        // Public interface
    public slots:
        void showInit();
        void showLog();
        void showStatus();
        void showError(const QException& iException);
        void showPresentation(const QDir &iLocation);

        // Events
    signals:
        void presentationError(QString iError);

        // UI events
    public:
        bool eventFilter(QObject *iObject, QEvent *iEvent);

        // Internal slots
    private slots:
        void _loadFinished(bool iOk);
        void _loadProgress(int iProgress);

    private:
        // Infrastructure
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;

        // Member objects
        QWebView *mWebView;
    };
}

#endif  // USERINTERFACE_H_
