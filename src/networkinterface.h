//
// Configuration
//

// Include guard
#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

// Library includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtCore/QUuid>
#include <HUpnpCore/HDeviceHost>
#include <Log4Qt/Logger>

// Local includes
#include "qexception.h"

namespace MIRA
{
    class NetworkInterface : public QObject
    {
    Q_OBJECT
    public:
        // Construction and destruction
        NetworkInterface(QObject *parent = 0);

        // Subsystem interface
        void init() throw(QException);

        // Getters and setters
        QUuid uuid() const;

        // Network slots
    public slots:
        void deviceCreated(const Herqq::Upnp::HDeviceInfo& iDeviceInfo);
        void serviceCreated(const Herqq::Upnp::HServiceInfo& iServiceInfo, const Herqq::Upnp::HDeviceInfo& iDeviceInfo);

    private:
        // Data members
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;
        Herqq::Upnp::HDeviceHost* mDeviceHost;
        QUuid mUuid;
    };
}

#endif // USERINTERFACE_H
