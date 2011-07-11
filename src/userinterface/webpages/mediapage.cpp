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

MediaPage::MediaPage(QObject *parent) : WebPage(QUrl("qrc:/webpages/mediapage.html"), parent)
{
}

MediaPage::~MediaPage()
{
}
