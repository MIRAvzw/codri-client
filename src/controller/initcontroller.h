/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef CONTROLLER_INITCONTROLLER_H_
#define CONTROLLER_INITCONTROLLER_H_

// Library includes
#include <QtCore/QObject>
#include <QtCore/QStateMachine>
#include <QtCore/QState>
#include <QtCore/QFinalState>
#include <Log4Qt/Logger>

// Local includes
#include "controller.h"

namespace Codri
{
    class Controller;

    class InitController : public QStateMachine
    {
        Q_OBJECT
    public:
        // Construction and destruction
        explicit InitController(Controller *iController);

    signals:
        // Initialization outcome signals
        void success();
        void failure();

    private slots:
        // Initialization slots
        void initializeUserInterface();
        void initializeDataManager();
        void initializeNetworkInterface();

    signals:
        // Subsystem initialization outcome signals
        void networkInterfaceFailure();
        void networkInterfaceSuccess();
        void userInterfaceFailure();
        void userInterfaceSuccess();
        void dataManagerFailure();
        void dataManagerSuccess();

    private slots:
        // State machine status
        void _onFinished();
    public:
        bool isFinished() const;

    private:
        // Parent controller
        Controller* mController;

        // State machine
        bool mFinished;
        QState *mStateInitializing, *mStateFailed;
        QFinalState *mStateSuccess;
        QState *mInitNetworkInterface, *mInitUserInterface, *mInitDataManager;

        // Subsystem objects
        Log4Qt::Logger *mLogger;
    };
}

#endif  // CONTROLLER_INITCONTROLLER_H_
