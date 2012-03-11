/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Local includes
#include "configuration.h"


//
// Construction and destruction
//

Codri::Configuration::Configuration(QObject *iParent) : QObject(iParent)
{
}


//
// Basic I/O
//

unsigned long Codri::Configuration::getRevision() const
{
    return mRevision;
}

void Codri::Configuration::setRevision(unsigned long iRevision)
{
    mRevision = iRevision;
}

unsigned short Codri::Configuration::getVolume() const
{
    return mVolume;
}

void Codri::Configuration::setVolume(unsigned char iVolume)
{
    mVolume = iVolume;
    emit onVolumeChanged(iVolume);
}
