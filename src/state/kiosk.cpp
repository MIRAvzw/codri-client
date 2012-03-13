/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "kiosk.h"


//
// Construction and destruction
//

Codri::Kiosk::Kiosk(QObject *iParent)
    : QObject(iParent) {
    // Setup logging
    mLogger =  Log4Qt::Logger::logger(metaObject()->className());
}


//
// Basic I/O
//

Codri::Kiosk::Status Codri::Kiosk::getStatus() const {
    return mStatus;
}

void Codri::Kiosk::setStatus(Codri::Kiosk::Status iStatus) {
    mStatus = iStatus;
    mLogger->debug() << "Power changing to " << iStatus;
    emit onStatusChanged(iStatus);
}

QUuid Codri::Kiosk::getUuid() const {
    return mUuid;
}

void Codri::Kiosk::setUuid(const QUuid &iUuid) {
    mUuid = iUuid;
}

QString Codri::Kiosk::getVendor() const {
    return mVendor;
}

void Codri::Kiosk::setVendor(const QString &iVendor) {
    mVendor = iVendor;
}

QString Codri::Kiosk::getModel() const {
    return mModel;
}

void Codri::Kiosk::setModel(const QString &iModel) {
    mModel = iModel;
}

unsigned short Codri::Kiosk::getPort() const {
    return mPort;
}

void Codri::Kiosk::setPort(unsigned short iPort) {
    mPort = iPort;
    mLogger->debug() << "Port changing to " << iPort;
}
