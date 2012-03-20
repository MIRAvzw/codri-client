/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "state/presentation.h"


//
// Construction and destruction
//

Codri::Presentation::Presentation(QObject *iParent)
    : QObject(iParent) {
    // Setup logging
    mLogger =  Log4Qt::Logger::logger(metaObject()->className());
}


//
// Basic I/O
//

uint32_t Codri::Presentation::getRevision() const {
    return mRevision;
}

void Codri::Presentation::setRevision(uint32_t iRevision) {
    mRevision = iRevision;
    mLogger->debug() << "Revision changing to " << iRevision;
    emit onRevisionChanged(iRevision);
}

QString Codri::Presentation::getLocation() const {
    return mLocation;
}

void Codri::Presentation::setLocation(const QString &iLocation) {
    mLocation = iLocation;
    mLogger->debug() << "Location changing to " << iLocation;
    emit onLocationChanged(iLocation);
}
