/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "initpage.h"


//
// Construction and destruction
//

Codri::InitPage::InitPage(QObject *iParent)
    : WebPage(QUrl("qrc:/webpages/initpage.html"), iParent)
{
}
