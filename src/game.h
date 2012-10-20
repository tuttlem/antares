
#ifndef __ant_game_h_

#define __ant_game_h_

#include "runcfg.h"
#include "server.h"
#include "client.h"

/** Sets up the game */
int ant_setup(void);

/** Runs the game */
int ant_run(void);

/** Tears the game down */
int ant_teardown(void);

#endif /* __ant_game_h_ */
