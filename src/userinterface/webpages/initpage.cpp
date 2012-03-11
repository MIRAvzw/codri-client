/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Local includes
#include "initpage.h"


//
// Construction and destruction
//

MIRA::InitPage::InitPage(QObject *iParent) : WebPage(QUrl("qrc:/webpages/initpage.html"), iParent)
{
}
