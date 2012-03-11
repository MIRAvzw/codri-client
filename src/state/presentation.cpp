/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Local includes
#include "presentation.h"


//
// Construction and destruction
//

MIRA::Presentation::Presentation(QObject *iParent) : QObject(iParent)
{
}


//
// Basic I/O
//

unsigned long MIRA::Presentation::getRevision() const
{
    return mRevision;
}

void MIRA::Presentation::setRevision(unsigned long iRevision)
{
    mRevision = iRevision;
    emit onRevisionChanged(iRevision);
}

QString MIRA::Presentation::getLocation() const
{
    return mLocation;
}

void MIRA::Presentation::setLocation(const QString &iLocation)
{
    mLocation = iLocation;
    emit onLocationChanged(iLocation);
}
