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
#include <svnqt/revision.h>

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

DataManager::DataManager(QObject *iParent) throw(QException) : QObject(iParent)
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

    mCache = new QDir(mSettings->value("location", "/tmp/cache").toString());
    if (! mCache->exists())
        QDir().mkdir(mCache->absolutePath());
    QFileInfo tCacheInfo(mCache->path());
    if (!tCacheInfo.isDir() || !tCacheInfo.isWritable()) {
        throw new QException("Data cache directory does not exist or is not writable");
    }
}


//
// Functionality
//

QDir DataManager::downloadData(const QString &iIdentifier, const QUrl &iUrl) throw(QException)
{
    mLogger->trace() << Q_FUNC_INFO;

    // Load the cache entries
    foreach (const QFileInfo &tCacheEntry, mCache->entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs))
    {
        if (tCacheEntry.fileName() != iIdentifier)
        {
            mLogger->debug() << "Removing old cache entry " << tCacheEntry.fileName();
            if (!removeDirectory(tCacheEntry.absoluteFilePath()))
            {
                mLogger->warn() << "Could not remove old cache entry " << tCacheEntry.fileName();
            }
        }
    }

    // Manage the data
    QDir tCachedMedia(mCache->absolutePath() + '/' + iIdentifier);
    if (tCachedMedia.exists())
    {
        mLogger->debug() << "cache hit, updating media";
        updateRepository(tCachedMedia);
    }
    else
    {
        mLogger->debug() << "cache miss, checking-out media";
        checkoutRepository(tCachedMedia, iUrl);
    }
    return tCachedMedia;
}


//
// Auxiliary
//

svn::Revision DataManager::checkoutRepository(const QDir &iDestination, const QUrl &iUrl) throw(QException)
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
        return mSubversionClient->checkout(tCheckoutParameters);
    }
    catch (const svn::ClientException &iException)
    {
        throw QException("could not checkout the repository", QException::fromSVNException(iException));
    }

}

svn::Revision DataManager::updateRepository(const QDir &iDestination) throw(QException)
{
    svn::UpdateParameter tUpdateParameters;
    tUpdateParameters
            .targets(iDestination.absolutePath())
            .revision(svn::Revision::HEAD)
            .depth(svn::DepthInfinity);

    try
    {
        QList<svn::Revision> tRevisions = mSubversionClient->update(tUpdateParameters);
        // TODO: verify that .back() is the latest revision
        return tRevisions.back();
    }
    catch (const svn::ClientException &iException)
    {
        throw QException("could not update the repository", QException::fromSVNException(iException));
    }
}

bool DataManager::removeDirectory(const QDir &iDirectory)
{
    bool tError = false;
    if (iDirectory.exists())
    {
        const QFileInfoList &tEntries = iDirectory.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);
        foreach (const QFileInfo &tEntry, tEntries)
        {
            QString tEntryPath = tEntry.absoluteFilePath();
            if (tEntry.isDir())
            {
                tError = removeDirectory(QDir(tEntryPath));
            }
            else
            {
                QFile tFile(tEntryPath);
                if (!tFile.remove())
                    tError = true;
            }
        }
        if (!iDirectory.rmdir(iDirectory.absolutePath()))
            tError = true;
    }
    return tError;
}
