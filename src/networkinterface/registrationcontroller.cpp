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
    tRegister->addTransition(this, SIGNAL(registrationSuccess()), tRefresh);
    tRegister->addTransition(this, SIGNAL(registrationConflict()), tConflict);
    QTimer *tRegisterRetry = new QTimer(this);
    tRegisterRetry->setSingleShot(true);
    tRegisterRetry->setInterval(mSettings->value("reconnect", 60*1000).toInt());
    connect(this, SIGNAL(registrationFailure()), tRegisterRetry, SLOT(start()));
    tRegister->addTransition(tRegisterRetry, SIGNAL(timeout()), tRegister);

    // Conflict state transitions
    connect(tConflict, SIGNAL(entered()), mServerClient, SLOT(unregisterKiosk()));
    tConflict->addTransition(this, SIGNAL(conflictResolved()), tRegister);
    QTimer *tConflictRetry = new QTimer(this);
    tConflictRetry->setSingleShot(true);
    tConflictRetry->setInterval(mSettings->value("reconnect", 60*1000).toInt());
    connect(this, SIGNAL(conflictRemaining()), tConflictRetry, SLOT(start()));
    tConflict->addTransition(tConflictRetry, SIGNAL(timeout()), tRegister);

    // Refreshing state transitions
    connect(tRefresh, SIGNAL(entered()), mServerClient, SLOT(refreshKiosk()));
    tRefresh->addTransition(this, SIGNAL(refreshFailure()), tRegister);
    QTimer *tRefreshDelay = new QTimer(this);
    tRefreshDelay->setSingleShot(true);
    tRefreshDelay->setInterval(mSettings->value("heartbeat", 30*1000).toInt());
    connect(this, SIGNAL(refreshSuccess()), tRefreshDelay, SLOT(start()));
    tRefresh->addTransition(tRefreshDelay, SIGNAL(timeout()), tRefresh);

    // Server client signals
    // TODO: don't use these functions, but directly connect the serverclient to the fsm transitions?
    connect(mServerClient, SIGNAL(registrationPerformed(bool,uint)), this, SLOT(_onRegistrationPerformed(bool,uint)));
    connect(mServerClient, SIGNAL(unregisterPerformed(bool,uint)), this, SLOT(_onUnregisterPerformed(bool,uint)));
    connect(mServerClient, SIGNAL(refreshPerformed(bool,uint)), this, SLOT(_onRefreshPerformed(bool,uint)));
}


//
// Server client handlers
//

void RegistrationController::_onRegistrationPerformed(bool iSuccess, unsigned int iErrorCode)
{
    if (iSuccess)
    {
        mLogger->info() << "Successfully connected to the server";
        emit registrationSuccess();
    }
    else if (iErrorCode == 409)
    {
        mLogger->warn() << "Kiosk was already registered";
        emit registrationConflict();
    }
    else
    {
        mLogger->warn() << "Error connecting to the server (HTTP error code " << (iErrorCode == 0 ? "unknown" : QString::number(iErrorCode)) << ")";
        emit registrationFailure();
    }
}

void RegistrationController::_onUnregisterPerformed(bool iSuccess, unsigned int iErrorCode)
{
    if (iSuccess)
    {
        mLogger->info() << "Successfully uregistered from the server";
        emit conflictResolved();
    }
    else
    {
        mLogger->warn() << "Error unregistering from the server (HTTP error code " << (iErrorCode == 0 ? "unknown" : QString::number(iErrorCode)) << ")";
        emit conflictRemaining();
    }
}

void RegistrationController::_onRefreshPerformed(bool iSuccess, unsigned int iErrorCode)
{
    if (iSuccess)
    {
        mLogger->info() << "Successfully refreshed the server";
        emit refreshSuccess();
    }
    else
    {
        mLogger->warn() << "Error refreshing the server (HTTP error code " << (iErrorCode == 0 ? "unknown" : QString::number(iErrorCode)) << ")";
        emit refreshFailure();
    }
}
