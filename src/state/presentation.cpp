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

QDir Presentation::getCheckout() const
{
    return mCheckout;
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

void Presentation::setContents(const QDir& iCheckout, unsigned long iRevision)
{
    mCheckout = iCheckout;
    mRevision = iRevision;
    emit onContentsChanged(iCheckout, iRevision);
}
