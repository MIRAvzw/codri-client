#ifndef SAMPLEAPPLICATION_H
#define SAMPLEAPPLICATION_H

#include <QObject>

class SampleApplication : public QObject
{
    Q_OBJECT
public:
    explicit SampleApplication(QObject *parent = 0);

signals:
    void done();

public slots:
    void run();

};

#endif // SAMPLEAPPLICATION_H
