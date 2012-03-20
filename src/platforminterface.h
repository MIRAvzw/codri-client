/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef PLATFORMINTERFACE_H_
#define PLATFORMINTERFACE_H_

// Library includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <Log4Qt/Logger>
#include <QtCore/QUuid>

// Local includes
#include "auxiliary/qexception.h"
#include "state/kiosk.h"

namespace Codri {
    class PlatformInterface : public QObject {
    Q_OBJECT
    public:
        // Construction and destruction
        explicit PlatformInterface(QObject *iParent) throw(QException);
        void start();

        // Public interface
    public slots:
        uint8_t getVolume();
        void setVolume(uint8_t iVolume);
        void setStatus(Kiosk::Status iStatus);

        // Auxiliary
    private:
        QUuid getUuid() const throw(QException);

    private:
        // Infrastructure
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;
    };
}

#endif  // PLATFORMINTERFACE_H_
