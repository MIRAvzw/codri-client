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
        connect(mNetworkInterface, SIGNAL(changeVolume(uint)), this, SLOT(_changeVolume(uint)));
        connect(mNetworkInterface, SIGNAL(loadMedia(const QString&, const QString&)), this, SLOT(_loadMedia(const QString&, const QString&)));

        mLogger->debug() << "Initializing user interface";
        mUserInterface = new UserInterface();
        connect(mUserInterface, SIGNAL(quit()), this, SLOT(_quit()));
        connect(mUserInterface, SIGNAL(mediaError(QString)), this, SLOT(_mediaError(QString)));
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

void Controller::_changeVolume(unsigned int iVolume)
{
    mLogger->trace() << Q_FUNC_INFO;

    // TODO: actually change the volume
}

void Controller::_loadMedia(const QString &iMediaIdentifier, const QString &iMediaLocation)
{
    mLogger->trace() << Q_FUNC_INFO;

    // Disable the user interface
    userInterface()->showInit();

    // Checkout the media
    DataManager::DataEntry tMedia;
    try
    {
        // TODO: only delete the data if it differs from the previous time
        //       (save iMediaIdentifier)
        dataManager()->removeMedia();
        tMedia = dataManager()->getMedia(iMediaLocation);
    }
    catch (const QException &tException)
    {
        mLogger->error() << "Could not download the new media" << tException.what();
        foreach (const QString& tCause, tException.causes())
            mLogger->error() << "Caused by: " << tCause;
        return;
    }

    // Show the media
    try
    {
        userInterface()->showMedia(tMedia.Location);
    }
    catch (const QException &tException)
    {
        mLogger->error() << "Could not show the new media" << tException.what();
        foreach (const QString& tCause, tException.causes())
            mLogger->error() << "Caused by: " << tCause;
        userInterface()->showError(tException.what());
        return;
    }
}

void Controller::_mediaError(const QString& iError)
{
    mLogger->trace() << Q_FUNC_INFO;

    mLogger->error("Error on loaded media: " + iError);
    // TODO: revert media or smth
    userInterface()->showError(iError);
}
