//
// Configuration
//

// Local includes
#include "kioskdevice.h"

// Namespaces
using namespace MIRA;

//
// Construction and destruction
//

KioskDevice::KioskDevice() : Brisa::BrisaDevice(DEVICE_TYPE,
                                                DEVICE_FRIENDLY_NAME,
                                                DEVICE_MANUFACTURER,
                                                DEVICE_MANUFACTURER_URL,
                                                DEVICE_MODEL_DESCRIPTION,
                                                DEVICE_MODEL_NAME,
                                                DEVICE_MODEL_NUMBER,
                                                DEVICE_MODEL_URL,
                                                DEVICE_SERIAL_NUMBER,
                                                getCompleteUuid())
{
    // Setup logging
    mLogger =  Log4Qt::Logger::logger("KioskDevice");
    mLogger->trace() << Q_FUNC_INFO;

    // Add services
    mApplication = new ApplicationService();
    addService(mApplication);
    mData = new DataService();
    addService(mData);
    // Initialize state variables
    mVolume = getServiceByType("urn:mira-be:service:Application:1")->getVariable("Volume");
    mInterfaceLocation = getServiceByType("urn:mira-be:service:Data:1")->getVariable("InterfaceLocation");
    mInterfaceRevision = getServiceByType("urn:mira-be:service:Data:1")->getVariable("InterfaceRevision");
    mMediaLocation = getServiceByType("urn:mira-be:service:Data:1")->getVariable("MediaLocation");
    mMediaRevision = getServiceByType("urn:mira-be:service:Data:1")->getVariable("MediaRevision");
}

KioskDevice::~KioskDevice()
{

}


void KioskDevice::stateChanged(Brisa::BrisaStateVariable *iVariable)
{
    mLogger->debug() << "State variable changed: " << iVariable->name;
}
