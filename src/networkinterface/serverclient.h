//
// Configuration
//

// Include guard
#ifndef SERVERCLIENT_H
#define SERVERCLIENT_H

// Local includes
#include "qexception.h"
#include "state/kiosk.h"

// Library includes
#include <QtCore/QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <qjson/parser.h>
#include <qjson/serializer.h>

namespace MIRA
{
    class ServerClient : public QObject
    {
        Q_OBJECT
    public:
        // Construction and destruction
        ServerClient(const QString& iLocation, QObject *iParent = 0);
        virtual ~ServerClient();

        // Functionality
        void postKiosk() throw(QException);
        void putKiosk() throw(QException);
        void deleteKiosk() throw(QException);

    signals:
        // Signals
        void connectionPerformed(bool iSuccess, unsigned int iErrorCode);
        void heartbeatUpdated(bool iSuccess, unsigned int iErrorCode);

    private slots:
        // Private signal handlers
        void _onRequestFinished(QNetworkReply *iReply);

    private:
        // Auxiliary
        void doGET(const QString& iPath);
        void doPUT(const QString& iPath, const QVariant& iPayload = QVariant());
        void doPOST(const QString& iPath, const QVariant& iPayload = QVariant());
        void doDELETE(const QString& iPath);
        QNetworkRequest createRequest(const QString& iPath);

        // Request enum
        enum Request {
            PUT_KIOSK,
            POST_KIOSK,
            DELETE_KIOSK
        };

    private:
        // Member data
        QJson::Parser *mParser;
        QJson::Serializer *mSerializer;
        const QString mLocation;
        QNetworkAccessManager *mNetworkAccessManager;
        Request mRequest;
    };
}

#endif // SERVERCLIENT_H
