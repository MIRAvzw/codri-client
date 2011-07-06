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
    connect(mDevice->deviceService(), SIGNAL(volumeChanged(unsigned int)), this, SIGNAL(volumeChanged(unsigned int)));
    connect(mDevice->deviceService(), SIGNAL(interfaceAdded(const QString&)), this, SIGNAL(interfaceAdded(const QSQtring&)));
    connect(mDevice->deviceService(), SIGNAL(interfaceLoad()), this, SIGNAL(interfaceLoad()));
    connect(mDevice->deviceService(), SIGNAL(mediaAdded(const QString&)), this, SIGNAL(mediaAdded(const QSQtring&)));
    connect(mDevice->deviceService(), SIGNAL(mediaLoad()), this, SIGNAL(mediaLoad()));
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
