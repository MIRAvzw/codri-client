//
// Configuration
//

// Includes
#include "mainapplication.h"

// Nalesoaces
using namespace MIRA;

int main(int argc, char *argv[])
{
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
