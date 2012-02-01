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
#include "networkinterface/serverclient.h"

namespace MIRA
{
    class NetworkInterface : public QObject
    {
    Q_OBJECT
    public:
        // Construction and destruction
        NetworkInterface(QObject *iParent = 0) throw(QException);
        ~NetworkInterface();

    signals:
        // Signals
        void onServerConnected();
        void onServerDisconnected();    // TODO: can happen due to heartbeat not working, or server="" put (server exits); OR ONLY DUE TO TIMEOUT?

    private slots:
        // Private signal handlers
        void _onConnectionTimeout();
        void _onConnectionPerformed(bool iSuccess, unsigned int iErrorCode);
        void _onHeartbeatTimeout();
        void _onHeartbeatUpdated(bool iSuccess, unsigned int iErrorCode);

    private:
        // Subsystem objects
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;
        WebserviceDispatcher *mWebserviceDispatcher;
        ServerClient *mServerClient;

        // Timers
        QTimer *mConnectionTimer;
        QTimer *mHeartbeatTimer;
    };
}

#endif // USERINTERFACE_H
