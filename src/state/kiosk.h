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

namespace Codri {
    class Kiosk : public QObject {
        Q_OBJECT
    public:
        // Construction and destruction
        explicit Kiosk(QObject *iParent);

        // Power enum
        enum Status {
            ON,
            OFF
        };

        // Basic I/O
        Kiosk::Status getStatus() const;
        void setStatus(Kiosk::Status iStatus);
        QUuid getUuid() const;
        void setUuid(const QUuid& iUuid);
        QString getVendor() const;
        void setVendor(const QString& iVendor);
        QString getModel() const;
        void setModel(const QString& iModel);
        unsigned short getPort() const;
        void setPort(unsigned short iPort);

        // Signals
    signals:
        void onStatusChanged(Kiosk::Status iPower);

    private:
        // Member data
        Status mStatus;
        QUuid mUuid;
        QString mVendor, mModel;
        unsigned short mPort;

        // Subsystem objects
        Log4Qt::Logger *mLogger;
    };
}

#endif  // STATE_KIOSK_H_
