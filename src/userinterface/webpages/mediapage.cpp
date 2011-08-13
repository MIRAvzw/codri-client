//
// Configuration
//

// Local includes
#include "mediapage.h"

// Namespaces
using namespace MIRA;

#include <QDebug>
//
// Construction and destruction
//

MediaPage::MediaPage(const QDir& iLocation, QObject *iParent) : WebPage("file://" + iLocation.absolutePath() + "/index.html", iParent)
{
}

MediaPage::~MediaPage()
{
    qDebug() << "DESTROY";
}
