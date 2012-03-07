//
// Configuration
//

// Local includes
#include "initpage.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

InitPage::InitPage(QObject *iParent) : WebPage(QUrl("qrc:/webpages/initpage.html"), iParent)
{
}
