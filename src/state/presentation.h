/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// Include guard
#ifndef PRESENTATION_H
#define PRESENTATION_H

// Library includes
#include <QtCore/QObject>
#include <QtCore/QDir>

namespace Codri
{
    class Presentation : public QObject
    {
        Q_OBJECT
    public:
        // Construction and destruction
        Presentation(QObject *iParent);

        // Basic I/O
        unsigned long getRevision() const;
        QString getLocation() const;
        void setLocation(const QString& iLocation);
        void setRevision(unsigned long iRevision);

    signals:
        // Signals
        void onLocationChanged(const QString& iLocation);
        void onRevisionChanged(unsigned long iRevision);

    private:
        // Member data
        unsigned long mRevision;
        QString mLocation;

    };
}

#endif // PRESENTATION_H
