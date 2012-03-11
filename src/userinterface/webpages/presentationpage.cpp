/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Local includes
#include "presentationpage.h"


//
// Construction and destruction
//

Codri::PresentationPage::PresentationPage(const QDir& iLocation, QObject *iParent) : WebPage("file://" + iLocation.absolutePath() + "/index.html", iParent)
{
}
