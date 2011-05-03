//
// Configuration
//

// Include guard
#ifndef DATASERVICE_H
#define DATASERVICE_H

// Library includes
#include <HUpnpCore/HServerService>
#include <HUpnpCore/HActionArguments>
#include <Log4Qt/Logger>

class DataService : public Herqq::Upnp::HServerService
{
public:
    // Construction and destruction
    DataService();
    virtual ~DataService();

private:
    // Service interface
    virtual HActionInvokes createActionInvokes();

    // Service actions
    qint32 LoadInterface(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs);
    qint32 SetInterfaceLocation(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs);
    qint32 GetInterfaceRevision(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs);
    qint32 LoadMedia(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs);
    qint32 SetMediaLocation(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs);
    qint32 GetMediaRevision(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs);

    // Data members
    Log4Qt::Logger *mLogger;
};

#endif // DATASERVICE_H
