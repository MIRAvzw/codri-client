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
    mState = UNINITIALIZED;
}


//
// Basic I/O
//

Presentation::State Presentation::getState() const
{
    return mState;
}

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

void Presentation::setLocation(const QString& iLocation, const QDir& iCheckout, unsigned long iRevision)
{
    mLocation = iLocation;
    mCheckout = iCheckout;
    mRevision = iRevision;
    mState = ACTIVE;
    emit onLocationChanged(iLocation, iCheckout, iRevision);
}

QString Presentation::getPendingLocation() const
{
    return mLocation;
}

void Presentation::setPendingLocation(const QString &iPendingLocation)
{
    mPendingLocation = iPendingLocation;
    if (iPendingLocation != "")
    {
        emit onPendingLocationChanged(iPendingLocation);
    }
}
