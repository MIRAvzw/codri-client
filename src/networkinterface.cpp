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
    connect(mDevice->deviceService(), SIGNAL(shutdown()), this, SIGNAL(shutdown()));
    connect(mDevice->deviceService(), SIGNAL(reboot()), this, SIGNAL(reboot()));
    connect(mDevice->deviceService(), SIGNAL(changeVolume(unsigned int)), this, SIGNAL(changeVolume(unsigned int)));
    connect(mDevice->applicationService(), SIGNAL(loadInterface(QString, QString, QString)), this, SIGNAL(loadInterface(QString, QString, QString)));
    connect(mDevice->applicationService(), SIGNAL(loadMedia(QString, QString)), this, SIGNAL(loadMedia(QString, QString)));

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
