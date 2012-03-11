/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "presentation.h"


//
// Construction and destruction
//

Codri::Presentation::Presentation(QObject *iParent)
    : QObject(iParent)
{
}


//
// Basic I/O
//

unsigned long Codri::Presentation::getRevision() const
{
    return mRevision;
}

void Codri::Presentation::setRevision(unsigned long iRevision)
{
    mRevision = iRevision;
    emit onRevisionChanged(iRevision);
}

QString Codri::Presentation::getLocation() const
{
    return mLocation;
}

void Codri::Presentation::setLocation(const QString &iLocation)
{
    mLocation = iLocation;
    emit onLocationChanged(iLocation);
}
