//
// Configuration
//

// Local includes
#include "kioskdevice.h"

// Platform includes
#include <sys/ioctl.h>
#include <net/if.h>

// Namespaces
using namespace MIRA;

//
// Construction and destruction
//

KioskDevice::KioskDevice(QObject* iParent) : Brisa::BrisaDevice(DEVICE_TYPE,
                                                                DEVICE_FRIENDLY_NAME,
                                                                DEVICE_MANUFACTURER,
                                                                DEVICE_MANUFACTURER_URL,
                                                                DEVICE_MODEL_DESCRIPTION,
                                                                DEVICE_MODEL_NAME,
                                                                DEVICE_MODEL_NUMBER,
                                                                DEVICE_MODEL_URL,
                                                                DEVICE_SERIAL_NUMBER,
                                                                getHardwareUuid(),
                                                                "",
                                                                "",
                                                                iParent)
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


//
// Auxiliary
//

QUuid KioskDevice::getHardwareUuid() const
{
    // Create an interface request struct
    struct ifreq ifr;
    bzero(&ifr, sizeof(ifr));
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);

    // Open a socket and perform the IOCTL
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    ioctl(fd, SIOCGIFHWADDR, &ifr);
    close(fd);

    // Create an UUID
    QUuid oUuid;
    oUuid.data1 |= (unsigned char) ifr.ifr_hwaddr.sa_data[0] << 24;
    oUuid.data1 |= (unsigned char) ifr.ifr_hwaddr.sa_data[1] << 16;
    oUuid.data1 |= (unsigned char) ifr.ifr_hwaddr.sa_data[2] << 8;
    oUuid.data1 |= (unsigned char) ifr.ifr_hwaddr.sa_data[3];
    oUuid.data2 |= (unsigned char) ifr.ifr_hwaddr.sa_data[4] << 8;
    oUuid.data2 |= (unsigned char) ifr.ifr_hwaddr.sa_data[5];
    oUuid.data4[0] = (oUuid.data4[0] & 0x3F) | 0x80; // UV_DCE
    oUuid.data3 = (oUuid.data3 & 0x0FFF) | 0x1000; // UV_Time (but without the actual timestamp, to persist reboots)
    return oUuid;
}
