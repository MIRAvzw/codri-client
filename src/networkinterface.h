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
        NetworkInterface(QObject *parent = 0);
        ~NetworkInterface();

        // Subsystem interface
        void init() throw(QException);

        // Getters and setters
        QString uuid() const;

    private:
        // Data members
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;
        KioskDevice* mDevice;
    };
}

#endif // USERINTERFACE_H
