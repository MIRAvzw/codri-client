/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */


//
// Configuration
//

// Include guard
#ifndef STATE_KIOSK_H_
#define STATE_KIOSK_H_

// Library includes
#include <QtCore/QObject>
#include <QtCore/QUuid>
#include <QtNetwork/QNetworkAddressEntry>
#include <Log4Qt/Logger>

namespace Codri
{
    class Kiosk : public QObject
    {
        Q_OBJECT
    public:
        // Construction and destruction
        explicit Kiosk(QObject *iParent);

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

        // Subsystem objects
        Log4Qt::Logger *mLogger;
    };
}

#endif  // STATE_KIOSK_H_
