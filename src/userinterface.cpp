//
// Configuration
//

// Includes
#include "userinterface.h"
#include <QStringList>
#include "mainapplication.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

UserInterface::UserInterface(QObject *parent) throw(QException) : QObject(parent)
{
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup("UserInterface");

    // Setup logging
    mLogger =  Log4Qt::Logger::logger("UserInterface");
    mLogger->trace() << Q_FUNC_INFO;

    // Read resolution
    QString tResolutionString = mSettings->value("resolution", "800x600").toString();
    QStringList tResolutionPair = tResolutionString.split('x');
    if (tResolutionPair.size() != 2)
        throw QException("invalid resolution string");
}
