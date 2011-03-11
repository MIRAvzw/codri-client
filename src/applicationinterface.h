//
// Configuration
//

// Include guard
#ifndef APPLICATIONINTERFACE_H
#define APPLICATIONINTERFACE_H

// System includes
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtCore/QSettings>

// Local includes
#include "xmlrpcserver.h"
#include "logger.h"

namespace MIRA
{
    class ApplicationInterface : QObject
    {
    Q_OBJECT
    public:
        // Construction and destruction
        ApplicationInterface(QObject *parent = 0);

    private slots:
        // RPC handlers
        QVariant testFunc(const QVariant &param);

    private:
        // Member objects
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;
        XmlRpcServer *mServer;
    };
}

#endif // APPLICATIONINTERFACE_H
