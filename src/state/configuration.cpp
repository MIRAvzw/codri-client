/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
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
    // Setup logging
    mLogger =  Log4Qt::Logger::logger(metaObject()->className());
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
    mLogger->debug() << "Volume changing to " << iVolume;
    emit onVolumeChanged(iVolume);
}
