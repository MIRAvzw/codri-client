
//
// Configuration
//

// Include guard
#ifndef KIOSK_H
#define KIOSK_H

// Library includes
#include <QtCore/QObject>
#include <QtCore/QUuid>

namespace MIRA
{
    class Kiosk : public QObject
    {
        Q_OBJECT
    public:
        // Construction and destruction
        Kiosk(QObject *iParent = 0);

        // Power enum
        enum Power {
            ON,
            OFF
        };

        // Basic I/O
        Kiosk::Power getPower() const;
        void setPower(Kiosk::Power iPower);
        QUuid getUuid() const;

        // Signals
    signals:
        void onPowerChanged(Kiosk::Power iPower);

    private:
        // Member data
        Power mPower;
        QUuid mUuid;
    };
}

#endif // KIOSK_H
