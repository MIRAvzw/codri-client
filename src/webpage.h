//
// Configuration
//

// Include guard
#ifndef WEBPAGE_H
#define WEBPAGE_H

// System includes
#include <QObject>
#include <QtWebKit/QWebPage>

// Local incudes
#include "logger.h"

namespace MIRA
{
    class WebPage : public QWebPage
    {
    Q_OBJECT
    public:
        // Construction and destruction
        WebPage(QObject* parent = 0);
        ~WebPage();

        // QWebPage interface
    protected:
        void javaScriptConsoleMessage(const QString& iMessage, int iLineNumber, const QString& iSourceId);

    protected:
        Log4Qt::Logger *mLogger;
    };
}

#endif // WEBPAGE_H
