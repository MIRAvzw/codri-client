/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef AUXILIARY_PARAMETERIZEDSIGNALTRANSITION_H_
#define AUXILIARY_PARAMETERIZEDSIGNALTRANSITION_H_

// Library includes
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtCore/QStateMachine>
#include <QtCore/QSignalTransition>
#include <QtCore/QDebug>

class ParameterizedSignalTransition : public QSignalTransition {
    Q_OBJECT
public:
    ParameterizedSignalTransition(QObject *iSender, const char *iSignal)
        : QSignalTransition(iSender, iSignal) {
        connect(this, SIGNAL(triggered()), this, SLOT(_onTriggered()));
    }

protected:
    bool eventTest(QEvent *iEvent) {
        if (!QSignalTransition::eventTest(iEvent))
            return false;

        QStateMachine::SignalEvent *tSignalEvent = static_cast<QStateMachine::SignalEvent*>(iEvent);
        mData = QVariant();
        if (tSignalEvent->arguments().size() == 1)
            mData = tSignalEvent->arguments().at(0);
        else if (tSignalEvent->arguments().size() > 1)
            qCritical() << "Parameterized signal transition only supports 0 or 1 signal arguments";

        return QSignalTransition::eventTest(iEvent);
    }

private slots:
    void _onTriggered() {
        if (!mData.isNull()) {
            switch (mData.type()) {
            case QVariant::Int:
                emit triggeredInt(mData.toInt());
                break;
            case QVariant::UInt:
                emit triggeredUInt(mData.toUInt());
                break;
            case QVariant::String:
                emit triggeredString(mData.toString());
                break;
            default:
                qWarning() << "Unhandled variant type" << mData.typeName();
                emit triggeredVariant(mData);
                break;
            }
        }
    }

signals:
    void triggeredVariant(QVariant);
    void triggeredInt(int);
    void triggeredUInt(uint);
    void triggeredString(QString);

private:
    QVariant mData;
};

#endif  // AUXILIARY_PARAMETERIZEDSIGNALTRANSITION_H_
