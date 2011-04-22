//
// Configuration
//

// Includes
#include "messagepage.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

MessagePage::MessagePage(QObject *parent) : WebPage(QUrl("qrc:/webpages/message.html"), parent)
{
}

MessagePage::~MessagePage()
{
}
