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
#include <log4qt/Logger>
#include <alsa/asoundlib.h>

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
        ~PlatformInterface();

        // Public interface
    public slots:
        uint8_t getVolume();
        void setVolume(uint8_t iVolume);
        void setPower(Kiosk::Power iPower);

        // Auxiliary
    private:
        bool system(const QString &iCommand, const QStringList &iArguments, QString &oOutput);
        bool sudo(const QStringList &iArguments, QString &oOutput);

    private:
        // Infrastructure
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;

        // Member data
        snd_mixer_t *mMixer;
        snd_mixer_elem_t *mMixerElement;
    };
}

#endif  // PLATFORMINTERFACE_H_
