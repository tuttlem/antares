
#include "game.h"

/** */
int ant_setup(void) {

   /* make sure the configuration validates */
   if (ant_rcfg_validate() != 0) {
      ant_log("invalid run configuration detected");
      return 1;
   }

   /* pre-setup before we start to initialize the game */
   if (ant_rcfg_setup() != 0) {
      ant_log("failed to complete run configuration setup");
      return 2;
   }

   return 0;
}

/** */
int ant_run(void) {

   ant_log("antares run has started");

   /* startup the server */
   if (ant_rcfg_mode == RC_SERVER) {
      ant_log("server requested in daemon mode");
      ant_server_startd();
   } else if (ant_rcfg_mode & RC_SERVER) {
      ant_log("server requested in process mode");
      ant_server_start();
   }

   /* startup the client (if required) */
   if (ant_rcfg_mode & RC_CLIENT) {
      ant_log("client requested");
      ant_client_start();

      /* check if we're running standalone */
      if (ant_rcfg_mode & RC_SERVER) {
         ant_log("in process server now exiting");

         /* let the server know that we don't need him around anymore */
         ant_server_end();
      }
   }

   ant_log("antares run has finished");

   return 0;
}

/** */
int ant_teardown(void) {

   /* teardown the configuration */
   ant_rcfg_teardown();

   return 0;
}

