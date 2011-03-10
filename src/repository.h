//
// Configuration
//

// Include guard
#ifndef REPOSITORY_H
#define REPOSITORY_H

// System includes
#include <QtCore/QObject>
#include <QtCore/QSettings>

// Local includes
#include "logfacility.h"

namespace MIRA
{
    class Repository : QObject
    {
    Q_OBJECT
    public:
        // Construction and destruction
        Repository(QObject *parent = 0);

    private:
        // Member objects
        QSettings *mSettings;
        LogFacility *mLogger;
    };
}

#endif // REPOSITORY_H
