/**
 * Copyright (C) 2011-2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef STATE_CONFIGURATION_H_
#define STATE_CONFIGURATION_H_

// System includes
#include <stdint.h>

// Library includes
#include <QtCore/QObject>
#include <Log4Qt/Logger>

namespace Codri {
    class Configuration : public QObject {
    Q_OBJECT
    public:
        // Construction and destruction
        explicit Configuration(QObject *iParent);

        // Basic I/O
        uint32_t getRevision() const;
        void setRevision(uint32_t iRevision);
        uint8_t getVolume() const;
        void setVolume(uint8_t iVolume);

    signals:
        // Signals
        void onRevisionChanged(uint32_t iRevision);
        void onVolumeChanged(uint8_t iVolume);

    private:
        // Member data
        uint32_t mRevision;
        uint8_t mVolume;

        // Subsystem objects
        Log4Qt::Logger *mLogger;
    };
}

#endif  // STATE_CONFIGURATION_H_
