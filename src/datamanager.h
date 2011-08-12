//
// Configuration
//

// Include guard
#ifndef DATAMANAGER_H
#define DATAMANAGER_H

// Library includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtCore/QList>
#include <QtCore/QDir>
#include <QtCore/QUrl>
#include <Log4Qt/Logger>
#include <svnqt/repositorylistener.h>
#include <svnqt/context_listener.h>
#include <svnqt/client.h>

// Local includes
#include "qexception.h"

namespace MIRA
{
    class DataManager : public QObject, public svn::repository::RepositoryListener, public svn::ContextListener
    {
    Q_OBJECT
    public:
        // ConstructQStringion and destruction
        DataManager(QObject *iParent = 0) throw(QException);

        // Functionality
        QDir downloadData(const QString &iIdentifier, const QUrl &iUrl) throw(QException);

        // Signals

        // Repository listening
        virtual void sendWarning(const QString&msg)
        {
            mLogger->warn() << msg.toAscii().data();
        }
        virtual void sendError(const QString&msg)
        {
            mLogger->error() << msg.toAscii().data();
        }
        virtual bool isCanceld(){return false;}

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
        virtual void contextNotify(const char *,svn_wc_notify_action_t,
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
                                     bool & maySave) { maySave = false; return false; }

    private:
        // Member objects
        QSettings *mSettings;
        Log4Qt::Logger *mLogger;
        svn::Client *mSubversionClient;
        QDir *mCache;

        // Auxiliary
        svn::Revision checkoutRepository(const QDir &iDestination, const QUrl &iUrl) throw(QException);
        svn::Revision updateRepository(const QDir &iDestination) throw(QException);
        bool removeDirectory(const QDir &iDirectory);
    };
}

#endif // DATAMANAGER_H
