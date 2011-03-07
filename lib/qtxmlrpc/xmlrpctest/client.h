#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QVariant>


class Client : QObject
{
      Q_OBJECT

public:
      Client( const QString &address, quint16 port, QObject *parent = 0 );

      void testFunc( const QVariant &param );
      QVariant operator()(const QVariant &param);
private slots:
      void onDataReady( const QVariant &response );
      void onError(const QString &errTxt);

private:
      QString address;
      quint16 port;

      bool ready;
      QVariant res;

};

#endif // CLIENT_H
