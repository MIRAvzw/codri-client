//
// Configuration
//

// Include guard
#ifndef APPLICATIONINTERFACE_H
#define APPLICATIONINTERFACE_H

// System includes
#include <QtCore/QObject>
#include <QtCore/QVariant>

// Local includes
#include "xmlrpcserver.h"
#include "logfacility.h"

namespace MIRA
{
    class ApplicationInterface : QObject
    {
    Q_OBJECT
    public:
        // Construction and destruction
        ApplicationInterface(const QString &address, quint16 port, QObject *parent = 0);

    private slots:
        // RPC handlers
        QVariant testFunc(const QVariant &param);

    private:
        // Member objects
        LogFacility *mLogger;
        XmlRpcServer *mServer;
    };
}

#endif // APPLICATIONINTERFACE_H
