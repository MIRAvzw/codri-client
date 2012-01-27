//
// Configuration
//

// Include guard
#ifndef WEBSERVICEDISPATCHER_H
#define WEBSERVICEDISPATCHER_H

// Library includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <Log4Qt/Logger>
#include <QxtWeb/QxtHttpSessionManager>

// Local includes
#include "resource.h"

namespace MIRA
{
    class WebserviceDispatcher : public QxtHttpSessionManager
    {
        Q_OBJECT
    public:
        WebserviceDispatcher(const QHostAddress &iHost, quint16 iPort);
        virtual ~WebserviceDispatcher();

        // Functionality
        void addService(QString iUri, Resource* iSubService);

    protected:
        // QxtHttpSessionManager implementation
        void incomingRequest(quint32 iRequestId, const QHttpRequestHeader &iHeader, QxtWebContent *iDeviceContent);

    private:
        // Member data
        Resource* mRootService;

        // Subsystem objects
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;
    };
}

#endif // WEBSERVICEDISPATCHER_H
