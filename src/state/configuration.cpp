//
// Configuration
//

// Local includes
#include "configuration.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

Configuration::Configuration(QObject *iParent) : QObject(iParent)
{
}


//
// Basic I/O
//

unsigned long Configuration::getRevision() const
{
    return mRevision;
}

void Configuration::setRevision(unsigned long iRevision)
{
    mRevision = iRevision;
}

unsigned short Configuration::getVolume() const
{
    return mVolume;
}

void Configuration::setVolume(unsigned char iVolume)
{
    mVolume = iVolume;
    emit onVolumeChanged(iVolume);
}
