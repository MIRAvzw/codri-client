//
// Configuration
//

// Local includes
#include "networkinterface.h"
#include "networkinterface/kioskcreator.h"

// Library includes
#include <HUpnpCore/HDeviceHostConfiguration>
#include <HUpnpCore/HDeviceConfiguration>

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
    Herqq::Upnp::HDeviceHostConfiguration hostConfiguration;

    // Setup the device model
    KioskCreator creator;
    hostConfiguration.setDeviceModelCreator(creator);

    // Load the device configuration
    Herqq::Upnp::HDeviceConfiguration config;
    config.setPathToDeviceDescription("descriptions/kiosk.xml");
    config.setCacheControlMaxAge(30);
    hostConfiguration.add(config);

    // Create the device
    mDeviceHost = new Herqq::Upnp::HDeviceHost(this);
    if (!mDeviceHost->init(hostConfiguration))
        throw QException("Failed to initialize the network interface: " + mDeviceHost->errorDescription());
}
