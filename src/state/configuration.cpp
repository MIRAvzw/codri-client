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

unsigned long Codri::Configuration::getRevision() const {
    return mRevision;
}

void Codri::Configuration::setRevision(unsigned long iRevision) {
    mRevision = iRevision;
    mLogger->debug() << "Revision changing to " << iRevision;
    emit onRevisionChanged(iRevision);
}

unsigned short Codri::Configuration::getVolume() const {
    return mVolume;
}

void Codri::Configuration::setVolume(unsigned char iVolume) {
    mVolume = iVolume;
    mLogger->debug() << "Volume changing to " << iVolume;
    emit onVolumeChanged(iVolume);
}
