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
        ErrorPage(QObject *iParent = 0);
    };
}

#endif // ERRORPAGE_H
