//
// Configuration
//

// Include guard
#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

// Library includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
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
        NetworkInterface(QObject *parent = 0) throw(QException);

    private:
        // Data members
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;
        Herqq::Upnp::HDeviceHost* mDeviceHost;
    };
}

#endif // USERINTERFACE_H
