//
// Configuration
//

// Include guard
#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

// Library includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
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
        NetworkInterface(QObject *parent = 0) throw(QException);
        ~NetworkInterface();

        // Getters and setters
        QString uuid() const;

        // Signals
    signals:
        void shutdown();
        void reboot();
        void changeVolume(unsigned int iVolume);
        void loadInterface(QString iInterfaceIdentifier, QString iIndetraceRole, QString iInterfaceLocation);
        void loadMedia(QString iMediaIdentifier, QString iMediaLocation);

    private:
        // Data members
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;
        KioskDevice* mDevice;
    };
}

#endif // USERINTERFACE_H
