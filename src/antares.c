
#include "runcfg.h"
#include "game.h"

/** Main program entry */
int main(int argc, char* argv[]) {

   /* interpret the command line */
   ant_rcfg_from_commandline(argc, argv);

   /* setup the game */
   if (ant_setup() != 0)
      return 1;

   /* run the game */
   ant_run();

   /* tear the game down */
   ant_teardown();

   return 0;
}


