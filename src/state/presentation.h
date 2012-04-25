/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef STATE_PRESENTATION_H_
#define STATE_PRESENTATION_H_

// System includes
#include <stdint.h>

// Library includes
#include <QtCore/QObject>
#include <QtCore/QDir>
#include <log4qt/Logger>

namespace Codri {
    class Presentation : public QObject {
    Q_OBJECT
    public:
        // Construction and destruction
        explicit Presentation(QObject *iParent);

        // Basic I/O
        uint32_t getRevision() const;
        void setRevision(uint32_t iRevision);
        QString getPath() const;
        void setPath(const QString& iPath);

    signals:
        // Signals
        void onRevisionChanged(uint32_t iRevision);
        void onPathChanged(const QString& iPath);

    private:
        // Member data
        uint32_t mRevision;
        QString mPath;

        // Subsystem objects
        Log4Qt::Logger *mLogger;
    };
}

#endif  // STATE_PRESENTATION_H_
