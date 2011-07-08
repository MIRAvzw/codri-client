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

NetworkInterface::NetworkInterface(QObject *parent) throw(QException) : QObject(parent)
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
    connect(mDevice->deviceService(), SIGNAL(shutdown()), this, SIGNAL(shutdown()));
    connect(mDevice->deviceService(), SIGNAL(reboot()), this, SIGNAL(reboot()));
    connect(mDevice->deviceService(), SIGNAL(changeVolume(unsigned int)), this, SIGNAL(changeVolume(unsigned int)));
    connect(mDevice->applicationService(), SIGNAL(loadInterface(const QString&, const QString&)), this, SIGNAL(loadInterface(const QString&, const QString&)));
    connect(mDevice->applicationService(), SIGNAL(loadInterface()), this, SIGNAL(loadInterface()));
    connect(mDevice->applicationService(), SIGNAL(loadMedia(const QString&, const QString&)), this, SIGNAL(loadMedia(const QString&, const QString&)));
    connect(mDevice->applicationService(), SIGNAL(loadMedia()), this, SIGNAL(loadMedia()));
}

NetworkInterface::~NetworkInterface()
{
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
