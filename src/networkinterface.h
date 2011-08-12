//
// Configuration
//

// Include guard
#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

// Library includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtCore/QTimer>
#include <Log4Qt/Logger>

// Local includes
#include "qexception.h"
#include "networkinterface/devices/kioskdevice.h"

namespace MIRA
{
    class NetworkInterface : public QObject
    {
    Q_OBJECT
    public:
        // Construction and destruction
        NetworkInterface(QObject *iParent = 0) throw(QException);
        ~NetworkInterface();

        // Getters and setters
        QString uuid() const;

        // Signals
    signals:
        void shutdown();
        void reboot();
        void changeVolume(unsigned int iVolume);
        void loadInterface(const QString &iInterfaceIdentifier, const QString &iIndetraceRole, const QString &iInterfaceLocation);
        void loadMedia(const QString &iMediaIdentifier, const QString &iMediaLocation);

        // Event handlers
    private slots:
        void _sendAlive() const;

    private:
        // Data members
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;
        KioskDevice *mDevice;
        QTimer *mAliveTimer;
    };
}

#endif // USERINTERFACE_H
