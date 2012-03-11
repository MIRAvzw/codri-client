/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef PRESENTATIONPAGE_H_
#define PRESENTATIONPAGE_H_

// Library includes
#include <QtCore/QObject>
#include <QtCore/QDir>

// Local incudes
#include "userinterface/webpage.h"

namespace Codri
{
    class PresentationPage : public WebPage
    {
    Q_OBJECT
    public:
        // Construction and destruction
        PresentationPage(const QDir& iLocation, QObject *iParent);
    };
}

#endif  // PRESENTATIONPAGE_H_
