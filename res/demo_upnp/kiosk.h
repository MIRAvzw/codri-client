#include <HUpnpCore/HServerDevice>
#include <HUpnpCore/HServerService>
#include <HUpnpCore/HActionArguments>

#ifndef KIOSK_H
#define KIOSK_H

class KioskDevice : public Herqq::Upnp::HServerDevice
{
public:
    KioskDevice();
    virtual ~KioskDevice();
};

class HardwareService : public Herqq::Upnp::HServerService
{
public:
    HardwareService();
    virtual ~HardwareService();

private:
    Q_INVOKABLE qint32 Shutdown(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs);
    Q_INVOKABLE qint32 Reboot(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs);
    Q_INVOKABLE qint32 GetVolume(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs);
    Q_INVOKABLE qint32 SetVolume(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs);
};

class SoftwareService : public Herqq::Upnp::HServerService
{
public:
    SoftwareService();
    virtual ~SoftwareService();

private:
    Q_INVOKABLE qint32 LoadInterface(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs);
    Q_INVOKABLE qint32 LoadMedia(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs);
};

#endif // KIOSK_H
