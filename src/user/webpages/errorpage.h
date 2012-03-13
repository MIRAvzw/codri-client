/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef USERINTERFACE_WEBPAGES_ERRORPAGE_H_
#define USERINTERFACE_WEBPAGES_ERRORPAGE_H_

// Library includes
#include <QtCore/QObject>

// Local incudes
#include "user/webpage.h"

namespace Codri {
    class ErrorPage : public WebPage {
    Q_OBJECT
    public:
        // Construction and destruction
        explicit ErrorPage(QObject *iParent);
    };
}

#endif  // USERINTERFACE_WEBPAGES_ERRORPAGE_H_