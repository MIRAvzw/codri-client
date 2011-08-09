//
// Configuration
//

// Include guard
#ifndef MEDIAPAGE_H
#define MEDIAPAGE_H

// Library includes
#include <QtCore/QObject>

// Local incudes
#include "userinterface/webpage.h"

namespace MIRA
{
    class MediaPage : public WebPage
    {
    Q_OBJECT
    public:
        // Construction and destruction
        MediaPage(QObject *iParent = 0);
        ~MediaPage();
    };
}

#endif // MEDIAPAGE_H
