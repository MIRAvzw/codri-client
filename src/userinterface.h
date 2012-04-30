/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
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
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>
#include <QtWebKit/QGraphicsWebView>
#include <log4qt/Logger>

// Local includes
#include "auxiliary/qexception.h"
#include "user/webpage.h"

namespace Codri {
    class UserInterface : public QMainWindow {
    Q_OBJECT
    public:
        // Construction and destruction
        explicit UserInterface(QWidget *iParent = 0) throw(QException);
        void start();

        // Public interface
    public slots:
        void showInit();
        void showLog();
        void showStatus();
        void showError();
        void showPresentation(const QDir &iLocation);

        // Events
    signals:
        void runtimeFailure();

        // UI events
    public:
        bool eventFilter(QObject *iObject, QEvent *iEvent);
        void resizeEvent(QResizeEvent *iResizeEvent);

        // Internal slots
    private slots:
        void _loadFinished(bool iOk);

    private:
        // Infrastructure
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;

        // Member objects
        QGraphicsScene *mGraphicsScene;
        QGraphicsView *mGraphicsView;
        QGraphicsWebView *mWebView;
    };
}

#endif  // USERINTERFACE_H_
