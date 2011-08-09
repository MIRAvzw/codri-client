//
// Configuration
//

// System includes
#include <signal.h>
#include <unistd.h>

// Local includes
#include "mainapplication.h"
#include "qexception.h"

// Namespaces
using namespace MIRA;

static int initSignalHandlers()
{
    // Set-up and register the SIGINT handler
    struct sigaction tSignalInterrupt;
    tSignalInterrupt.sa_handler = MainApplication::handleInterruptUnix;
    sigemptyset(&tSignalInterrupt.sa_mask);
    tSignalInterrupt.sa_flags = 0;
    tSignalInterrupt.sa_flags |= SA_RESTART;
    if (sigaction(SIGINT, &tSignalInterrupt, 0) > 0)
        return 1;

    // Set-up and register the SIGTERM handler
    struct sigaction tSignalTerminate;
    tSignalTerminate.sa_handler = MainApplication::handleTerminateUnix;
    sigemptyset(&tSignalTerminate.sa_mask);
    tSignalTerminate.sa_flags |= SA_RESTART;
    if (sigaction(SIGTERM, &tSignalTerminate, 0) > 0)
        return 2;

    return 0;
}

int main(int iArgumentCount, char *iArgumentValues[])
{
    // Handle Unix signals
    initSignalHandlers();

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
