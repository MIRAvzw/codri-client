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

    // Kiosk details
    MainApplication::instance()->kiosk()->setStatus(Codri::Kiosk::ON);
    MainApplication::instance()->kiosk()->setUuid(getUuid());

    // Configuration details
    MainApplication::instance()->configuration()->setVolume(getVolume());
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


//
// Auxiliary
//

QUuid Codri::PlatformInterface::getUuid() const throw(QException) {
    // Get the network interface
    QNetworkInterface tRemoteInterface = QNetworkInterface::interfaceFromName("eth0");
    if (!tRemoteInterface.isValid())
        throw QException("couldn't access eth0 network interface");

    // Extract the hardware address
    QString tHardwareAddress = tRemoteInterface.hardwareAddress();
    QStringList tHardwareAddressParts = tHardwareAddress.split(":");
    if (tHardwareAddressParts.size() != 6)
        throw new QException("invalid hardware address for eth0 network interface");

    // Create an UUID
    QUuid tUuid;
    tUuid.data1 |= (unsigned char) tHardwareAddressParts.at(0).toInt(0, 16) << 24;
    tUuid.data1 |= (unsigned char) tHardwareAddressParts.at(1).toInt(0, 16) << 16;
    tUuid.data1 |= (unsigned char) tHardwareAddressParts.at(2).toInt(0, 16) << 8;
    tUuid.data1 |= (unsigned char) tHardwareAddressParts.at(3).toInt(0, 16);
    tUuid.data2 |= (unsigned char) tHardwareAddressParts.at(4).toInt(0, 16) << 8;
    tUuid.data2 |= (unsigned char) tHardwareAddressParts.at(5).toInt(0, 16);
    tUuid.data4[0] = (tUuid.data4[0] & 0x3F) | 0x80;  // UV_MAC
    tUuid.data3 = (tUuid.data3 & 0x0FFF) | 0x1000;  // UV_Time (but without the actual timestamp, to persist reboots)

    return tUuid;
}
