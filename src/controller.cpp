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
        connect(mNetworkInterface, SIGNAL(shutdown()), this, SLOT(_shutdown()));
        connect(mNetworkInterface, SIGNAL(reboot()), this, SLOT(_reboot()));
        connect(mNetworkInterface, SIGNAL(setVolume(uint)), this, SLOT(_setVolume(uint)));
        connect(mNetworkInterface, SIGNAL(setConfigurationRevision(unsigned long)), this, SLOT(_setConfigurationRevision(unsigned long)));
        connect(mNetworkInterface, SIGNAL(setPresentationLocation(const QString&)), this, SLOT(_setPresentationLocation(const QString&)));

        mLogger->debug() << "Initializing user interface";
        mUserInterface = new UserInterface();
        connect(mUserInterface, SIGNAL(quit()), this, SLOT(_quit()));
        connect(mUserInterface, SIGNAL(mediaError(QString)), this, SLOT(_presentationError(QString)));
        mUserInterface->show();

        mLogger->debug() << "Initializing data manager";
        mDataManager = new DataManager(this);
    }
    catch (const QException &iException)
    {
        mLogger->fatal() << "Failed to initialize: " << iException.what();
        throw QException(QString("could not load all subsystems"));
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

DataManager::Presentation Controller::presentation() const
{
    return mPresentation;
}

DataManager::Configuration Controller::configuration() const
{
    return mConfiguration;
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

    // Load the configuration (this also provides the default configuration)
    _setVolume(dataManager()->config("device/volume", 255).toInt());
    _setConfigurationRevision(dataManager()->config("device/revision", 0).toULongLong());
    if (dataManager()->containsConfig("media/location"))
    {
        loadCachedMedia();
    }
    else
    {
        mPresentation.Location = "none";
        mPresentation.Revision = 0;
    }
}

void Controller::stop()
{
    mLogger->trace() << Q_FUNC_INFO;

    mLogger->fatal() << "Fatal error occured, halting application";

    // Clean up
    dataManager()->saveConfig();

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

void Controller::_quit()
{
    mLogger->trace() << Q_FUNC_INFO;
    stop();
}

void Controller::_shutdown()
{
    mLogger->trace() << Q_FUNC_INFO;

    // TODO: actually change the volume
}

void Controller::_reboot()
{
    mLogger->trace() << Q_FUNC_INFO;

    // TODO: actually reboot
}

void Controller::_setVolume(unsigned int iVolume)
{
    mLogger->trace() << Q_FUNC_INFO;

    // Cache the value
    dataManager()->setConfig("device/volume", iVolume);

    // TODO: actually change the volume
}

void Controller::_setConfigurationRevision(unsigned long iConfigurationRevision)
{
    mLogger->trace() << Q_FUNC_INFO;

    mConfiguration.Revision = iConfigurationRevision;
    dataManager()->config("device/revision", (unsigned long long) iConfigurationRevision);

}

void Controller::_setPresentationLocation(const QString &iMediaLocation)
{
    mLogger->trace() << Q_FUNC_INFO;

    // Disable the user interface
    userInterface()->showInit();

    // Load the data from a remote source
    try
    {
        // Delete the media if the identifier changed
        if (! dataManager()->containsConfig("media/location") || dataManager()->config("media/location").toString() != iMediaLocation)
        {
            mLogger->debug() << "Clearing";
            dataManager()->removeMedia();
            mPresentation = dataManager()->getRemoteMedia(iMediaLocation);
        }
        else
        {
            try
            {
                mPresentation = dataManager()->getRemoteMedia(iMediaLocation);
            }
            catch (const QException &tException)
            {
                mLogger->warn() << "Incremental download failed, trying with a clean cache now";
                dataManager()->removeMedia();
                mPresentation = dataManager()->getRemoteMedia(iMediaLocation);
            }
        }
    }
    catch (const QException &tException)
    {
        mLogger->error() << "Could not download the new media: " << tException.what();
        foreach (const QString& tCause, tException.causes())
            mLogger->error() << "Caused by: " << tCause;
        userInterface()->showError("could not download media");
        return;
    }

    // Cache the values
    dataManager()->setConfig("media/location", mPresentation.Location);
    dataManager()->setConfig("media/revision", (unsigned long long) mPresentation.Revision);

    // Show the media
    userInterface()->showPresentation(dataManager()->getMediaLocation());
}

void Controller::_presentationError(const QString& iError)
{
    mLogger->trace() << Q_FUNC_INFO;

    mLogger->error("Error on loaded media: " + iError);
    // TODO: revert media or smth
}


//
// Auxiliary
//

void Controller::loadCachedMedia()
{
    mLogger->trace() << Q_FUNC_INFO;

    // Disable the user interface
    userInterface()->showInit();

    // Check the media
    try
    {
        mPresentation = dataManager()->getCachedMedia();
    }
    catch (const QException& tException)
    {
        mLogger->error() << "Could not load the cached media" << tException.what();
        foreach (const QString& tCause, tException.causes())
            mLogger->error() << "Caused by: " << tCause;
        userInterface()->showError("could not load cached media");

        mPresentation.Revision = 0;

        return;
    }

    // Show the media
    userInterface()->showPresentation(dataManager()->getMediaLocation());
}
