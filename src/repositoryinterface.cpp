/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "repositoryinterface.h"

// Library includes
#include <svnqt/repository.h>
#include <svnqt/repositorylistener.h>
#include <svnqt/repoparameter.h>
#include <svnqt/targets.h>
#include <svnqt/client_parameter.h>
#include <svnqt/client_update_parameter.h>
#include <svnqt/info_entry.h>
#include <QtCore/QQueue>

// Local includes
#include "mainapplication.h"
#include "auxiliary/parameterizedsignaltransition.h"


//
// Construction and destruction
//

Codri::RepositoryInterface::RepositoryInterface(QObject *iParent) throw(QException)
    : QStateMachine(iParent) {
    // Load settings
    mSettings = new QSettings(this);
    mSettings->beginGroup(metaObject()->className());

    // Setup logging
    mLogger =  Log4Qt::Logger::logger(metaObject()->className());

    // Checkout directory
    mCheckout = QDir(mSettings->value("checkout", "/tmp/repository").toString());

    // Actual implementation
    mImplementation = new RepositoryInterfacePrivate(this);

    // State machine
    // TODO: log transitions
    initFSM();
    start();
}

Codri::RepositoryInterfacePrivate::RepositoryInterfacePrivate(QObject *iParent)
    : QObject(iParent) {
    // Configure subversion client
    svn::ContextP tSubversionContext;
    mSubversionClient = svn::Client::getobject(0, 0);
    tSubversionContext = new svn::Context();
    tSubversionContext->setListener(this);
    mSubversionClient->setContext(tSubversionContext);
}


//
// Construction helpers
//

void Codri::RepositoryInterface::initFSM() {
    mIdle = new QState(this);
    QState *tChecking = new QState(this);
    QState *tUpdating = new QState(this);
    QState *tCheckingOut = new QState(this);
    setInitialState(mIdle);


    // IDLE STATE //

    // Transitions to active states
    mIdle->addTransition(this, SIGNAL(_check()), tChecking);

    // TODO: connect dataChanging


    // CHECKING STATE //

    // Action on activation
    connect(tChecking, SIGNAL(entered()), this, SLOT(_onCheckout()));

    // Transition on need for update
    tChecking->addTransition(mImplementation, SIGNAL(needsUpdate()), tUpdating);

    // Transition on need for checkout
    tChecking->addTransition(mImplementation, SIGNAL(needsCheckout()), tCheckingOut);


    // UPDATING STATE //

    // Action on activation
    connect(tUpdating, SIGNAL(entered()), this, SLOT(_onUpdate()));

    // Transition on update success
    tUpdating->addTransition(mImplementation, SIGNAL(updateSuccess(uint32_t)), mIdle);
    connect(mImplementation, SIGNAL(updateSuccess(uint32_t)), this, SLOT(_onUpdateSuccess(uint32_t)));

    // Transition on update failure
    tUpdating->addTransition(mImplementation, SIGNAL(updateFailure(QException)), tCheckingOut);
    connect(mImplementation, SIGNAL(updateFailure(QException)), this, SLOT(_onUpdateFailure(QException)));


    // CHECKING OUT STATE //

    // Action on activation
    connect(tCheckingOut, SIGNAL(entered()), this, SLOT(_onCheckout()));

    // Transition on checkout success
    tCheckingOut->addTransition(mImplementation, SIGNAL(checkoutSuccess(uint32_t)), mIdle);
    connect(mImplementation, SIGNAL(checkoutSuccess(uint32_t)), this, SLOT(_onCheckoutSuccess(uint32_t)));

    // Transition on checkout failure (delayed restart of checkout)
    QTimer *tCheckoutRetry = new QTimer(this);
    tCheckoutRetry->setSingleShot(true);
    tCheckoutRetry->setInterval(mSettings->value("retry", 60*1000).toInt());
    connect(mImplementation, SIGNAL(checkoutFailure(QException)), tCheckoutRetry, SLOT(start()));
    tCheckingOut->addTransition(tCheckoutRetry, SIGNAL(timeout()), tCheckingOut);
    connect(mImplementation, SIGNAL(checkoutFailure(QException)), this, SLOT(_onCheckoutFailure(QException)));
    // TODO: is entered() triggered when going to the same state again?
}


//
// Public interface
//

void Codri::RepositoryInterface::check(const QString &iLocation) {
    mLocation = iLocation;

    if (configuration().contains(mIdle)) {
        emit _check();
    } else {
        mLogger->warn() << "Request to check while busy";
        QTimer::singleShot(100, this, SLOT(recheck()));
    }
}

// TODO: only necessary because QTimer::timeout() doesn't provide arguments
void Codri::RepositoryInterface::recheck() {
    if (configuration().contains(mIdle)) {
        emit _check();
    } else {
        mLogger->warn() << "Request to check while busy";
        QTimer::singleShot(100, this, SLOT(recheck()));
    }
}


//
// Proxy slots
//

void Codri::RepositoryInterface::_onCheck() {
    mImplementation->check(mCheckout, mLocation);
}

void Codri::RepositoryInterface::_onUpdate() {
    emit changing();
    mImplementation->update(mCheckout);
}

void Codri::RepositoryInterface::_onUpdateSuccess(uint32_t iRevision) {
    // TODO: do something with revision?
    emit ready(mCheckout);
}

