//
// Configuration
//

// Local includes
#include "presentationpage.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

PresentationPage::PresentationPage(const QDir& iLocation, QObject *iParent) : WebPage("file://" + iLocation.absolutePath() + "/index.html", iParent)
{
}
