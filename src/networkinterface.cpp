//
// Configuration
//

// Local includes
#include "networkinterface.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

NetworkInterface::NetworkInterface(QObject *iParent) throw(QException) : QObject(iParent)
{
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup("NetworkInterface");

    // Setup logging
    mLogger =  Log4Qt::Logger::logger("NetworkInterface");
    mLogger->trace() << Q_FUNC_INFO;

    // Create and start the device
    mDevice = new KioskDevice(this);
    mLogger->debug() << "Starting UPnP device";
    mDevice->start();

    // Connect the signals
    connect(mDevice->configurationService(), SIGNAL(setRevision(unsigned long)), this, SIGNAL(setConfigurationRevision(unsigned long)));
    connect(mDevice->configurationService(), SIGNAL(shutdown()), this, SIGNAL(shutdown()));
    connect(mDevice->configurationService(), SIGNAL(reboot()), this, SIGNAL(reboot()));
    connect(mDevice->configurationService(), SIGNAL(setVolume(unsigned int)), this, SIGNAL(setVolume(unsigned int)));
    connect(mDevice->presentationService(), SIGNAL(setLocation(QString)), this, SIGNAL(setPresentationLocation(QString)));

    // Schedule an alive timer
    mAliveTimer = new QTimer(this);
    connect(mAliveTimer, SIGNAL(timeout()), this, SLOT(_sendAlive()));
    mAliveTimer->start(mSettings->value("alivetimer", 300*1000).toInt());
}

NetworkInterface::~NetworkInterface()
{
    mLogger->trace() << Q_FUNC_INFO;

    mLogger->debug() << "Stopping UPnP device";
    mDevice->stop();
}


//
// Getters and setters
//

QString NetworkInterface::uuid() const
{
    return mDevice->getAttribute(Brisa::BrisaDevice::Udn);
}


//
// Event handlers
//

void NetworkInterface::_sendAlive() const
{
    mLogger->trace() << Q_FUNC_INFO;

    mLogger->debug() << "Sending UPnP alive notice";
    mDevice->doNotify();
}
