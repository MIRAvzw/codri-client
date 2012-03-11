/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef INITPAGE_H_
#define INITPAGE_H_

// Library includes
#include <QtCore/QObject>

// Local incudes
#include "userinterface/webpage.h"

namespace Codri
{
    class InitPage : public WebPage
    {
    Q_OBJECT
    public:
        // Construction and destruction
        explicit InitPage(QObject *iParent);
    };
}

#endif  // INITPAGE_H_
