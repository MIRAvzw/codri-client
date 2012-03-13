/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef USERINTERFACE_WEBPAGES_PRESENTATIONPAGE_H_
#define USERINTERFACE_WEBPAGES_PRESENTATIONPAGE_H_

// Library includes
#include <QtCore/QObject>
#include <QtCore/QDir>

// Local incudes
#include "user/webpage.h"

namespace Codri {
    class PresentationPage : public WebPage {
    Q_OBJECT
    public:
        // Construction and destruction
        PresentationPage(const QDir& iLocation, QObject *iParent);
    };
}

#endif  // USERINTERFACE_WEBPAGES_PRESENTATIONPAGE_H_
