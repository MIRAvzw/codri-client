/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QtCore/QObject>

namespace Codri
{
    class Configuration : public QObject
    {
        Q_OBJECT
    public:
        // Construction and destruction
        Configuration(QObject *iParent);

        // Basic I/O
        unsigned long getRevision() const;
        void setRevision(unsigned long iRevision);
        unsigned short getVolume() const;
        void setVolume(unsigned char iVolume);

    signals:
        // Signals
        void onVolumeChanged(unsigned char iVolume);

    private:
        // Member data
        unsigned long mRevision;
        unsigned char mVolume;
    };
}

#endif // CONFIGURATION_H
