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

namespace Codri {
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
            if (tSignalEvent->arguments().size() == 1 && tSignalEvent->arguments().at(0).canConvert(QVariant::Int))
                mData = tSignalEvent->arguments().at(0).toInt();

            return QSignalTransition::eventTest(iEvent);
        }

    private slots:
        void _onTriggered() {
            emit dataTriggered(mData);
        }

    signals:
        void dataTriggered(QVariant);

    private:
        QVariant mData;
    };
}

#endif  // AUXILIARY_PARAMETERIZEDSIGNALTRANSITION_H_
