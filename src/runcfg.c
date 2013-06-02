
#include "runcfg.h"

FILE *ant_rcfg_log = NULL;
int ant_rcfg_mode = RC_NONE;
int ant_rcfg_port = 0;
char ant_rcfg_logfile[256] = {0};
char ant_rcfg_address[256] = {0};

/* Holds the name of this program */
const char* ant_rcfg_program_name;

/**
 * Prints the usage statement then quits
 * @param stream Where to print the usage statement to
 * @param exit_code What code to terminate with
 */
void ant_print_usage(FILE* stream, int exit_code);

/**
 * Processes command line arguments
 * @param argc Command line parameter count
 * @param argv Command line parameter data
 */
void ant_rcfg_from_commandline(int argc, char* argv[]) {
   int next_option;

   ant_rcfg_program_name = argv[0];

   /* Short listing of arguments */
   const char* const short_options = "csa:p:l:h";

   /* Command line arguments */
   const struct option long_options[] = {
      { "client" , 0, NULL, 'c' },
      { "server" , 0, NULL, 's' },
      { "address", 1, NULL, 'a' },
      { "port"   , 1, NULL, 'p' },
      { "help"   , 0, NULL, 'h' },
      { "logfile", 1, NULL, 'l' },
      { NULL  , 0, NULL, 0   }      /* required to end the array */
   };

   do {
      /* process the next item */
      next_option = getopt_long(
            argc, argv,
            short_options, long_options,
            NULL
      );

      /* interpret the next option */
      switch (next_option) {
         case 'h':
            ant_print_usage(stdout, 0);

         case '?':
            ant_print_usage(stdout, 1);

         case -1:
            break;

         case 'c':
            ant_rcfg_mode |= RC_CLIENT;
            break;

         case 's':
            ant_rcfg_mode |= RC_SERVER;
            break;

         case 'p':
            ant_rcfg_port = atoi(optarg);
            break;

         case 'l':
            strcpy(ant_rcfg_logfile, optarg);
            break;

         case 'a':
            strcpy(ant_rcfg_address, optarg);
            break;

         default:
            abort();
      }
   } while (next_option != -1);

   /* for the convenience of running at the command line, sending
    * in no run mode should just run both the client and server */
   if (ant_rcfg_mode == RC_NONE) {
      ant_rcfg_mode = RC_STANDALONE;
   }
}

/**
 * Prints the usage statement then quits
 * @param stream Where to print the usage statement to
 * @param exit_code What code to terminate with
 */
void ant_print_usage(FILE* stream, int exit_code) {

   /* show the usage message */
   fprintf(stream, "Usage: %s options [ inputfile ... ]\n", ant_rcfg_program_name);
   fprintf(stream,
"  -h  --help         Display this usage information\n \
 -s  --server       Run in server mode\n \
 -c  --client       Run in client mode\n \
 -p  --port         Specify the port number to use\n \
 -a  --address      Specify the address to use\n \
 -l  --logfile      Provide a logfile to write to\n"
   );

   /* terminate */
   exit(exit_code);
}

/** Validates the state of the apps configuration */
int ant_rcfg_validate(void) {
   return 0;
}

/** Sets up any items as a product of configuration */
int ant_rcfg_setup(void) {

   /* open the logfile if specified, otherwise /dev/null */
   if (strlen(ant_rcfg_logfile) > 0) {
      if ((ant_rcfg_log = fopen(ant_rcfg_logfile, "a")) == NULL) {
         return -1;
      }
   } else {
      ant_rcfg_log = fopen("/dev/null", "a");
   }

   return 0;
}

/** Destroys any allocated resources during the setup process */
int ant_rcfg_teardown(void) {

   /* close the logfile */
   if (ant_rcfg_log != NULL) {
      fclose(ant_rcfg_log);
      ant_rcfg_log = NULL;
   }

   return 0;
}
