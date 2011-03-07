#include <QCoreApplication>
#include <QWaitCondition>
#include <QMutex>
#include "server.h"
#include "client.h"
#include <iostream>

void sleep(int ms)
{
    QMutex mutx;
    QWaitCondition wcond;
    mutx.lock();
    wcond.wait(&mutx,ms);
    mutx.unlock();
}

int main( int argc, char **argv )
{
      QCoreApplication app( argc, argv );

      QString address = "127.0.0.1";
      quint16 port = 8080;

      Server s( address, port );
      Client c( address, port  );

      /* NB: Responses are not syncronized */

      c.testFunc( QVariant( "test" ) );

      //sleep(1000);
      c.testFunc( QVariant( 1 ) );
      //sleep(1000);
      c.testFunc( QVariant( true ) );
      //sleep(1000);
      c.testFunc( QVariant( 1.5 ) );
      //sleep(1000);
      QVariant t = c(QVariant("test as function"));
      std::cout << t.toString().toStdString()<<std::endl;
      QVariantMap m;
      m["one"] = 1;
      m["two"] = 2;
      m["three"] = 3;
      c.testFunc( QVariant( m ) );

      c.testFunc( QVariant( QByteArray("Hello world!") ) );
      //sleep(1000);

      return app.exec();
}

