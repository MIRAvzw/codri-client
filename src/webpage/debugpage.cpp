//
// Configuration
//

// Includes
#include "debugpage.h"
#include <QtWebKit/QWebFrame>

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

DebugPage::DebugPage(QObject *parent) : QWebPage(parent)
{
    this->mainFrame()->load(QUrl("http://www.google.be"));
}


DebugInterface::DebugInterface(QObject *parent) : QObject(parent)
{

}
