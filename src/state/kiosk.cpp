/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Local includes
#include "kiosk.h"

// Platform includes
#include <sys/ioctl.h>
#include <net/if.h>


//
// Construction and destruction
//

MIRA::Kiosk::Kiosk(QObject *iParent) : QObject(iParent)
{
    // Default power state
    mPower = ON;

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
    mUuid.data1 |= (unsigned char) ifr.ifr_hwaddr.sa_data[0] << 24;
    mUuid.data1 |= (unsigned char) ifr.ifr_hwaddr.sa_data[1] << 16;
    mUuid.data1 |= (unsigned char) ifr.ifr_hwaddr.sa_data[2] << 8;
    mUuid.data1 |= (unsigned char) ifr.ifr_hwaddr.sa_data[3];
    mUuid.data2 |= (unsigned char) ifr.ifr_hwaddr.sa_data[4] << 8;
    mUuid.data2 |= (unsigned char) ifr.ifr_hwaddr.sa_data[5];
    mUuid.data4[0] = (mUuid.data4[0] & 0x3F) | 0x80; // UV_MAC
    mUuid.data3 = (mUuid.data3 & 0x0FFF) | 0x1000; // UV_Time (but without the actual timestamp, to persist reboots)
}


//
// Basic I/O
//

MIRA::Kiosk::Power MIRA::Kiosk::getPower() const
{
    return mPower;
}

void MIRA::Kiosk::setPower(MIRA::Kiosk::Power iPower)
{
    mPower = iPower;
    emit onPowerChanged(iPower);
}

QUuid MIRA::Kiosk::getUuid() const
{
    return mUuid;
}

QString MIRA::Kiosk::getVendor() const
{
    return "MIRA";
}

QString MIRA::Kiosk::getModel() const
{
    return "Genesi kiosk";
}

unsigned short MIRA::Kiosk::getPort() const
{
    return mPort;
}

void MIRA::Kiosk::setPort(unsigned short iPort)
{
    mPort = iPort;
}
