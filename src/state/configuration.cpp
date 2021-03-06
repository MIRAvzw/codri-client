/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "state/configuration.h"


//
// Construction and destruction
//

Codri::Configuration::Configuration(QObject *iParent)
    : QObject(iParent) {
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup(metaObject()->className());

    // Setup logging
    mLogger =  Log4Qt::Logger::logger(metaObject()->className());

    // Default values
    setRevision(0);
    setVolume(mSettings->value("volume", 255).toInt());
}


//
// Basic I/O
//

uint32_t Codri::Configuration::getRevision() const {
    return mRevision;
}

void Codri::Configuration::setRevision(uint32_t iRevision) {
    mRevision = iRevision;
    mLogger->debug() << "Revision changing to " << iRevision;
    emit onRevisionChanged(iRevision);
}

uint8_t Codri::Configuration::getVolume() const {
    return mVolume;
}

void Codri::Configuration::setVolume(uint8_t iVolume) {
    mVolume = iVolume;
    mSettings->setValue("volume", iVolume);
    mLogger->debug() << "Volume changing to " << iVolume;
    emit onVolumeChanged(iVolume);
}
