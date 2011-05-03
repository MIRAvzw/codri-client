//
// Configuration
//

// Local includes
#include "networkinterface.h"
#include "networkinterface/kioskcreator.h"

// Library includes
#include <HUpnpCore/HDeviceHostConfiguration>
#include <HUpnpCore/HDeviceConfiguration>
#include <HUpnpCore/HUdn>

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

NetworkInterface::NetworkInterface(QObject *parent) : QObject(parent)
{
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup("NetworkInterface");

    // Setup logging
    mLogger =  Log4Qt::Logger::logger("NetworkInterface");
    mLogger->trace() << Q_FUNC_INFO;
}


//
// Subsystem interface
//

void NetworkInterface::init() throw(QException)
{
    // Setup the host configuration
    Herqq::Upnp::HDeviceHostConfiguration hostConfiguration;

    // Setup the device model
    mLogger->debug() << "Setting up device model";
    KioskCreator creator;
    hostConfiguration.setDeviceModelCreator(creator);

    // Load the device configuration
    mLogger->debug() << "Loading device configuration";
    Herqq::Upnp::HDeviceConfiguration config;
    config.setPathToDeviceDescription("networkinterface/descriptions/kiosk.xml");
    config.setCacheControlMaxAge(30);
    hostConfiguration.add(config);

    // Create the device
    mLogger->debug() << "Hosting device";
    mDeviceHost = new Herqq::Upnp::HDeviceHost(this);
    if (!mDeviceHost->init(hostConfiguration))
        throw QException("Failed to initialize the network interface: " + mDeviceHost->errorDescription());
}



//
// Network signals
//

void NetworkInterface::deviceCreated(const Herqq::Upnp::HDeviceInfo& iDeviceInfo)
{
    mUuid = iDeviceInfo.udn().value();
}

void NetworkInterface::serviceCreated(const Herqq::Upnp::HServiceInfo& iServiceInfo, const Herqq::Upnp::HDeviceInfo& iDeviceInfo)
{
}


//
// Getters and setters
//

QUuid NetworkInterface::uuid() const
{
    return mUuid;
}
