//
// Configuration
//

// Local includes
#include "datamanager.h"

// Library includes
#include <svnqt/repository.h>
#include <svnqt/repositorylistener.h>
#include <svnqt/repoparameter.h>
#include <svnqt/targets.h>
#include <svnqt/client_parameter.h>
#include <svnqt/client_update_parameter.h>

// Definitions
#define CHECKOUT_CACHE "/tmp/cache"
#define CHECKOUT_MEMORY "/tmp/memory"

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

DataManager::DataManager(QObject *parent) : QObject(parent)
{
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup("Repository");

    // Setup logging
    mLogger =  Log4Qt::Logger::logger("Repository");
    mLogger->trace() << Q_FUNC_INFO;

    // Configure subversion
    svn::ContextP tSubversionContext;
    mSubversionClient = svn::Client::getobject(0,0);
    tSubversionContext = new svn::Context();
    tSubversionContext->setListener(this);
    mSubversionClient->setContext(tSubversionContext);
}


//
// Functionality
//

QDir DataManager::downloadData(const QString& iIdentifier, const QUrl& iUrl) throw(QException)
{
    mLogger->trace() << Q_FUNC_INFO;

    QDir tCache(CHECKOUT_CACHE);
    if (tCache.exists())
    {
        // Load the cache entries
        tCache.setFilter(QDir::Dirs);
        QStringList tCacheEntries = tCache.entryList();

        // Delete old cache entries?
        bool tCacheHit = false;
        foreach (const QString& tCacheEntry, tCacheEntries)
        {
            if (tCacheEntry == "." || tCacheEntry == "..")
                continue;

            if (tCacheEntry != iIdentifier)
                mLogger->warn() << "detected unknown cache entry '" << tCacheEntry << "'";
            else
                tCacheHit = true;
        }

        // Manage the data
        QDir tCachedMedia(tCache.absolutePath() + '/' + iIdentifier);
        if (tCacheHit)
        {
            mLogger->debug() << "cache hit, updating media";
            _updateRepository(tCachedMedia);
        }
        else
        {
            mLogger->debug() << "cache miss, checking-out media";
            _checkoutRepository(tCachedMedia, iUrl);
        }
        return tCachedMedia;
    }
    else
    {
        mLogger->warn() << "cache does not exist, performing full checkout";

        // Manage the data
        QDir tMedia(CHECKOUT_MEMORY + QString("/") + iIdentifier);
        if (tMedia.exists())
        {
            mLogger->debug() << "memory hit, updating media";
            _updateRepository(tMedia);
        }
        else
        {
            mLogger->debug() << "memory miss, checking-out media";
            _checkoutRepository(tMedia, iUrl);
        }
        return tMedia;
    }
}


//
// Auxiliary
//

void DataManager::_checkoutRepository(const QDir& iDestination, const QUrl& iUrl) throw(QException)
{
    svn::CheckoutParameter tCheckoutParameters;
    tCheckoutParameters
            .moduleName(iUrl.toString())
            .destination(iDestination.absolutePath())
            .revision(svn::Revision::HEAD)
            .peg(svn::Revision::HEAD)
            .depth(svn::DepthInfinity);

    try
    {
        mSubversionClient->checkout(tCheckoutParameters);
    }
    catch (const svn::ClientException& iException)
    {
        throw QException("could not checkout the repository", QException::fromSVNException(iException));
    }

}

void DataManager::_updateRepository(const QDir& iDestination) throw(QException)
{
    svn::UpdateParameter tUpdateParameters;
    tUpdateParameters
            .targets(iDestination.absolutePath())
            .revision(svn::Revision::HEAD)
            .depth(svn::DepthInfinity);

    try
    {
        mSubversionClient->update(tUpdateParameters);
    }
    catch (const svn::ClientException& iException)
    {
        throw QException("could not update the repository", QException::fromSVNException(iException));
    }
}
