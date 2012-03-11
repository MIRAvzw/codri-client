/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef ERRORPAGE_H_
#define ERRORPAGE_H_

// Library includes
#include <QtCore/QObject>

// Local incudes
#include "userinterface/webpage.h"

namespace Codri
{
    class ErrorPage : public WebPage
    {
    Q_OBJECT
    public:
        // Construction and destruction
        explicit ErrorPage(QObject *iParent);
    };
}

#endif  // ERRORPAGE_H_