void Codri::RepositoryInterface::_onUpdateFailure(const QException &iException) {
    mLogger->error() << "Repository update failed: " << iException.what();
    foreach (const QString& tCause, iException.causes())
        mLogger->error() << "Caused by: " << tCause;
}

void Codri::RepositoryInterface::_onCheckout() {
    emit changing();
    mImplementation->checkout(mCheckout, mLocation);
}

void Codri::RepositoryInterface::_onCheckoutSuccess(uint32_t iRevision) {
    // TODO: do something with revision?
    emit ready(mCheckout);
}

void Codri::RepositoryInterface::_onCheckoutFailure(const QException &iException) {
    mLogger->error() << "Repository checkout failed: " << iException.what();
    foreach (const QString& tCause, iException.causes())
        mLogger->error() << "Caused by: " << tCause;
}


//
// Functionality
//

void Codri::RepositoryInterfacePrivate::check(const QDir& iCheckout, const QString& iLocation) {
    if (iCheckout.exists() && getRepositoryLocation(iCheckout) == iLocation) {
        // TODO: compare revision, don't update if not needed
        emit needsUpdate();
    } else {
        emit needsCheckout();
    }
}

void Codri::RepositoryInterfacePrivate::update(const QDir& iCheckout) {
    svn::UpdateParameter tUpdateParameters;
    tUpdateParameters
            .targets(iCheckout.absolutePath())
            .revision(svn::Revision::HEAD)
            .depth(svn::DepthInfinity);

    try {
        QList<svn::Revision> tRevisions = mSubversionClient->update(tUpdateParameters);
        // TODO: verify that .back() is the latest revision
        emit updateSuccess(tRevisions.back().revnum());
    } catch (const svn::ClientException &iException) {
        emit updateFailure(QException::fromSVNException(iException));
    }
}

void Codri::RepositoryInterfacePrivate::checkout(const QDir& iCheckout, const QString& iLocation) {
    // Create, remove, ... directory
    svn::CheckoutParameter tCheckoutParameters;
    tCheckoutParameters
            .moduleName(iLocation)
            .destination(iCheckout.absolutePath())
            .revision(svn::Revision::HEAD)
            .peg(svn::Revision::HEAD)
            .depth(svn::DepthInfinity);

    try {
        // TODO: do this asynchronously
        svn::Revision tRevision = mSubversionClient->checkout(tCheckoutParameters).revnum();
        emit checkoutSuccess(tRevision);
    } catch (const svn::ClientException &iException) {
        emit checkoutFailure(QException::fromSVNException(iException));
    }
}


//
// Repository helpers
//

QString Codri::RepositoryInterfacePrivate::getRepositoryLocation(const QDir &iCheckout) throw(QException) {
    // TODO
    return "dummy";
}

uint32_t Codri::RepositoryInterfacePrivate::getRepositoryRevision(const QDir &iCheckout) throw(QException) {
    try {
        QList<svn::InfoEntry> tInfoEntries =  mSubversionClient->info(
                    iCheckout.absolutePath(),
                    svn::DepthEmpty,
                    svn::Revision::HEAD);
        if (tInfoEntries.size() != 1)
            throw QException("unexpected amount of info entries");
        return tInfoEntries.first().revision().revnum();
    } catch (const svn::ClientException &iException) {
        throw QException("could not check the repository", QException::fromSVNException(iException));
    } catch (const QException &iException) {
        throw QException("could not check the repository", iException);
    }
}



//
// Filesystem helpers
//

bool Codri::RepositoryInterfacePrivate::removeDirectory(const QDir &iDirectory) {
    bool tError = false;
    if (iDirectory.exists()) {
        const QFileInfoList &tEntries = iDirectory.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files | QDir::Hidden);
        foreach (const QFileInfo &tEntry, tEntries) {
            QString tEntryPath = tEntry.absoluteFilePath();
            if (tEntry.isDir()) {
                tError = removeDirectory(QDir(tEntryPath));
            } else {
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

void Codri::RepositoryInterfacePrivate::copyDirectory(const QDir &tSource, const QDir &tDestination) {
    // Create the destination path
    if (!tDestination.exists())
        tDestination.mkpath(tDestination.absolutePath());

    // Enqueue the initial pair
    QQueue< QPair<QDir, QDir> > tQueue;
    tQueue.enqueue(qMakePair(tSource, tDestination));

    // Process iteratively
    while (!tQueue.isEmpty()) {
        QPair<QDir, QDir> tDirectories = tQueue.dequeue();
        if (!tDirectories.first.exists())
            continue;

        // Copy all files
        foreach (QString tFile, tDirectories.first.entryList(QDir::Files))
            QFile::copy(tDirectories.first.absoluteFilePath(tFile), tDirectories.second.absoluteFilePath(tFile));

        // Enqueue all directories
        foreach (QString tDirectory, tDirectories.first.entryList(QDir::AllDirs | QDir::NoDotAndDotDot)) {
            tDirectories.second.mkdir(tDirectory);
            tQueue.enqueue(qMakePair(QDir(tDirectories.first.absoluteFilePath(tDirectory)), QDir(tDirectories.second.absoluteFilePath(tDirectory))));
        }
    }
}
