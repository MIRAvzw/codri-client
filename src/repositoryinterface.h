/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef REPOSITORYINTERFACE_H_
#define REPOSITORYINTERFACE_H_

// Library includes
#include <QtCore/QObject>
#include <QtCore/QStateMachine>
#include <QtCore/QSettings>
#include <QtCore/QList>
#include <QtCore/QDir>
#include <QtCore/QUrl>
#include <QtCore/QDebug>
#include <Log4Qt/Logger>
#include <svnqt/repositorylistener.h>
#include <svnqt/context_listener.h>
#include <svnqt/client.h>
#include <svnqt/revision.h>

// Local includes
#include "auxiliary/qexception.h"

namespace Codri {
    class RepositoryInterfacePrivate;
    class RepositoryInterface : public QStateMachine {
    Q_OBJECT
    public:
        // Construction and destruction
        explicit RepositoryInterface(QObject *iParent) throw(QException);

        // Construction helpers
    private:
        void initFSM();

        // Public interface
    public slots:
        void check(const QString& iLocation);
        void recheck();

        // Transition signals
        // TODO: these are nasty, but necessary since we can't relay the public slots to a FSM transition directly
    signals:
        void _check();

        // Internal state and transition slots
        // TODO: these are nasty, but neccesary because:
        // - event/signal parameters are tedious and sometimes can't be connected directly
        // - the state machines don't log state transitions
    private slots:
        void _onExisting();
        void _onExistingSuccess(long long iRevision);
        void _onExistingFailure(const QException &iException);
        void _onCheck();
        void _onUpdate();
        void _onUpdateSuccess(long long iRevision);
        void _onUpdateFailure(const QException &iException);
        void _onCheckout();
        void _onCheckoutSuccess(long long iRevision);
        void _onCheckoutFailure(const QException &iError);

        // Events
    signals:
        void changing();
        void ready(const QDir &iLocation);
        void runtimeFailure();

    private:
        // Member data
        RepositoryInterfacePrivate *mImplementation;
        QDir mCheckout;

        // Proxy data
        QString mLocation;

        // Subsystem objects
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;

        // States
        QState *mIdle;
    };

    class RepositoryInterfacePrivate
            : public QObject, public svn::repository::RepositoryListener, public svn::ContextListener {
        Q_OBJECT
    public:
        // Construction and destruction
        explicit RepositoryInterfacePrivate(QObject *iParent);

        // Functionality
    public slots:
        void exists(const QDir &iCheckout);
        void check(const QDir &iCheckout, const QString &iLocation);
        void update(const QDir &iCheckout);
        void checkout(const QDir &iCheckout, const QString &iLocation);

        // Events
    signals:
        void needsUpdate();
        void needsCheckout();
        void success(long long iRevision);  // svn_revnum_t is a long int, closest QVariant type is long long
        void failure(const QException &iException);

    private:
        // Filesystem helpers
        bool removeDirectory(const QDir &iDirectory);
        void copyDirectory(const QDir &tSource, const QDir &tDestination);

        // Repository listening
        virtual void sendWarning(const QString& iMessage) {
            qWarning() << iMessage.toAscii().data();
        }
        virtual void sendError(const QString& iMessage) {
            qWarning() << iMessage.toAscii().data();
        }
        virtual bool isCanceld() { return false; }

        // Context listening
        virtual void contextProgress(long long int, long long int) {}
        virtual bool contextSslClientCertPwPrompt (QString &, const QString &, bool &) { return false; }
        virtual bool contextLoadSslClientCertPw(QString &, const QString &) { return false; }
        virtual bool contextSslClientCertPrompt (QString &) { return false; }
        virtual svn::ContextListener::SslServerTrustAnswer contextSslServerTrustPrompt(const SslServerTrustData &, apr_uint32_t &)
        { return svn::ContextListener::SslServerTrustAnswer(); }
        virtual bool contextGetLogMessage (QString &, const svn::CommitItemList &) { return false; }
        virtual bool contextCancel() { return false; }
        virtual void contextNotify(const svn_wc_notify_t *) { }
        virtual void contextNotify(const char *, svn_wc_notify_action_t,
                                    svn_node_kind_t,
                                    const char *,
                                    svn_wc_notify_state_t,
                                    svn_wc_notify_state_t,
                                    svn_revnum_t) { }
        virtual bool contextGetSavedLogin(const QString &, QString &, QString &) { return false; }
        virtual bool contextGetCachedLogin(const QString &, QString &, QString &) { return false; }
        virtual bool contextGetLogin(const QString &,
                                     QString &,
                                     QString &,
                                     bool &maySave) {
            maySave = false;
            return false;
        }

    private:
        // Member objects
        svn::Client *mSubversionClient;
    };
}

#endif  // REPOSITORYINTERFACE_H_
