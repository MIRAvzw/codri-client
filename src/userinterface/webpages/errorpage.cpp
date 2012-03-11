/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "errorpage.h"


//
// Construction and destruction
//

Codri::ErrorPage::ErrorPage(QObject *iParent)
    : WebPage(QUrl("qrc:/webpages/errorpage.html"), iParent)
{
}
