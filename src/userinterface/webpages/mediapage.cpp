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

MediaPage::MediaPage(QObject *iParent) : WebPage(QUrl("qrc:/webpages/mediapage.html"), iParent)
{
}

MediaPage::~MediaPage()
{
}
