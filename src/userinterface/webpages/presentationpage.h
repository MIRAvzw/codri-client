//
// Configuration
//

// Include guard
#ifndef PRESENTATIONPAGE_H
#define PRESENTATIONPAGE_H

// Library includes
#include <QtCore/QObject>
#include <QtCore/QDir>

// Local incudes
#include "userinterface/webpage.h"

namespace MIRA
{
    class PresentationPage : public WebPage
    {
    Q_OBJECT
    public:
        // Construction and destruction
        PresentationPage(const QDir& iLocation, QObject *iParent = 0);
        ~PresentationPage();
    };
}

#endif // PRESENTATIONPAGE_H