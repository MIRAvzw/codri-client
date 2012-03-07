//
// Configuration
//

// System includes
#include <csignal>

// Local includes
#include "mainapplication.h"
#include "qexception.h"

// Namespaces
using namespace MIRA;

struct ExitHandler
{
    ExitHandler()
    {
        signal(SIGINT, &ExitHandler::exit);
        signal(SIGTERM, &ExitHandler::exit);
    }

    static void exit(int) {
        // Calling exit in the QApplication will cause the aboutToQuit
        // signal to be emitted, allowing us to clean up properly from
        // within a Qt event thread (since this isn't, hence we cannot
        // call Qt functions from here).
        MainApplication::exit(0);
    }
};

int main(int iArgumentCount, char *iArgumentValues[])
{
    // Handle Unix signals
    ExitHandler tExitHandler;

    // Initialize the application
    MainApplication *tApplication;
    try
    {
        tApplication = new MainApplication(iArgumentCount, iArgumentValues);
    }
    catch (const QException &iException)
    {
        QTextStream qerr(stderr);

        qerr << "--------------------------------------\n";
        qerr << "        INITIALIZATION FAILURE        \n";
        qerr << "--------------------------------------\n";
        qerr << "\n";
        qerr << "Exception details: " << iException.what() << "\n";

        return 0;
    }

    // Run the application
    return tApplication->exec();
}
