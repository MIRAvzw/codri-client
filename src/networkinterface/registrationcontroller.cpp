//
// Configuration
//

// Local includes
#include "registrationcontroller.h"

// Library includes
#include <QtCore/QTimer>

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

RegistrationController::RegistrationController(ServerClient* iServerClient, QObject *iParent) : QStateMachine(iParent), mServerClient(iServerClient)
{
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup("NetworkInterface");

    // Setup logging
    mLogger =  Log4Qt::Logger::logger(metaObject()->className());

    // States
    QState *tRegister = new QState(this);
    QState *tConflict = new QState(this);
    QState *tRefresh = new QState(this);

    // Registering state transitions
    setInitialState(tRegister);
    connect(tRegister, SIGNAL(entered()), mServerClient, SLOT(registerKiosk()));
    tRegister->addTransition(mServerClient, SIGNAL(registrationSuccess()), tRefresh);
    tRegister->addTransition(mServerClient, SIGNAL(registrationConflict()), tConflict);
    QTimer *tRegisterRetry = new QTimer(this);
    tRegisterRetry->setSingleShot(true);
    tRegisterRetry->setInterval(mSettings->value("reconnect", 60*1000).toInt());
    connect(mServerClient, SIGNAL(registrationFailure(QVariant)), tRegisterRetry, SLOT(start()));
    tRegister->addTransition(tRegisterRetry, SIGNAL(timeout()), tRegister);

    // Conflict state transitions
    connect(tConflict, SIGNAL(entered()), mServerClient, SLOT(unregisterKiosk()));
    tConflict->addTransition(mServerClient, SIGNAL(unregisterSuccess()), tRegister);
    QTimer *tConflictRetry = new QTimer(this);
    tConflictRetry->setSingleShot(true);
    tConflictRetry->setInterval(mSettings->value("reconnect", 60*1000).toInt());
    connect(mServerClient, SIGNAL(unregisterFailure(QVariant)), tConflictRetry, SLOT(start()));
    tConflict->addTransition(tConflictRetry, SIGNAL(timeout()), tRegister);

    // Refreshing state transitions
    connect(tRefresh, SIGNAL(entered()), mServerClient, SLOT(refreshKiosk()));
    tRefresh->addTransition(mServerClient, SIGNAL(refreshFailure(QVariant)), tRegister);
    QTimer *tRefreshDelay = new QTimer(this);
    tRefreshDelay->setSingleShot(true);
    tRefreshDelay->setInterval(mSettings->value("heartbeat", 30*1000).toInt());
    connect(mServerClient, SIGNAL(refreshSuccess()), tRefreshDelay, SLOT(start()));
    tRefresh->addTransition(tRefreshDelay, SIGNAL(timeout()), tRefresh);

    // TODO: log state transitions
}
