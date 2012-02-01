//
// Configuration
//

// Include guard
#ifndef PRESENTATION_H
#define PRESENTATION_H

// Library includes
#include <QtCore/QObject>
#include <QtCore/QDir>

namespace MIRA
{
    class Presentation : public QObject
    {
        Q_OBJECT
    public:
        // Construction and destruction
        Presentation(QObject *iParent = 0);

        // State enum
        enum State {
            UNINITIALIZED,
            ACTIVE
        };

        // Basic I/O
        State getState() const;
        unsigned long getRevision() const;
        QDir getCheckout() const;
        QString getLocation() const;
        void setLocation(const QString& iLocation, const QDir& iCheckout, unsigned long iRevision);
        QString getPendingLocation() const;
        void setPendingLocation(const QString &iLocation);

    signals:
        // Signals
        void onLocationChanged(const QString& iLocation, const QDir& iCheckout, unsigned long iRevision);
        void onPendingLocationChanged(const QString& iPendingLocation);

    private:
        // Member data
        State mState;
        unsigned long mRevision;
        QDir mCheckout;
        QString mLocation, mPendingLocation;

    };
}

#endif // PRESENTATION_H
