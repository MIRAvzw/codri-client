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
    const Kiosk *tKiosk = MainApplication::instance()->kiosk();

    // TODO: duplicate code...
    QVariantMap tRequest;
    tRequest["vendor"] = tKiosk->getVendor();
    tRequest["model"] = tKiosk->getModel();
    /*
    switch (tKiosk->getPower())
    {
    case Kiosk::ON:
        tRequest["power"] = "on";
        break;
    case Kiosk::OFF:
        tRequest["power"] = "off";
        break;
    }
    */
    tRequest["port"] = tKiosk->getPort();

    mRequest = PUT_KIOSK;
    doPOST("/network/kiosks/" + tKiosk->getUuid().toString().replace('{', "").replace('}', ""), tRequest);
}

void ServerClient::putKiosk() throw(QException)
{
    const Kiosk *tKiosk = MainApplication::instance()->kiosk();

    mRequest = POST_KIOSK;
    doPUT("/network/kiosks/" + tKiosk->getUuid().toString().replace('{', "").replace('}', ""));
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
