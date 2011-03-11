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
#include "logger.h"

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
        Log4Qt::Logger *mLogger;
    };
}

#endif // REPOSITORY_H
