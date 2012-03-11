/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Local includes
#include "errorpage.h"


//
// Construction and destruction
//

MIRA::ErrorPage::ErrorPage(QObject *iParent) : WebPage(QUrl("qrc:/webpages/errorpage.html"), iParent)
{
}
