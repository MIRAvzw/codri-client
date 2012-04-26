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

// System includes
#include <sys/reboot.h>

// Library includes
#include <QtNetwork/QHostInfo>

// Local includes
#include "mainapplication.h"

// Function prototypes
int reboot(int magic, int magic2, int cmd, void *arg);


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
#ifdef DEVEL
    snd_mixer_selem_id_set_name(tElementId, "Master");
#else
    snd_mixer_selem_id_set_name(tElementId, "Playback");
#endif
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
    setStatus(MainApplication::instance()->kiosk()->getPower());
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

void Codri::PlatformInterface::setStatus(Codri::Kiosk::Power iStatus) {
    switch (iStatus) {
    case Codri::Kiosk::ON:
        return;
    case Codri::Kiosk::OFF:
        sync();
        reboot(RB_POWER_OFF);
        return;
    }
}
