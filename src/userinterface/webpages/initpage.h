//
// Configuration
//

// Include guard
#ifndef INITPAGE_H
#define INITPAGE_H

// Library includes
#include <QtCore/QObject>

// Local incudes
#include "userinterface/webpage.h"

namespace MIRA
{
    class InitPage : public WebPage
    {
    Q_OBJECT
    public:
        // Construction and destruction
        InitPage(QObject *iParent);
    };
}

#endif // INITPAGE_H
