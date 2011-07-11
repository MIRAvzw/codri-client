//
// Configuration
//

// Include guard
#ifndef WEBPAGE_H
#define WEBPAGE_H

// Library includes
#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtWebKit/QWebPage>
#include <Log4Qt/Logger>

namespace MIRA
{
    class WebPage : public QWebPage
    {
    Q_OBJECT
    public:
        // Construction and destruction
        WebPage(QUrl iURL, QObject* parent = 0);
        virtual ~WebPage();

        // QWebPage interface
    protected:
        void javaScriptConsoleMessage(const QString& iMessage, int iLineNumber, const QString& iSourceId);

    protected:
        Log4Qt::Logger *mLogger;
    };
}

#endif // WEBPAGE_H
