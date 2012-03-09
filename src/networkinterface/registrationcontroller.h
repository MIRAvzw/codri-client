//
// Configuration
//

// Include guard
#ifndef REGISTRATIONCONTROLLER_H
#define REGISTRATIONCONTROLLER_H

// Library includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtCore/QStateMachine>
#include <QtCore/QState>
#include <QtCore/QFinalState>
#include <Log4Qt/Logger>

// Local includes
#include "serverclient.h"

namespace MIRA
{
    class RegistrationController : public QStateMachine
    {
        Q_OBJECT
    public:
        // Construction and destruction
        RegistrationController(ServerClient *iServerClient, QObject *iParent);

        // Construction helpers
    private:
        void initFSM();

    signals:
        // State outcome signals
        void registrationSuccess();
        void registrationFailure();
        void registrationConflict();
        void conflictResolved();
        void conflictRemaining();
        void refreshSuccess();
        void refreshFailure();

    private:
        // Member data
        ServerClient* mServerClient;

        // Subsystem objects
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;
    };
}

#endif // REGISTRATIONCONTROLLER_H
