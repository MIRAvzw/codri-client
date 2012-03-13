/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "platforminterface.h"

// Local includes
#include "mainapplication.h"


//
// Construction and destruction
//

Codri::PlatformInterface::PlatformInterface(QObject* iParent) throw(QException)
    : QObject(iParent) {
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup(metaObject()->className());

    // Setup logging
    mLogger =  Log4Qt::Logger::logger(metaObject()->className());

    // Kiosk details
    MainApplication::instance()->kiosk()->setStatus(Codri::Kiosk::ON);
    MainApplication::instance()->kiosk()->setUuid(getUuid());
}


//
// State event listeners
//

void Codri::PlatformInterface::onConfigurationVolumeChanged(unsigned char iVolume) {
    // TODO: change the volume
}

void Codri::PlatformInterface::onKioskStatusChanged(Codri::Kiosk::Status iStatus) {
    // TODO: change the power state
}


//
// Auxiliary
//

QUuid Codri::PlatformInterface::getUuid() const throw(QException) {
    // Get the network interface
    QNetworkInterface tRemoteInterface = QNetworkInterface::interfaceFromName("eth0");
    if (!tRemoteInterface.isValid())
        throw QException("couldn't access eth0 network interface");

    // Extract the hardware address
    QString tHardwareAddress = tRemoteInterface.hardwareAddress();
    QStringList tHardwareAddressParts = tHardwareAddress.split(":");
    if (tHardwareAddressParts.size() != 6)
        throw new QException("invalid hardware address for eth0 network interface");

    // Create an UUID
    QUuid tUuid;
    tUuid.data1 |= (unsigned char) tHardwareAddressParts.at(0).toInt(0, 16) << 24;
    tUuid.data1 |= (unsigned char) tHardwareAddressParts.at(1).toInt(0, 16) << 16;
    tUuid.data1 |= (unsigned char) tHardwareAddressParts.at(2).toInt(0, 16) << 8;
    tUuid.data1 |= (unsigned char) tHardwareAddressParts.at(3).toInt(0, 16);
    tUuid.data2 |= (unsigned char) tHardwareAddressParts.at(4).toInt(0, 16) << 8;
    tUuid.data2 |= (unsigned char) tHardwareAddressParts.at(5).toInt(0, 16);
    tUuid.data4[0] = (tUuid.data4[0] & 0x3F) | 0x80;  // UV_MAC
    tUuid.data3 = (tUuid.data3 & 0x0FFF) | 0x1000;  // UV_Time (but without the actual timestamp, to persist reboots)

    return tUuid;
}
