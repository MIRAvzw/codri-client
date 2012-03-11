/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

// Library includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtGui/QApplication>
#include <QtCore/QSocketNotifier>
#include <QtCore/QDateTime>
#include <Log4Qt/Logger>

// Local includes
#include "qexception.h"
#include "controller.h"

namespace MIRA
{
    class MainApplication : public QApplication
    {
        Q_OBJECT
    public:
        // Construction and destruction
        explicit MainApplication(int &iArgumentCount, char **iArgumentValues) throw(QException);
        ~MainApplication();

        // System signals (Unix)
        static void handleInterruptUnix(int unused);
        static void handleTerminateUnix(int unused);

        // State getters
        Kiosk *kiosk() const;
        Configuration *configuration() const;
        Presentation *presentation() const;

        // Subsystem getters
        Controller *controller() const;

        // Singleton object getters
    public:
        static MainApplication *instance();

    private:
        // Singleton object
        static MainApplication *mInstance;

        // State objects
        Kiosk *mKiosk;
        Configuration *mConfiguration;
        Presentation *mPresentation;

        // Subsystem objects
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;
        Controller *mController;

        // External
        friend void doMessage(QtMsgType iMessageType, const char *iMessage);
    };

    void doMessage(QtMsgType iMessageType, const char *iMessage);
}

#endif // MAINAPPLICATION_H
