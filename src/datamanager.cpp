//
// Configuration
//

// Local includes
#include "datamanager.h"
#include "mainapplication.h"

// Library includes
#include <svnqt/repository.h>
#include <svnqt/repositorylistener.h>
#include <svnqt/repoparameter.h>
#include <svnqt/targets.h>
#include <svnqt/client_parameter.h>
#include <svnqt/client_update_parameter.h>
#include <svnqt/info_entry.h>
#include <QtCore/QQueue>

// Namespaces
using namespace MIRA;


//
// Construction and destruction
//

DataManager::DataManager(QObject *iParent) throw(QException) : QObject(iParent)
{
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup("DataManager");

    // Setup logging
    mLogger =  Log4Qt::Logger::logger(metaObject()->className());

    // Configure subversion
    svn::ContextP tSubversionContext;
    mSubversionClient = svn::Client::getobject(0, 0);
    tSubversionContext = new svn::Context();
    tSubversionContext->setListener(this);
    mSubversionClient->setContext(tSubversionContext);
}


//
// High-level functionality
//

QPair<QDir, unsigned long> DataManager::downloadPresentation(const QString &iLocation) throw(QException) {
    // Manage the checkout directory
    QDir tCheckout(mSettings->value("presentations/checkout", "/tmp/data/presentation").toString());

    // Check if we need to update or get a new copy
    unsigned long tRevision;
    if (tCheckout.exists() && getRepositoryLocation(tCheckout) == iLocation)
    {
        // Update the copy
        tRevision = updateRepository(tCheckout);
    }
    else
    {
        // Do a full checkout
        removeDirectory(tCheckout);
        tRevision = checkoutRepository(tCheckout, iLocation);
    }

    return QPair<QDir, unsigned long>(tCheckout, tRevision);
}


//
// Low-level functionality
//

QString DataManager::getRepositoryLocation(const QDir &iCheckout) throw(QException)
{
    // TODO
    return "dummy";
}

unsigned long DataManager::getRepositoryRevision(const QDir &iCheckout) throw(QException)
{
    try
    {
        QList<svn::InfoEntry> tInfoEntries =  mSubversionClient->info(
                    iCheckout.absolutePath(),
                    svn::DepthEmpty,
                    svn::Revision::HEAD);
        if (tInfoEntries.size() != 1)
            throw QException("unexpected amount of info entries");
        return tInfoEntries.first().revision().revnum();
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

unsigned long DataManager::checkoutRepository(const QDir &iCheckout, const QUrl &iLocation) throw(QException)
{
    svn::CheckoutParameter tCheckoutParameters;
    tCheckoutParameters
            .moduleName(iLocation.toString())
            .destination(iCheckout.absolutePath())
            .revision(svn::Revision::HEAD)
            .peg(svn::Revision::HEAD)
            .depth(svn::DepthInfinity);

    try
    {
        // TODO: do this asynchronously
        return mSubversionClient->checkout(tCheckoutParameters).revnum();
    }
    catch (const svn::ClientException &iException)
    {
        throw QException("could not checkout the repository", QException::fromSVNException(iException));
    }

}

unsigned long DataManager::updateRepository(const QDir &iCheckout) throw(QException)
{
    svn::UpdateParameter tUpdateParameters;
    tUpdateParameters
            .targets(iCheckout.absolutePath())
            .revision(svn::Revision::HEAD)
            .depth(svn::DepthInfinity);

    try
    {
        QList<svn::Revision> tRevisions = mSubversionClient->update(tUpdateParameters);
        // TODO: verify that .back() is the latest revision
        return tRevisions.back().revnum();
    }
    catch (const svn::ClientException &iException)
    {
        throw QException("could not update the repository", QException::fromSVNException(iException));
    }
}


//
// Auxiliary
//

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

void DataManager::copyDirectory(const QDir &tSource, const QDir &tDestination)
{
    // Create the destination path
    if (!tDestination.exists())
        tDestination.mkpath(tDestination.absolutePath());

    // Enqueue the initial pair
    QQueue< QPair<QDir, QDir> > tQueue;
    tQueue.enqueue(qMakePair(tSource, tDestination));

    // Process iteratively
    while (!tQueue.isEmpty())
    {
        QPair<QDir, QDir> tDirectories = tQueue.dequeue();
        if(!tDirectories.first.exists())
            continue;

        // Copy all files
        foreach (QString tFile, tDirectories.first.entryList(QDir::Files))
            QFile::copy(tDirectories.first.absoluteFilePath(tFile), tDirectories.second.absoluteFilePath(tFile));

        // Enqueue all directories
        foreach (QString tDirectory, tDirectories.first.entryList(QDir::AllDirs | QDir::NoDotAndDotDot))
        {
            tDirectories.second.mkdir(tDirectory);
            tQueue.enqueue(qMakePair(QDir(tDirectories.first.absoluteFilePath(tDirectory)), QDir(tDirectories.second.absoluteFilePath(tDirectory))));
        }
    }
}
