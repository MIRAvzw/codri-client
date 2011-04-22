//
// Configuration
//

// Include guard
#ifndef MESSAGEPAGE_H
#define MESSAGEPAGE_H

// System includes
#include <QtCore/QObject>

// Local incudes
#include "webpage.h"

namespace MIRA
{
    class MessagePage : public WebPage
    {
    Q_OBJECT
    public:
        // Construction and destruction
        MessagePage(QObject* parent = 0);
        ~MessagePage();

    signals:
        void newMessage(const QString& iMessage);
    };
}

#endif // MESSAGEPAGE_H
