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
#include <Log4Qt/Logger>

namespace Codri {
    class Presentation : public QObject {
    Q_OBJECT
    public:
        // Construction and destruction
        explicit Presentation(QObject *iParent);

        // Basic I/O
        uint32_t getRevision() const;
        void setRevision(uint32_t iRevision);
        QString getLocation() const;
        void setLocation(const QString& iLocation);

    signals:
        // Signals
        void onRevisionChanged(uint32_t iRevision);
        void onLocationChanged(const QString& iLocation);

    private:
        // Member data
        uint32_t mRevision;
        QString mLocation;

        // Subsystem objects
        Log4Qt::Logger *mLogger;
    };
}

#endif  // STATE_PRESENTATION_H_
