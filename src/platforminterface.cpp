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

// System includes
#include <sys/ioctl.h>
#include <net/if.h>

// Local includes
#include "mainapplication.h"


//
// Construction and destruction
//

Codri::PlatformInterface::PlatformInterface(QObject* iParent) throw(QException)
    : QObject(iParent)
{
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

void Codri::PlatformInterface::onConfigurationVolumeChanged(unsigned char iVolume)
{
    // TODO: change the volume
}

void Codri::PlatformInterface::onKioskStatusChanged(Codri::Kiosk::Status iStatus)
{
    // TODO: change the power state
}


//
// Auxiliary
//

QUuid Codri::PlatformInterface::getUuid() const
{
    // Create an interface request struct
    // FIXME: use Qt;
    //        QNetworkInterface tRemoteInterface = QNetworkInterface::interfaceFromName("eth0");
    //        qDebug() << tRemoteInterface.hardwareAddress();
    struct ifreq ifr;
    memset(&ifr, '\0', sizeof(ifr));
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);

    // Open a socket and perform the IOCTL
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    ioctl(fd, SIOCGIFHWADDR, &ifr);
    close(fd);

    // Create an UUID
    QUuid tUuid;
    tUuid.data1 |= (unsigned char) ifr.ifr_hwaddr.sa_data[0] << 24;
    tUuid.data1 |= (unsigned char) ifr.ifr_hwaddr.sa_data[1] << 16;
    tUuid.data1 |= (unsigned char) ifr.ifr_hwaddr.sa_data[2] << 8;
    tUuid.data1 |= (unsigned char) ifr.ifr_hwaddr.sa_data[3];
    tUuid.data2 |= (unsigned char) ifr.ifr_hwaddr.sa_data[4] << 8;
    tUuid.data2 |= (unsigned char) ifr.ifr_hwaddr.sa_data[5];
    tUuid.data4[0] = (tUuid.data4[0] & 0x3F) | 0x80;  // UV_MAC
    tUuid.data3 = (tUuid.data3 & 0x0FFF) | 0x1000;  // UV_Time (but without the actual timestamp, to persist reboots)

    return tUuid;
}
