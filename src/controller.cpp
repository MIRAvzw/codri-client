//
// Configuration
//

// Local includes
#include "controller.h"
#include "mainapplication.h"

// Library includes
#include <QtGui/QDesktopServices>
#include <QtCore/QDir>
#include <QtCore/QStringBuilder>
#include <QtCore/QTimer>
#include <Log4Qt/TTCCLayout>
#include <Log4Qt/ConsoleAppender>

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

Controller::Controller(QObject* iParent) throw(QException) : QObject(iParent)
{
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup("Controller");

    // Setup logging
    mLogger =  Log4Qt::Logger::logger("Controller");
    mLogger->trace() << Q_FUNC_INFO;

    // Mark startup time
    mTimestampStartup = QDateTime::currentDateTime();

    // Initialize subsystems
    mLogger->debug() << "Loading subsystems";
    try
    {
        mLogger->debug() << "Initializing network interface";
        mNetworkInterface = new NetworkInterface(this);
        connect(mNetworkInterface, SIGNAL(shutdown()), this, SLOT(_shutdown()));
        connect(mNetworkInterface, SIGNAL(reboot()), this, SLOT(_reboot()));
        connect(mNetworkInterface, SIGNAL(volumeChanged(uint)), this, SLOT(_volumeChanged(uint)));
        connect(mNetworkInterface, SIGNAL(interfaceAdded(const QString&)), this, SLOT(_interfaceAdded(const QString&)));
        connect(mNetworkInterface, SIGNAL(interfaceLoad()), this, SLOT(_interfaceLoad()));
        connect(mNetworkInterface, SIGNAL(interfaceAdded(const QString&)), this, SLOT(_interfaceAdded(const QString&)));
        connect(mNetworkInterface, SIGNAL(interfaceLoad()), this, SLOT(_interfaceLoad()));

        mLogger->debug() << "Initializing user interface";
        mUserInterface = new UserInterface();
        mUserInterface->show();

        mLogger->debug() << "Initializing data manager";
        mDataManager = new DataManager(this);
    }
    catch (const QException& iException)
    {
        mLogger->fatal() << "Failed to initialize: " << iException.what();
        throw QException("could not load all subsystems");
    }
}

Controller::~Controller()
{
}


//
// Basic I/O
//

QUuid Controller::uuid() const
{
    return mNetworkInterface->uuid();
}

QDateTime Controller::startup() const
{
    return mTimestampStartup;
}


//
// Application control
//

void Controller::start()
{
    mLogger->trace() << Q_FUNC_INFO;

    // TODO: make sure this only runs if all subsystems are initialized
    // TODO: make sure the subsystems are only interconnected here (e.g. webpage cannot show
    //       the networkinterface's uuid yet

    mLogger->info() << "Initialisation completed successfully, all functionality should be operational";

}

void Controller::stop()
{
    mLogger->trace() << Q_FUNC_INFO;

    mLogger->fatal() << "Fatal error occured, halting application";

    // Clean up

    // Delete subsystems
    delete mUserInterface;
    delete mNetworkInterface;

    // Actually quit
    MainApplication::instance()->quit();
}


//
// Subsystem object getters
//

NetworkInterface* Controller::networkInterface() const
{
    return mNetworkInterface;
}

UserInterface* Controller::userInterface() const
{
    return mUserInterface;
}


//
// Subsystem events
//

void Controller::_shutdown()
{
    mLogger->trace() << Q_FUNC_INFO;

}

void Controller::_reboot()
{
    mLogger->trace() << Q_FUNC_INFO;

}

void Controller::_volumeChanged(unsigned int iVolume)
{
    mLogger->trace() << Q_FUNC_INFO;

}

void Controller::_interfaceAdded(const QString& iInterface)
{
    mLogger->trace() << Q_FUNC_INFO;

}

void Controller::_interfaceLoad()
{
    mLogger->trace() << Q_FUNC_INFO;

}

void Controller::_mediaAdded(const QString& iMedia)
{
    mLogger->trace() << Q_FUNC_INFO;

}

void Controller::_mediaLoad()
{
    mLogger->trace() << Q_FUNC_INFO;

}
