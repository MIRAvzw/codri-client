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

    // Load the individual caches
    mCacheMedia = new QDir(mCache->filePath("media"));
    mCacheConfiguration = new QSettings(mCache->filePath("configuration"), QSettings::NativeFormat, this);
}

DataManager::~DataManager()
{
    // Delete parent-less objects
    delete mCacheMedia;
    delete mCache;
}


//
// Functionality
//

bool DataManager::containsConfig(const QString& iKey) const
{
    mLogger->trace() << Q_FUNC_INFO;

    return mCacheConfiguration->contains(iKey);
}

QVariant DataManager::config(const QString& iKey, const QVariant &iDefaultValue) const
{
    mLogger->trace() << Q_FUNC_INFO;

    return mCacheConfiguration->value(iKey, iDefaultValue);
}

void DataManager::setConfig(const QString& iKey, const QVariant &iValue)
{
    mLogger->trace() << Q_FUNC_INFO;

    mCacheConfiguration->setValue(iKey, iValue);
}

void DataManager::saveConfig()
{
    mLogger->trace() << Q_FUNC_INFO;

    // TODO: shouldn't be neccesary if the delete would work properly (segfaults now)

    mCacheConfiguration->sync();
}

DataManager::Media DataManager::getMedia(const QUrl &iUrl) throw(QException)
{
    mLogger->trace() << Q_FUNC_INFO;

    Media tData;
    tData.LocalLocation = *mCacheMedia;
    tData.RemoteLocation = iUrl;

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
    mLogger->trace() << Q_FUNC_INFO;

    if (removeDirectory(*mCacheMedia))
        throw QException("could not remove media");
}

DataManager::Media DataManager::getCachedMedia() throw(QException)
{
    mLogger->trace() << Q_FUNC_INFO;

    if (! mCacheMedia->exists())
        throw QException("media cache does not exist");

    svn::Revision tRevision = checkRepository(*mCacheMedia);

    Media tData;
    tData.LocalLocation = *mCacheMedia;
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
        const QFileInfoList &tEntries = iDirectory.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files | QDir::Hidden);
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
