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
#include <svnqt/info_entry.h>

#include <QDebug>

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

    // Check the cache
    mCache = new QDir(mSettings->value("location", "/tmp/cache").toString());
    if (!mCache->exists() && !QDir().mkpath(mCache->absolutePath()))
        throw new QException("Could not create main cache directory");
    QFileInfo tCacheInfo(mCache->path());
    if (!tCacheInfo.isDir() || !tCacheInfo.isWritable()) {
        throw new QException("Data cache directory does not exist or is not writable");
    }

    // Load the cache subdirectories
    mCacheMedia = new QDir(mCache->filePath(mSettings->value("mediadir", "media").toString()));
}


//
// Functionality
//

DataManager::DataEntry DataManager::getMedia(const QUrl &iUrl) throw(QException)
{
    mLogger->trace() << Q_FUNC_INFO;

    DataEntry tData;
    tData.Location = *mCacheMedia;

    if (mCacheMedia->exists())
    {
        mLogger->debug() << "cache hit, updating media";
        tData.Revision = updateRepository(*mCacheMedia);
    }
    else
    {
        mLogger->debug() << "cache miss, checking-out media";
        tData.Revision = checkoutRepository(*mCacheMedia, iUrl);
    }

    return tData;
}

void DataManager::removeMedia() throw(QException)
{
    if (mCacheMedia->exists() && !removeDirectory(*mCacheMedia))
        throw QException("Could not remove media");
}

DataManager::DataEntry DataManager::getCachedMedia() throw(QException)
{
    svn::Revision tRevision = checkRepository(*mCacheMedia);

    DataEntry tData;
    tData.Location = *mCacheMedia;
    tData.Revision = tRevision;
    return tData;
}


//
// Auxiliary
//

svn::Revision DataManager::checkRepository(const QDir &iSource) throw(QException)
{
    try
    {
        QList<svn::InfoEntry> tInfoEntries =  mSubversionClient->info(
                    iSource.absolutePath(),
                    svn::DepthEmpty,
                    svn::Revision::HEAD);
        if (tInfoEntries.size() != 1)
            throw QException("unexpected amount of info entries");
        return tInfoEntries.first().revision();
    }
    catch (const svn::ClientException &iException)
    {
        throw QException("could not check the repository", QException::fromSVNException(iException));
    }
    catch (const QException &iException)
    {
        throw QException("could not check the repository", iException);
    }
}

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
