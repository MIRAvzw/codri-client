//
// Configuration
//

// Include guard
#ifndef REPOSITORY_H
#define REPOSITORY_H

// Library includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <Log4Qt/Logger>

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
