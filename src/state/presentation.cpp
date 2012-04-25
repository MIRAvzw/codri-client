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

    // Default values
    setRevision(0);
    setPath("uninitialized");
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

QString Codri::Presentation::getPath() const {
    return mPath;
}

void Codri::Presentation::setPath(const QString &iPath) {
    mPath = iPath;
    mLogger->debug() << "Path changing to " << iPath;
    emit onPathChanged(iPath);
}
