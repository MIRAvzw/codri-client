/**
 * Copyright (C) 2012 Tim Besard <tim.besard@gmail.com>
 *
 * All rights reserved.
 */

//
// Configuration
//

// System includes
#include <csignal>

// Local includes
#include "mainapplication.h"
#include "qexception.h"

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
        Codri::MainApplication::exit(0);
    }
};

int main(int iArgumentCount, char *iArgumentValues[])
{
    // Handle Unix signals
    ExitHandler tExitHandler;

    // Run the applications
    Codri::MainApplication *tApplication = new Codri::MainApplication(iArgumentCount, iArgumentValues);
    return tApplication->exec();
}
