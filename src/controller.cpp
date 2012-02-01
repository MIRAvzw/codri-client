//
// Configuration
//

// Local includes
#include "controller.h"
#include "mainapplication.h"
#include "qexception.h"

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

Controller::Controller(QObject *iParent) throw(QException) : QObject(iParent)
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

        mLogger->debug() << "Initializing user interface";
        mUserInterface = new UserInterface();
        connect(mUserInterface, SIGNAL(presentationError(QString)), this, SLOT(_onPresentationError(QString)));
        mUserInterface->show();

        mLogger->debug() << "Initializing data manager";
        mDataManager = new DataManager(this);
    }
    catch (const QException &iException)
    {
        mLogger->fatal() << "Failed to initialize: " << iException.what();
        throw QException(QString("could not load all subsystems"));
    }

    // Initialize state signals
    connect(MainApplication::instance()->kiosk(), SIGNAL(onPowerChanged(Kiosk::Power)), this, SLOT(_onKioskPowerChanged(Kiosk::Power)));
    connect(MainApplication::instance()->configuration(), SIGNAL(onVolumeChanged(unsigned char)), this, SLOT(_onConfigurationVolumeChanged(unsigned char)));
    connect(MainApplication::instance()->presentation(), SIGNAL(onLocationChanged(const QString&)), this, SLOT(_onPresentationLocationChanged(const QString&)));
}

Controller::~Controller()
{
}


//
// Basic I/O
//

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

    // TODO: load default configuration
}

void Controller::stop()
{
    mLogger->trace() << Q_FUNC_INFO;

    mLogger->fatal() << "Fatal error occured, halting application";

    // Clean up
    // FIXME dataManager()->saveConfig();

    // Delete subsystems
    delete mUserInterface;
    delete mNetworkInterface;

    // Actually quit
    MainApplication::instance()->quit();
}


//
// Subsystem object getters
//

NetworkInterface *Controller::networkInterface() const
{
    return mNetworkInterface;
}

UserInterface *Controller::userInterface() const
{
    return mUserInterface;
}

DataManager *Controller::dataManager() const
{
    return mDataManager;
}


//
// Subsystem events
//

void Controller::_onPresentationError(const QString& iError)
{
    mLogger->trace() << Q_FUNC_INFO;

    mLogger->error("Error on loaded media: " + iError);
    // TODO: revert media or smth
}


//
// State events
//

void Controller::_onKioskPowerChanged(Kiosk::Power iPower)
{
    mLogger->trace() << Q_FUNC_INFO;

    switch (iPower)
    {
    case Kiosk::OFF:
        stop();
        break;
    case Kiosk::ON:
        break;
    }
}

void Controller::_onConfigurationVolumeChanged(unsigned char iVolume)
{
    mLogger->trace() << Q_FUNC_INFO;

    // TODO: cache the value

    // TODO: actually change the volume
}

void Controller::_onPresentationLocationChanged(const QString &iLocation)
{
    mLogger->trace() << Q_FUNC_INFO;

    try
    {
        // Disable the current presentation
        // TODO: updating message
        userInterface()->showInit();

        // Download the new presentation
        QPair<QDir, unsigned long> tCheckout = dataManager()->downloadPresentation(iLocation);

        // Show the new presentation
        MainApplication::instance()->presentation()->setRevision(tCheckout.second);
        userInterface()->showPresentation(tCheckout.first);
    }
    catch (const QException &tException)
    {
        mLogger->error() << "Could not download the new presentation: " << tException.what();
        foreach (const QString& tCause, tException.causes())
            mLogger->error() << "Caused by: " << tCause;
        userInterface()->showError("could not download presentation");
        return;
    }
}
