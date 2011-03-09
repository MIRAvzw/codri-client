//
// Configuration
//

// System includes
#include <signal.h>
#include <unistd.h>

// Local includes
#include "mainapplication.h"

// Namespaces
using namespace MIRA;

static int initSignalHandlers()
{
    // Set-up and register the SIGINT handler
    struct sigaction sigint;
    sigint.sa_handler = MainApplication::handleInterruptUnix;
    sigemptyset(&sigint.sa_mask);
    sigint.sa_flags = 0;
    sigint.sa_flags |= SA_RESTART;
    if (sigaction(SIGINT, &sigint, 0) > 0)
        return 1;

    // Set-up and register the SIGTERM handler
    struct sigaction sigterm;
    sigterm.sa_handler = MainApplication::handleTerminateUnix;
    sigemptyset(&sigterm.sa_mask);
    sigterm.sa_flags |= SA_RESTART;
    if (sigaction(SIGTERM, &sigterm, 0) > 0)
        return 2;

    return 0;
}

int main(int argc, char *argv[])
{
    // Handle Unix signals
    initSignalHandlers();

    // Initialize the application
    MainApplication tApplication(argc, argv);

    tApplication.start();

    // Run the application
    /*
    try
    {
    */
        return tApplication.exec();
    /*
    }
    catch (const Exception& iException)
    {
         QTextStream qerr(stderr);

         qerr << "---------------------------------------\n";
         qerr << "          UNTRAPPED EXCEPTION          \n";
         qerr << "---------------------------------------\n";
         qerr << "\n";
         qerr << iException.toString();

         return 0;
    }
    */
}