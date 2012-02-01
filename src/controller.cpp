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

    // Initialize the kiosk state
    mKiosk = new Kiosk(this);
    connect(mKiosk, SIGNAL(onPowerChanged(Kiosk::Power)), this, SLOT(_onKioskPowerChanged(Kiosk::Power)));

    // Initialize the configuration state
    mConfiguration = new Configuration(this);
    connect(mConfiguration, SIGNAL(onVolumeChanged(unsigned char)), this, SLOT(_onConfigurationVolumeChanged(unsigned char)));

    // Initialize the presentation state
    mPresentation = new Presentation(this);
    connect(mPresentation, SIGNAL(onLocationChanged(QString&, QDir&, unsigned long)), this, SLOT(_onPresentationLocationChanged(QString&, QDir&, unsigned long)));
    connect(mPresentation, SIGNAL(onPendingLocationChanged(QString&)), this, SLOT(_onPresentationPendingLocationChanged(QString&)));
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
// State getters
//

Kiosk *Controller::kiosk() const
{
    return mKiosk;
}

Configuration *Controller::configuration() const
{
    return mConfiguration;
}

Presentation *Controller::presentation() const
{
    return mPresentation;
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

void Controller::_onPresentationPendingLocationChanged(const QString &iLocation)
{
    mLogger->trace() << Q_FUNC_INFO;
    // TODO: check for errors

    try
    {
        if (mPresentation->getState() == Presentation::ACTIVE)
        {
            // Manage the checkout directory
            QDir tPendingCheckout = QDir::temp().absoluteFilePath("pendingPresentation");
            dataManager()->removeDirectory(tPendingCheckout);

            // Check if we need to update or get a new copy
            unsigned long tRevision;
            if (dataManager()->getRepositoryLocation(mPresentation->getCheckout()) == iLocation)
            {
                // Copy current presentation to temporary directory
                dataManager()->copyDirectory(mPresentation->getCheckout(), tPendingCheckout);

                // Update the copy
                tRevision = dataManager()->updateRepository(tPendingCheckout);
            }
            else
            {
                // Do a full checkout
                tRevision = dataManager()->checkoutRepository(tPendingCheckout, iLocation);
            }

            // Disable the current presentation
            // TODO: updating message
            userInterface()->showInit();
            // TODO: check errors
            dataManager()->removeDirectory(mPresentation->getCheckout());

            // Put the new copy in place
            // TODO: this can easily fail (if on other partition)
            tPendingCheckout.rename(tPendingCheckout.absolutePath(), mPresentation->getCheckout().absolutePath());

            mPresentation->setPendingLocation("");
            mPresentation->setLocation(iLocation, mPresentation->getCheckout(), tRevision);
        }
        else
        {
            // Manage the checkout directory
            // TODO: choose appropriate directory here
            QDir tCheckout = QDir::temp().absoluteFilePath("presentation");
            dataManager()->removeDirectory(tCheckout);

            // Do a full checkout
            unsigned long tRevision = dataManager()->checkoutRepository(tCheckout, iLocation);

            mPresentation->setPendingLocation("");
            mPresentation->setLocation(iLocation, iLocation, tRevision);
        }
    }
    catch (const QException &tException)
    {
        mLogger->error() << "Could not download the new presentation: " << tException.what();
        foreach (const QString& tCause, tException.causes())
            mLogger->error() << "Caused by: " << tCause;
        // FIXME: no error, keep previous (cached) presentation
        userInterface()->showError("could not download presentation");
        return;
    }
}

void Controller::_onPresentationLocationChanged(const QString &iLocation, const QDir &iCheckout, unsigned long iRevision)
{
    // Show the media
    userInterface()->showPresentation(iCheckout);
}
