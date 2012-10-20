
#ifndef __ant_runcfg_h_

#define __ant_runcfg_h_

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>

#include "log.h"

#define RC_NONE            0x00000000
#define RC_CLIENT          0x00000001
#define RC_SERVER          0x00000002
#define RC_STANDALONE      (RC_CLIENT | RC_SERVER)

/** Requested run configuration */
extern int ant_rcfg_mode;

/** The port to listen on / connect to */
extern int ant_rcfg_port;

/** The file to log messages to */
extern char ant_rcfg_logfile[256];

/** The file handle for the log file */
extern FILE *ant_rcfg_log;

/** The address to connect to */
extern char ant_rcfg_address[256];

/** Interprets the passed in command line into this unit */
void ant_rcfg_from_commandline(int argc, char **argv);

/** Validates the state of the apps configuration */
int ant_rcfg_validate(void);

/** Sets up any items as a product of configuration */
int ant_rcfg_setup(void);

/** Destroys any allocated resources during the setup process */
int ant_rcfg_teardown(void);

#endif /* __ant_runcfg_h_ */
