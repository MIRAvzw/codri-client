//
// Configuration
//

// Include guard
#ifndef DEBUGPAGE_H
#define DEBUGPAGE_H

// System includes
#include <QtWebKit/QWebPage>

namespace MIRA
{
    class DebugPage : public QWebPage
    {
    Q_OBJECT
    public:
        // Construction and destruction
        DebugPage(QObject* parent = 0);
    };

    class DebugInterface : QObject
    {
    Q_OBJECT
    public:
        DebugInterface(QObject* parent = 0);
    };
}

#endif // DEBUGPAGE_H
