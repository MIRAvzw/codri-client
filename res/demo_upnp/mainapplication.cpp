#include "mainapplication.h"
#include "kioskcreator.h"
#include <HUpnpCore/HDeviceHostConfiguration>
#include <HUpnpCore/HDeviceConfiguration>
#include <QDebug>


MainApplication::MainApplication()
{
    Herqq::Upnp::HDeviceHostConfiguration hostConfiguration;

    KioskCreator creator;
    hostConfiguration.setDeviceModelCreator(creator);

    Herqq::Upnp::HDeviceConfiguration config;
    config.setPathToDeviceDescription("kiosk.xml");

    config.setCacheControlMaxAge(30);

    hostConfiguration.add(config);

    m_deviceHost = new Herqq::Upnp::HDeviceHost(this);

    if (!m_deviceHost->init(hostConfiguration))
    {
        qWarning() << m_deviceHost->errorDescription();
        Q_ASSERT(false);
        return;
    }
}
