/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */


//
// Configuration
//

// Include guard
#ifndef STATE_KIOSK_H_
#define STATE_KIOSK_H_

// System includes
#include <stdint.h>

// Library includes
#include <QtCore/QObject>
#include <QtNetwork/QNetworkAddressEntry>
#include <log4qt/Logger>

namespace Codri {
    class Kiosk : public QObject {
    Q_OBJECT
    public:
        // Construction and destruction
        explicit Kiosk(QObject *iParent);

        // Power enum
        enum Power {
            ON,
            OFF
        };
        Q_ENUMS(Power)

        // Basic I/O
        QString getId() const;
        void setId(const QString& iId);
        Kiosk::Power getPower() const;
        void setPower(Kiosk::Power iStatus);
        QString getVendor() const;
        void setVendor(const QString& iVendor);
        QString getModel() const;
        void setModel(const QString& iModel);
        uint16_t getPort() const;
        void setPort(uint16_t iPort);

        // Signals
    signals:
        void onPowerChanged(Kiosk::Power iPower);

    private:
        // Member data
        QString mId;
        Power mPower;
        QString mVendor, mModel;
        uint16_t mPort;

        // Subsystem objects
        Log4Qt::Logger *mLogger;
    };
}

#endif  // STATE_KIOSK_H_
