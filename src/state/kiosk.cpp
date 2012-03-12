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

// System includes
#include <sys/ioctl.h>
#include <net/if.h>


//
// Construction and destruction
//

Codri::Kiosk::Kiosk(QObject *iParent)
    : QObject(iParent)
{
    // Setup logging
    mLogger =  Log4Qt::Logger::logger(metaObject()->className());

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
    mUuid.data4[0] = (mUuid.data4[0] & 0x3F) | 0x80;  // UV_MAC
    mUuid.data3 = (mUuid.data3 & 0x0FFF) | 0x1000;  // UV_Time (but without the actual timestamp, to persist reboots)
}


//
// Basic I/O
//

Codri::Kiosk::Power Codri::Kiosk::getPower() const
{
    return mPower;
}

void Codri::Kiosk::setPower(Codri::Kiosk::Power iPower)
{
    mPower = iPower;
    mLogger->debug() << "Power changing to " << iPower;
    emit onPowerChanged(iPower);
}

QUuid Codri::Kiosk::getUuid() const
{
    return mUuid;
}

QString Codri::Kiosk::getVendor() const
{
    return "Codri";
}

QString Codri::Kiosk::getModel() const
{
    return "Genesi kiosk";
}

unsigned short Codri::Kiosk::getPort() const
{
    return mPort;
}

void Codri::Kiosk::setPort(unsigned short iPort)
{
    mPort = iPort;
    mLogger->debug() << "Port changing to " << iPort;
}
