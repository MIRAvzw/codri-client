#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include <HUpnpCore/HDeviceHost>

class MainApplication : public QObject
{
Q_OBJECT
public:
    MainApplication();
    Herqq::Upnp::HDeviceHost* m_deviceHost;
};

#endif // MAINAPPLICATION_H
