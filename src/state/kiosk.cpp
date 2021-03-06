/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "state/kiosk.h"

// Library includes
#include <QtCore/QMetaEnum>


//
// Construction and destruction
//

Codri::Kiosk::Kiosk(QObject *iParent)
    : QObject(iParent) {
    // Setup logging
    mLogger =  Log4Qt::Logger::logger(metaObject()->className());

    // Default values
    setId("uninitialized");
    setVendor("uninitialized");
    setModel("uninitialized");
    setPort(0);
    setPower(Kiosk::ON);
}


//
// Basic I/O
//

QString Codri::Kiosk::getId() const {
    return mId;
}

void Codri::Kiosk::setId(const QString &iId) {
    mId = iId;
}

Codri::Kiosk::Power Codri::Kiosk::getPower() const {
    return mPower;
}

void Codri::Kiosk::setPower(Codri::Kiosk::Power iPower) {
    mPower = iPower;

    // Get the enum's meta object
    const QMetaObject &tMetaObject = Kiosk::staticMetaObject;
    int tIndex = tMetaObject.indexOfEnumerator("Power");
    QMetaEnum tMetaEnum = tMetaObject.enumerator(tIndex);

    mLogger->debug() << "Power changing to " << tMetaEnum.valueToKey(iPower);
    emit onPowerChanged(iPower);
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

uint16_t Codri::Kiosk::getPort() const {
    return mPort;
}

void Codri::Kiosk::setPort(uint16_t iPort) {
    mPort = iPort;
    mLogger->debug() << "Port changing to " << iPort;
}
