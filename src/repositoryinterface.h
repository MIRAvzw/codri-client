/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
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
        RepositoryInterface(QObject *iParent) throw(QException);

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

        // Proxy slots
        // TODO: these are nasty, but neccesary since we can't pass parameters directly into the implementation
    private slots:
        void _onCheck();
        void _onUpdate();
        void _onUpdateSuccess(long iRevision);
        void _onUpdateFailure(const QException& iException);
        void _onCheckout();
        void _onCheckoutSuccess(long iRevision);
        void _onCheckoutFailure(const QException& iException);

        // Events
    signals:
        void changing();
        void ready(const QDir& iLocation);
        void failure(const QException& iException);

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
        void check(const QDir& iCheckout, const QString& iLocation);
        void update(const QDir& iCheckout);
        void checkout(const QDir& iCheckout, const QString& iLocation);

        // Events
    signals:
        void needsUpdate();
        void needsCheckout();
        void updateSuccess(long iRevision);
        void updateFailure(const QException& iException);
        void checkoutSuccess(long iRevision);
        void checkoutFailure(const QException iException);

    private:
        // Repository helpers
        QString getRepositoryLocation(const QDir& iCheckout) throw(QException);
        unsigned long getRepositoryRevision(const QDir &iCheckout) throw(QException);
        unsigned long checkoutRepository(const QDir &iCheckout, const QUrl &iUrl) throw(QException);
        unsigned long updateRepository(const QDir &iDestination) throw(QException);

        // Filesystem helpers
        bool removeDirectory(const QDir &iDirectory);
        void copyDirectory(const QDir &tSource, const QDir &tDestination);

        // Repository listening
        virtual void sendWarning(const QString& iMessage) {
            // TODO
            qWarning() << iMessage.toAscii().data();
        }
        virtual void sendError(const QString& iMessage) {
            // TODO
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
