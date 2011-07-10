//
// Configuration
//

// Include guard
#ifndef CONTROLLER_H
#define CONTROLLER_H

// Library includes
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <Log4Qt/Logger>

// Local includes
#include "qexception.h"
#include "userinterface.h"
#include "networkinterface.h"
#include "datamanager.h"

/*
  This class controls the entire application. It uses and coordinates
  the actual subsystems in order to properly respond and react to
  external events.

  A note about the exceptions: they are only thrown within subsystems,
  and should not be used anywhere else in the application. Only the
  controller uses try/catch statements to catch errors within the
  subsystems, but doesn't rethrow them, and rather reacts properly to
  error conditions.
  */

namespace MIRA
{
    class Controller : public QObject
    {
        Q_OBJECT
    public:
        // Construction and destruction
        explicit Controller(QObject* iParent = 0) throw(QException);
        ~Controller();

        // Basic I/O
    public:
        QUuid uuid() const;
        QDateTime startup() const;

        // Application control
    public slots:
        void start();
        void stop();

        // Subsystem object getters
    public:
        NetworkInterface* networkInterface() const;
        UserInterface* userInterface() const;
        DataManager* dataManager() const;

        // Subsystem events
    private slots:
        void _shutdown();
        void _reboot();
        void _changeVolume(unsigned int iVolume);
        void _loadInterface(const QString& iInterfaceIdentifier, const QString& iInterfaceRole, const QString& iInterfaceLocation);
        void _loadMedia(const QString& iMediaIdentifier, const QString& iMediaLocation);

    private:
        // Member data
        QDateTime mTimestampStartup;

        // Subsystem objects
        QSettings* mSettings;
        Log4Qt::Logger *mLogger;
        UserInterface* mUserInterface;
        NetworkInterface* mNetworkInterface;
        DataManager* mDataManager;
    };
}

#endif // CONTROLLER_H
