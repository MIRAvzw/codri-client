

#include "client.h"
#include "xmlrpcclient.h"

#include <QVariantList>
#include <QtCore/QCoreApplication>
#include <iostream>

Client::Client( const QString &address, quint16 port, QObject *parent )
            : QObject( parent ), address( address ), port( port )
{

}


void Client::testFunc( const QVariant &param )
{
      ready = false;
      XmlRpcClient *client = new XmlRpcClient( address, port );
      connect( client, SIGNAL( dataReady(QVariant) ), this, SLOT( onDataReady(QVariant) ) );
      connect( client, SIGNAL( error(const QString &) ), this, SLOT( onError(const QString &) ) );
      client->execute( "testFunc", QVariantList() << param );
      while(!ready)
          {
              qApp->processEvents();
          }
}


void Client::onDataReady( const QVariant &response )
{
      qDebug() << response;
      ready = true;
      res = response;
      //std::cout<<"Client::onDataReady " << response.toString().toStdString()<<std::endl;
}

void Client::onError(const QString &errTxt)
{
    qDebug() << errTxt;
    ready = true;
    res = QVariant(errTxt);
}

QVariant Client::operator()(const QVariant &param)
{
    ready = false;
    XmlRpcClient *client = new XmlRpcClient( address, port );
    connect( client, SIGNAL( dataReady(QVariant) ), this, SLOT( onDataReady(QVariant) ) );
    connect( client, SIGNAL( error(const QString &) ), this, SLOT( onError(const QString &) ) );
    client->execute( "testFunc", QVariantList() << param );
    while(!ready)
        {
            qApp->processEvents();
        }
    return res;
}
