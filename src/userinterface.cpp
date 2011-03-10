//
// Configuration
//

// Includes
#include "userinterface.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

UserInterface::UserInterface(QObject *parent) : QObject(parent)
{
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup("ApplicationInterface");

    // Setup logging
    mLogger =  new LogFacility("ApplicationInterface", this);
    mLogger->trace() << Q_FUNC_INFO;
}
