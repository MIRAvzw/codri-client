/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef STATE_CONFIGURATION_H_
#define STATE_CONFIGURATION_H_

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
        unsigned long getRevision() const;
        void setRevision(unsigned long iRevision);
        unsigned short getVolume() const;
        void setVolume(unsigned char iVolume);

    signals:
        // Signals
        void onRevisionChanged(unsigned long iRevision);
        void onVolumeChanged(unsigned char iVolume);

    private:
        // Member data
        unsigned long mRevision;
        unsigned char mVolume;

        // Subsystem objects
        Log4Qt::Logger *mLogger;
    };
}

#endif  // STATE_CONFIGURATION_H_
