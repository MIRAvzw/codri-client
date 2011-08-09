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
        explicit WebPage(const QUrl &iURL, QObject *iParent = 0);
        virtual ~WebPage();

        // Functionality
        void loadFallback();
        void load(const QUrl &iUrl);

        // QWebPage interface
    protected:
        void javaScriptConsoleMessage(const QString &iMessage, int iLineNumber, const QString &iSourceId);

    protected:
        Log4Qt::Logger *mLogger;
        QUrl mFallback;
    };
}

#endif // WEBPAGE_H
