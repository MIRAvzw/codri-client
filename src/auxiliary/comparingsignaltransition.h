/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef AUXILIARY_COMPARINGSIGNALTRANSITION_H_
#define AUXILIARY_COMPARINGSIGNALTRANSITION_H_

// Library includes
#include <QtCore/QObject>
#include <QtCore/QStateMachine>

// Local includes
#include "auxiliary/parameterizedsignaltransition.h"

class ComparingSignalTransition : public ParameterizedSignalTransition {
Q_OBJECT
public:
    enum Check {
        EQUALITY,
        INEQUALITY
    };

    ComparingSignalTransition(QObject *iSender, const char *iSignal, Check iCheck, QVariant iData)
        : ParameterizedSignalTransition(iSender, iSignal), mCheck(iCheck), mData(iData) {
    }

protected:
    // TODO: compare to array
    bool eventTest(QEvent *iEvent) {
        if (!QSignalTransition::eventTest(iEvent))
            return false;
        QStateMachine::SignalEvent *tSignalEvent = static_cast<QStateMachine::SignalEvent*>(iEvent);
        if (tSignalEvent->arguments().size() == 1) {
            QVariant iData = tSignalEvent->arguments().at(0);
            switch (mCheck) {
            case EQUALITY:
                return (mData == iData);
            case INEQUALITY:
                return (mData != iData);
            default:
                return false;
            }
        } else {
            qCritical() << "Comparing signal transition requires exactly 1 signal parameter";
        }
        return false;
    }

private:
    const Check mCheck;
    const QVariant mData;
};

#endif  // AUXILIARY_COMPARINGSIGNALTRANSITION_H_
