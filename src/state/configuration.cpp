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

MIRA::Configuration::Configuration(QObject *iParent) : QObject(iParent)
{
}


//
// Basic I/O
//

unsigned long MIRA::Configuration::getRevision() const
{
    return mRevision;
}

void MIRA::Configuration::setRevision(unsigned long iRevision)
{
    mRevision = iRevision;
}

unsigned short MIRA::Configuration::getVolume() const
{
    return mVolume;
}

void MIRA::Configuration::setVolume(unsigned char iVolume)
{
    mVolume = iVolume;
    emit onVolumeChanged(iVolume);
}
