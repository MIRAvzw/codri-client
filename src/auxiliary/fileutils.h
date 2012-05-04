/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef AUXILIARY_FILEUTILS_H_
#define AUXILIARY_FILEUTILS_H_

// Library includes
#include <QtCore/QDir>

namespace Codri {
    class FileUtils
    {
    public:
        // Directory operations
        static bool removeDirectory(const QDir &iDirectory);
        static void copyDirectory(const QDir &tSource, const QDir &tDestination);
    };
}

#endif  // AUXILIARY_FILEUTILS_H_
