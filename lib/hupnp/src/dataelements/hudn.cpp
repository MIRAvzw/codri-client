/*
 *  Copyright (C) 2010, 2011 Tuomo Penttinen, all rights reserved.
 *
 *  Author: Tuomo Penttinen <tp@herqq.org>
 *
 *  This file is part of Herqq UPnP (HUPnP) library.
 *
 *  Herqq UPnP is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Herqq UPnP is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with Herqq UPnP. If not, see <http://www.gnu.org/licenses/>.
 */

#include "hudn.h"

#include "../utils/hmisc_utils_p.h"

#include <QtCore/QString>
#include <QtCore/QByteArray>

#include <sys/ioctl.h>
#include <net/if.h>

namespace Herqq
{

namespace Upnp
{

HUdn::HUdn() :
    m_value()
{
}

HUdn::HUdn(const QUuid& value) :
    m_value(value.toString().remove('{').remove('}'))
{
}

HUdn::HUdn(const QString& value) :
    m_value(value.simplified())
{
}

HUdn::~HUdn()
{
}

QUuid HUdn::value() const
{
    if (m_value.startsWith("uuid:"))
    {
        return QUuid(m_value.mid(5));
    }

    return QUuid(m_value);
}

QString HUdn::toString() const
{
    if (m_value.isEmpty())
    {
        return m_value;
    }
    else if (m_value.startsWith("uuid:"))
    {
        return m_value;
    }

    return QString("uuid:").append(m_value);
}

QString HUdn::toSimpleUuid() const
{
    if (m_value.startsWith("uuid:"))
    {
        return m_value.mid(5);
    }

    return m_value;
}

HUdn HUdn::createUdn()
{
    // Create an interface request struct
    struct ifreq ifr;
    bzero(&ifr, sizeof(ifr));
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
    tUuid.data4[0] = (tUuid.data4[0] & 0x3F) | 0x80;        // UV_DCE
    tUuid.data3 = (tUuid.data3 & 0x0FFF) | 0x1000;        // UV_Time (but without the actual timestamp, to persist reboots)

    return HUdn(tUuid);
}

bool operator==(const HUdn& udn1, const HUdn& udn2)
{
    return udn1.toString() == udn2.toString();
}

quint32 qHash(const HUdn& key)
{
    QByteArray data = key.toString().toLocal8Bit();
    return hash(data.constData(), data.size());
}

}
}
