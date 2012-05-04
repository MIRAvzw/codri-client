/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "platforminterface.h"

// Library includes
#include <QtCore/QProcess>
#include <QtNetwork/QHostInfo>

// Local includes
#include "mainapplication.h"


//
// Construction and destruction
//

Codri::PlatformInterface::PlatformInterface(QObject* iParent) throw(QException)
    : QObject(iParent) {
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup(metaObject()->className());

    // Setup logging
    mLogger =  Log4Qt::Logger::logger(metaObject()->className());

    // Get a hold of the mixer
    if (snd_mixer_open(&mMixer, 0) < 0)
        throw QException("could not open mixer");
    if (snd_mixer_attach(mMixer, "default") < 0) {
        snd_mixer_close(mMixer);
        throw QException("could not attach mixer to soundcard");
    }
    if (snd_mixer_selem_register(mMixer, NULL, NULL) < 0) {
        snd_mixer_close(mMixer);
        throw QException("could not register mixer");
    }
    if (snd_mixer_load(mMixer) < 0) {
        snd_mixer_close(mMixer);
        throw QException("could not load mixer");
    }

    // Get a hold of the relevant mixer elements
    snd_mixer_selem_id_t *tElementId;
    snd_mixer_selem_id_alloca(&tElementId);
    snd_mixer_selem_id_set_index(tElementId, 0);
    snd_mixer_selem_id_set_name(tElementId, "Master");
    mMixerElement = snd_mixer_find_selem(mMixer, tElementId);
    if (mMixerElement == NULL) {
        snd_mixer_close(mMixer);
        throw QException("could not find main mixer element");
    }

    // Apply default values
#ifdef DEVEL
    MainApplication::instance()->kiosk()->setId("testclient");
#else
    QHostInfo tHostInfo;
    MainApplication::instance()->kiosk()->setId(tHostInfo.localHostName());
#endif
    setVolume(MainApplication::instance()->configuration()->getVolume());
    setPower(MainApplication::instance()->kiosk()->getPower());
}

void Codri::PlatformInterface::start() {
}

Codri::PlatformInterface::~PlatformInterface() {
    snd_mixer_close(mMixer);
}


//
// Public interface
//

uint8_t Codri::PlatformInterface::getVolume() {
    // Get the volume range
    long tMinimum, tMaximum;
    snd_mixer_selem_get_playback_volume_range(mMixerElement, &tMinimum, &tMaximum);

    // Get the volume of all channels
    long tLeft, tRight;
    snd_mixer_selem_get_playback_volume(mMixerElement, SND_MIXER_SCHN_FRONT_LEFT, &tLeft);
    snd_mixer_selem_get_playback_volume(mMixerElement, SND_MIXER_SCHN_FRONT_RIGHT, &tRight);
    long tVolume = (tLeft + tRight) / 2;

    // Finalize
    return tVolume * 255 / tMaximum;
}

void Codri::PlatformInterface::setVolume(uint8_t iVolume) {
    // Get the volume range
    long tMinimum, tMaximum;
    snd_mixer_selem_get_playback_volume_range(mMixerElement, &tMinimum, &tMaximum);

    // Finalize
    snd_mixer_selem_set_playback_volume_all(mMixerElement, iVolume * tMaximum / 255);
}

void Codri::PlatformInterface::setPower(Codri::Kiosk::Power iPower) {
    switch (iPower) {
    case Codri::Kiosk::ON:
        return;
    case Codri::Kiosk::OFF:
        // FIXME: using reboot(2) is nicer, but not possible from non-root user
        QString tOutput;
        QStringList tArguments;
        tArguments << "/sbin/poweroff";
        if (!sudo(tArguments, tOutput))
            mLogger->error() << "Could not shut down device: " << tOutput;
        return;
    }
}


//
// Auxiliary
//

bool Codri::PlatformInterface::system(const QString& iCommand, const QStringList& iArguments, QString& oOutput) {
    // Set-up the process
    mLogger->debug() << "Executing system command " << iCommand << " with arguments " << iArguments.join(" ");
    QProcess tProcess(this);
    tProcess.setProcessChannelMode(QProcess::MergedChannels);

    // Execute the command
    tProcess.start(iCommand, iArguments);
    tProcess.waitForStarted(mSettings->value("executiondelay", 5000).toInt());
    if (tProcess.state() != QProcess::Running)
        return false;
    tProcess.waitForFinished(mSettings->value("executiondelay", 30000).toInt());

    // Return appropriate data
    oOutput = tProcess.readAll();
    return (tProcess.exitStatus() == QProcess::NormalExit);
}

bool Codri::PlatformInterface::sudo(const QStringList& iArguments, QString& oOutput) {
    return system("/usr/bin/sudo", iArguments, oOutput);
}
