//
// Configuration
//

// Include guard
#ifndef USERINTERFACE_H
#define USERINTERFACE_H

// System includes
#include <QtCore/QObject>
#include <QtCore/QSettings>

// Local includes
#include "logger.h"

namespace MIRA
{
    class UserInterface : QObject
    {
    Q_OBJECT
    public:
        // Construction and destruction
        UserInterface(QObject *parent = 0);

    private:
        // Member objects
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;
    };
}

#endif // USERINTERFACE_H
