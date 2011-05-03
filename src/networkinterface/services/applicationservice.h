//
// Configuration
//

// Include guard
#ifndef APPLICATIONSERVICE_H
#define APPLICATIONSERVICE_H

// Library includes
#include <HUpnpCore/HServerService>
#include <HUpnpCore/HActionArguments>
#include <Log4Qt/Logger>

class ApplicationService : public Herqq::Upnp::HServerService
{
public:
    // Construction and destruction
    ApplicationService();
    virtual ~ApplicationService();

private:
    // Service interface
    virtual HActionInvokes createActionInvokes();

    // Service actions
    qint32 Shutdown(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs);
    qint32 Reboot(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs);
    qint32 GetVolume(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs);
    qint32 SetVolume(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs);

    // Data members
    Log4Qt::Logger *mLogger;
};

#endif // APPLICATIONSERVICE_H
