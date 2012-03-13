/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef USERINTERFACE_WEBPAGES_INITPAGE_H_
#define USERINTERFACE_WEBPAGES_INITPAGE_H_

// Library includes
#include <QtCore/QObject>

// Local incudes
#include "user/webpage.h"

namespace Codri {
    class InitPage : public WebPage {
    Q_OBJECT
    public:
        // Construction and destruction
        explicit InitPage(QObject *iParent);
    };
}

#endif  // USERINTERFACE_WEBPAGES_INITPAGE_H_