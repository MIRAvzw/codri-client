/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef NETWORK_SERVERCLIENT_H_
#define NETWORK_SERVERCLIENT_H_

// Library includes
#include <QtCore/QObject>
#include <QtCore/QStateMachine>
#include <QtCore/QSignalTransition>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <qjson/parser.h>
#include <qjson/serializer.h>

// Local includes
#include "qexception.h"
#include "state/kiosk.h"

namespace Codri {
    class ServerClientPrivate;
    class ServerClient : public QStateMachine {
        Q_OBJECT
    public:
        // Construction and destruction
        ServerClient(const QString& iLocation, QObject *iParent);

        // Construction helpers
    private:
        void initFSM();

        // Public interface
    public slots:
        void registerKiosk();
        void refreshKiosk();
        void unregisterKiosk();

        // Transition signals
        // TODO: these are nasty, but necessary since we can't relay the public slots to a FSM transition directly
    signals:
        void _registerKiosk();
        void _refreshKiosk();
        void _unregisterKiosk();

    signals:
        // Signals
        void registrationSuccess();
        void registrationConflict();
        void registrationFailure(QVariant iError);
        void refreshSuccess();
        void refreshFailure(QVariant iError);
        void unregisterSuccess();
        void unregisterFailure(QVariant iError);

    private:
        // Member data
        ServerClientPrivate *mImplementation;
    };

    class ServerClientPrivate : public QObject {
        Q_OBJECT
    public:
        ServerClientPrivate(const QString& iLocation, QObject *iParent);
        virtual ~ServerClientPrivate();

        // Functionality
    public slots:
        void registerKiosk();
        void refreshKiosk();
        void unregisterKiosk();

    private slots:
        // Private signal handlers
        void _onRequestFinished(QNetworkReply *iReply);

    signals:
        void _onRequestSuccess();
        void _onRequestFailure(unsigned int iErrorCode);

    private:
        // Auxiliary
        void doGET(const QString& iPath);
        void doPUT(const QString& iPath, const QVariant& iPayload = QVariant());
        void doPOST(const QString& iPath, const QVariant& iPayload = QVariant());
        void doDELETE(const QString& iPath);
        QNetworkRequest createRequest(const QString& iPath);

    private:
        // Member data
        QJson::Parser *mParser;
        QJson::Serializer *mSerializer;
        const QString mLocation;
        QNetworkAccessManager *mNetworkAccessManager;

    };

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

    class ComparingSignalTransition : public ParameterizedSignalTransition {
        Q_OBJECT
    public:
        enum Check {
            EQUALITY,
            INEQUALITY
        };

        ComparingSignalTransition(QObject *iSender, const char *iSignal, Check iCheck, int iData)
            : ParameterizedSignalTransition(iSender, iSignal), mCheck(iCheck), mData(iData) {
        }

    protected:
        // TODO: compare to array
        bool eventTest(QEvent *iEvent) {
            if (!QSignalTransition::eventTest(iEvent))
                return false;
            QStateMachine::SignalEvent *tSignalEvent = static_cast<QStateMachine::SignalEvent*>(iEvent);
            if (tSignalEvent->arguments().size() == 1 && tSignalEvent->arguments().at(0).canConvert(QVariant::Int)) {
                int iData = tSignalEvent->arguments().at(0).toInt();
                switch (mCheck) {
                case EQUALITY:
                    return (mData == iData);
                case INEQUALITY:
                    return (mData != iData);
                default:
                    return false;
                }
            }
            return false;
        }

    private:
        const Check mCheck;
        const int mData;
    };
}

#endif  // NETWORK_SERVERCLIENT_H_
