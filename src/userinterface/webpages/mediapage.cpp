//
// Configuration
//

// Local includes
#include "mediapage.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

MediaPage::MediaPage(QObject *iParent) : WebPage(QUrl("about:none"), iParent)
{
}

MediaPage::~MediaPage()
{
}
