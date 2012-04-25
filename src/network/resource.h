/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef NETWORK_RESOURCE_H_
#define NETWORK_RESOURCE_H_

// Library includes
#include <QtCore/QString>
#include <QxtWeb/QxtWebServiceDirectory>
#include <QxtWeb/QxtWebRequestEvent>
#include <QxtWeb/QxtWebContent>
#include <log4qt/Logger>

namespace Codri {
    class Resource : public QxtWebServiceDirectory {
    Q_OBJECT
    public:
        // Construction and destruction
        Resource(QxtAbstractWebSessionManager* iSessionManager, QObject* iParent, const QVariant& iClassName = QVariant());
        virtual ~Resource();

    protected:
        // Service methods
        virtual void doGET(const int iSessionId, int iRequestId);
        virtual void doPUT(int iSessionId, int iRequestId, QIODevice *iContent);
        virtual void doPOST(int iSessionId, int iRequestId, QIODevice *iContent);
        virtual void doDELETE(int iSessionId, int iRequestId);

        // Helper methods
        void postError(int iSessionId, int iRequestId, int iErrorCode, QString iErrorMessage);
        void postUnsupportedMethod(int iSessionId, int iRequestId);

    private:
        // QxtWebServiceDirectory implementation
        void indexRequested(QxtWebRequestEvent *iEvent);

        // Auxiliary
        void handleCompleteEvent(QxtWebRequestEvent *iEvent);

    protected:
        // Subsystem objects
        Log4Qt::Logger *mLogger;
    };
}

#endif  // NETWORK_RESOURCE_H_
