/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef ERRORPAGE_H
#define ERRORPAGE_H

// Library includes
#include <QtCore/QObject>

// Local incudes
#include "userinterface/webpage.h"

namespace MIRA
{
    class ErrorPage : public WebPage
    {
    Q_OBJECT
    public:
        // Construction and destruction
        ErrorPage(QObject *iParent);
    };
}

#endif // ERRORPAGE_H
