/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */


//
// Configuration
//

// Include guard
#ifndef KIOSK_H
#define KIOSK_H

// Library includes
#include <QtCore/QObject>
#include <QtCore/QUuid>
#include <QtNetwork/QNetworkAddressEntry>

namespace Codri
{
    class Kiosk : public QObject
    {
        Q_OBJECT
    public:
        // Construction and destruction
        Kiosk(QObject *iParent);

        // Power enum
        enum Power {
            ON,
            OFF
        };

        // Basic I/O
        Kiosk::Power getPower() const;
        void setPower(Kiosk::Power iPower);
        QUuid getUuid() const;
        QString getVendor() const;
        QString getModel() const;
        unsigned short getPort() const;
        void setPort(unsigned short iPort);

        // Signals
    signals:
        void onPowerChanged(Kiosk::Power iPower);

    private:
        // Member data
        Power mPower;
        QUuid mUuid;
        unsigned short mPort;
    };
}

#endif // KIOSK_H
