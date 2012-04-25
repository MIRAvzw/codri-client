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
#include <alsa/asoundlib.h>

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

    // Apply default values
#ifdef DEVEL
    MainApplication::instance()->kiosk()->setId("testclient");
#else
    QHostInfo tHostInfo;
    MainApplication::instance()->kiosk()->setId(tHostInfo.localHostName());
#endif
    setVolume(MainApplication::instance()->configuration()->getVolume());
    setStatus(MainApplication::instance()->kiosk()->getStatus());
}

void Codri::PlatformInterface::start() {
}


//
// Public interface
//

uint8_t Codri::PlatformInterface::getVolume() {
    // Open the simple mixer interface
    snd_mixer_t *tHandle;
    snd_mixer_open(&tHandle, 0);
    snd_mixer_attach(tHandle, "default");
    snd_mixer_selem_register(tHandle, NULL, NULL);
    snd_mixer_load(tHandle);

    // Get a hold of the Master element
    snd_mixer_selem_id_t *tElementId;
    snd_mixer_selem_id_alloca(&tElementId);
    snd_mixer_selem_id_set_index(tElementId, 0);
    snd_mixer_selem_id_set_name(tElementId, "Master");
    snd_mixer_elem_t* tElement = snd_mixer_find_selem(tHandle, tElementId);

    // Get the volume range
    long tMinimum, tMaximum;
    snd_mixer_selem_get_playback_volume_range(tElement, &tMinimum, &tMaximum);

    // Get the volume of all channels
    long tLeft, tRight;
    snd_mixer_selem_get_playback_volume(tElement, SND_MIXER_SCHN_FRONT_LEFT, &tLeft);
    snd_mixer_selem_get_playback_volume(tElement, SND_MIXER_SCHN_FRONT_RIGHT, &tRight);
    long tVolume = (tLeft + tRight) / 2;

    // Finalize
    snd_mixer_close(tHandle);
    return tVolume * 255 / tMaximum;
}

void Codri::PlatformInterface::setVolume(uint8_t iVolume) {
    // Open the simple mixer interface
    snd_mixer_t *tHandle;
    snd_mixer_open(&tHandle, 0);
    snd_mixer_attach(tHandle, "default");
    snd_mixer_selem_register(tHandle, NULL, NULL);
    snd_mixer_load(tHandle);

    // Get a hold of the Master element
    snd_mixer_selem_id_t *tElementId;
    snd_mixer_selem_id_alloca(&tElementId);
    snd_mixer_selem_id_set_index(tElementId, 0);
    snd_mixer_selem_id_set_name(tElementId, "Master");
    snd_mixer_elem_t* tElement = snd_mixer_find_selem(tHandle, tElementId);

    // Get the volume range
    long tMinimum, tMaximum;
    snd_mixer_selem_get_playback_volume_range(tElement, &tMinimum, &tMaximum);

    // Finalize
    snd_mixer_selem_set_playback_volume_all(tElement, iVolume * tMaximum / 255);
    snd_mixer_close(tHandle);
}

void Codri::PlatformInterface::setStatus(Codri::Kiosk::Status iStatus) {
    switch (iStatus) {
    case Codri::Kiosk::ON:
        return;
    case Codri::Kiosk::OFF:
        sync();
        reboot(RB_POWER_OFF);
        return;
    }
}
