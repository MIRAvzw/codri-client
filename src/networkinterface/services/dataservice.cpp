//
// Configuration
//

// Local includes
#include "dataservice.h"

// Library includes
#include <HUpnpCore/HServerAction>
#include <HUpnpCore/HServerStateVariable>


//
// Construction and destruction
//

DataService::DataService()
{

}

DataService::~DataService()
{

}


//
// Service interface
//

Herqq::Upnp::HServerService::HActionInvokes DataService::createActionInvokes()
{
    Herqq::Upnp::HServerService::HActionInvokes retVal;

    retVal.insert("LoadInterface", Herqq::Upnp::HActionInvoke(this, &DataService::LoadInterface));
    retVal.insert("SetInterfaceLocation", Herqq::Upnp::HActionInvoke(this, &DataService::SetInterfaceLocation));
    retVal.insert("GetInterfaceRevision", Herqq::Upnp::HActionInvoke(this, &DataService::GetInterfaceRevision));
    retVal.insert("LoadMedia", Herqq::Upnp::HActionInvoke(this, &DataService::LoadMedia));
    retVal.insert("SetMediaLocation", Herqq::Upnp::HActionInvoke(this, &DataService::SetMediaLocation));
    retVal.insert("GetMediaRevision", Herqq::Upnp::HActionInvoke(this, &DataService::GetMediaRevision));

    return retVal;
}


//
// Service methods
//

qint32 DataService::LoadInterface(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs)
{
    int tInterfaceRevisionValue = stateVariables().value("InterfaceRevision")->value().toInt();

    tInterfaceRevisionValue++;
    stateVariables().value("Volume")->setValue(tInterfaceRevisionValue);

    return Herqq::Upnp::UpnpSuccess;
}

qint32 DataService::SetInterfaceLocation(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs)
{
    Herqq::Upnp::HActionArgument iInterfaceLocationValue = inArgs.get("iInterfaceLocationValue");

    stateVariables().value("InterfaceLocation")->setValue(iInterfaceLocationValue.value().toString());

    return Herqq::Upnp::UpnpSuccess;

}

qint32 DataService::GetInterfaceRevision(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs)
{
    int tInterfaceRevisionValue = stateVariables().value("InterfaceRevision")->value().toInt();
    outArgs->setValue("oInterfaceRevisionValue", tInterfaceRevisionValue);

    return Herqq::Upnp::UpnpSuccess;
}

qint32 DataService::LoadMedia(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs)
{
    int tMediaRevisionValue = stateVariables().value("MediaRevision")->value().toInt();

    tMediaRevisionValue++;
    stateVariables().value("MediaRevision")->setValue(tMediaRevisionValue);

    return Herqq::Upnp::UpnpSuccess;
}

qint32 DataService::SetMediaLocation(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs)
{
    Herqq::Upnp::HActionArgument iMediaLocationValue = inArgs.get("iMediaLocationValue");

    stateVariables().value("MediaLocation")->setValue(iMediaLocationValue.value().toString());

    return Herqq::Upnp::UpnpSuccess;
}

qint32 DataService::GetMediaRevision(const Herqq::Upnp::HActionArguments& inArgs, Herqq::Upnp::HActionArguments* outArgs)
{
    int oMediaRevisionValue = stateVariables().value("MediaRevision")->value().toInt();
    outArgs->setValue("oMediaRevisionValue", oMediaRevisionValue);

    return Herqq::Upnp::UpnpSuccess;

}
