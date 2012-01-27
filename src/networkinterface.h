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
#include "networkinterface/webservicedispatcher.h"

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
        void setConfigurationRevision(const unsigned long iRevision);
        void shutdown();
        void reboot();
        void setVolume(unsigned int iVolume);
        void setPresentationLocation(const QString &iMediaLocation);

    private:
        // Subsystem objects
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;
        QTimer *mAliveTimer;
        WebserviceDispatcher *mWebserviceDispatcher;
    };
}

#endif // USERINTERFACE_H
