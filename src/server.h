
#ifndef __ant_server_h_

#define __ant_server_h_

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

/** Starts the server as a forked process */
int ant_server_start(void);

/** Ends the server */
void ant_server_end(void);

/** Starts the server as a daemon */
int ant_server_startd(void);

#endif /* __ant_server_h_ */
