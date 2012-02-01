//
// Configuration
//

// Local includes
#include "serverclient.h"
#include "mainapplication.h"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

ServerClient::ServerClient(const QString &iLocation, QObject *iParent)
    : QObject(iParent), mLocation(iLocation)
{
    // Network access manager
    mNetworkAccessManager = new QNetworkAccessManager(this);
    connect(mNetworkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(_onRequestFinished(QNetworkReply*)));

    // QJson objects
    mParser = new QJson::Parser();
    mSerializer = new QJson::Serializer();
}

ServerClient::~ServerClient()
{
    // QJson objects
    // FIXME: memory management through Qt semantics
    delete mParser;
    delete mSerializer;
}


//
// Functionality
//


void ServerClient::postKiosk() throw(QException)
{
    const Kiosk *tKiosk = MainApplication::instance()->controller()->kiosk();

    QVariantMap tRequest;
    tRequest["power"] = tKiosk->getPower();
    tRequest["port"] = tKiosk->getPort();

    mRequest = PUT_KIOSK;
    doPOST("/network/kiosks/" + tKiosk->getUuid().toString(), tRequest);
}

void ServerClient::putKiosk() throw(QException)
{
    const Kiosk *tKiosk = MainApplication::instance()->controller()->kiosk();

    mRequest = POST_KIOSK;
    doPUT("/network/kiosks/" + tKiosk->getUuid().toString());
}


//
// Private signal handlers
//


void ServerClient::_onRequestFinished(QNetworkReply *iReply)
{
    // Get reply data
    bool tSuccess = iReply->error() == QNetworkReply::NoError;
    unsigned int tErrorCode = iReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).isNull()
            ? 0
            : iReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();

    // Process different requests
    switch (mRequest)
    {
    case PUT_KIOSK:
        emit connectionPerformed(tSuccess, tErrorCode);
        break;
    case POST_KIOSK:
        emit heartbeatUpdated(tSuccess, tErrorCode);
        break;
    }
}


//
// Auxiliary
//

void ServerClient::doGET(const QString& iPath)
{
    mNetworkAccessManager->get(createRequest(iPath));
}

void ServerClient::doPUT(const QString& iPath, const QVariant& iPayload)
{
    mNetworkAccessManager->put(createRequest(iPath), mSerializer->serialize(iPayload));
}

void ServerClient::doPOST(const QString& iPath, const QVariant& iPayload)
{
    mNetworkAccessManager->post(createRequest(iPath), mSerializer->serialize(iPayload));
}

void ServerClient::doDELETE(const QString& iPath)
{
    mNetworkAccessManager->deleteResource(createRequest(iPath));
}

QNetworkRequest ServerClient::createRequest(const QString& iPath)
{
    QNetworkRequest tRequest;
    tRequest.setUrl(QUrl(mLocation + "/" + iPath));
    tRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    return tRequest;
}
