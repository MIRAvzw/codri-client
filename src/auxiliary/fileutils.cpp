/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Header include
#include "fileutils.h"

// Library includes
#include <QtCore/QQueue>
#include <QtCore/QPair>


//
// Directory operations
//

bool Codri::FileUtils::removeDirectory(const QDir &iDirectory) {
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

void Codri::FileUtils::copyDirectory(const QDir &tSource, const QDir &tDestination) {
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
