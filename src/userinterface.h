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
#include <QtCore/QProcess>
#include <QtGui/QMainWindow>
#include <QtGui/QX11EmbedContainer>
#include <log4qt/Logger>

// Local includes
#include "auxiliary/qexception.h"

namespace Codri {
    class UserInterface : public QObject {
    Q_OBJECT
    public:
        // Construction and destruction
        explicit UserInterface(QObject *iParent) throw(QException);
        void start();

        // Public interface
    public slots:
        void showInit();
        void showError();
        void showPresentation(const QDir &iLocation);

    private:
        // Auxiliary
        void load(const QString& iUrl);

        // Infrastructure
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;

        // Member objects
        QProcess *mApplication;
        QDir mUserData;
    };
}

#endif  // USERINTERFACE_H_
