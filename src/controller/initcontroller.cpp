//
// Configuration
//

// Local includes
#include "initcontroller.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

InitController::InitController(Controller *iController) : QStateMachine(iController), mController(iController)
{    
    // Setup logging
    mLogger =  Log4Qt::Logger::logger(metaObject()->className());

    // Main states
    mStateInitializing = new QStateMachine(this);
    mStateFailed = new QState(this);
    mStateSuccess = new QFinalState(this);
    setInitialState(mStateInitializing);
    mFinished = false;

    // Subsystem states
    mInitNetworkInterface = new QState(mStateInitializing);
    mInitUserInterface = new QState(mStateInitializing);
    mInitDataManager = new QState(mStateInitializing);
    mStateInitializing->setInitialState(mInitUserInterface);

    // User interface transitions
    connect(mInitUserInterface, SIGNAL(entered()), this, SLOT(initializeUserInterface()));
    mInitUserInterface->addTransition(this, SIGNAL(userInterfaceSuccess()), mInitDataManager);
    mStateInitializing->addTransition(this, SIGNAL(userInterfaceFailure()), mStateFailed);

    // Data manager transitions
    connect(mInitDataManager, SIGNAL(entered()), this, SLOT(initializeDataManager()));
    mInitDataManager->addTransition(this, SIGNAL(dataManagerSuccess()), mInitNetworkInterface);
    mStateInitializing->addTransition(this, SIGNAL(dataManagerFailure()), mStateFailed);

    // Network interface transitions
    connect(mInitNetworkInterface, SIGNAL(entered()), this, SLOT(initializeNetworkInterface()));
    mStateInitializing->addTransition(this, SIGNAL(networkInterfaceSuccess()), mStateSuccess);
    mStateInitializing->addTransition(this, SIGNAL(userInterfaceFailure()), mStateFailed);

    // Main transitions
    connect(this, SIGNAL(finished()), this, SLOT(_onFinished()));
    connect(mStateFailed, SIGNAL(entered()), this, SIGNAL(failure()));
    connect(mStateSuccess, SIGNAL(entered()), this, SIGNAL(success()));
}


//
// Initialization slots
//

void InitController::initializeUserInterface()
{
    try
    {
        mController->mUserInterface = new UserInterface();
        connect(mController->mUserInterface, SIGNAL(presentationError(QString)), mController, SLOT(_onPresentationError(QString)));
        mController->mUserInterface->show();

        emit userInterfaceSuccess();
    }
    catch (const QException &iException)
    {
        emit userInterfaceFailure();
    }
}

void InitController::initializeDataManager()
{
    try
    {
        mController->mDataManager = new DataManager(this);

        emit dataManagerSuccess();
    }
    catch (const QException &iException)
    {
        emit dataManagerFailure();
    }
}

void InitController::initializeNetworkInterface()
{
    try
    {
        mController->mNetworkInterface = new NetworkInterface(this);

        emit networkInterfaceSuccess();
    }
    catch (const QException &iException)
    {
        emit networkInterfaceFailure();
    }
}


//
// State machine status
//

void InitController::_onFinished()
{
    // TODO: why isn't this provided?
    mFinished = true;
}

bool InitController::isFinished() const
{
    return mFinished;
}
