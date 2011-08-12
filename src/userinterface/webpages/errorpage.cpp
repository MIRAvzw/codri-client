//
// Configuration
//

// Local includes
#include "errorpage.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

ErrorPage::ErrorPage(QObject *iParent) : WebPage(QUrl("qrc:/webpages/errorpage.html"), iParent)
{
}

ErrorPage::~ErrorPage()
{
}
