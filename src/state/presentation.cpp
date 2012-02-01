//
// Configuration
//

// Local includes
#include "presentation.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

Presentation::Presentation(QObject *iParent) : QObject(iParent)
{
}


//
// Basic I/O
//

unsigned long Presentation::getRevision() const
{
    return mRevision;
}

void Presentation::setRevision(unsigned long iRevision)
{
    mRevision = iRevision;
    emit onRevisionChanged(iRevision);
}

QString Presentation::getLocation() const
{
    return mLocation;
}

void Presentation::setLocation(const QString &iLocation)
{
    mLocation = iLocation;
    emit onLocationChanged(iLocation);
}
