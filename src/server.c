
#include "server.h"

int ant_server_running = 0;
pid_t ant_server_pid = 0;

/** Signal handler for the daemon */
void daemon_signalhandler(int sig);

/** Runs the actual server process itself */
void ant_server_run(void) {

   ant_log("server process running");

   while (ant_server_running) {

   }

   ant_log("server process leaving");

   /* explicitly exit the proces here otherwise orphaned antares
    * carcasses litter the process table */
   exit(0);
}

/** Ends the running server */
void ant_server_end(void) {

   ant_log("killing server pid %d", ant_server_pid);
   /* sigterm the server pid */
   kill(ant_server_pid, SIGTERM);

}

/** */
int ant_server_start(void) {

   pid_t pid;

   /* fork off the parent process */
   pid = fork();

   /* start the server in the child */
   if (pid == 0) {

      ant_log("preparing server to run");

      /* attach the signal handlers now */
      signal(SIGCHLD, SIG_IGN);
      signal(SIGTSTP, SIG_IGN);
      signal(SIGTTOU, SIG_IGN);
      signal(SIGTTIN, SIG_IGN);
      signal(SIGHUP, daemon_signalhandler);
      signal(SIGTERM, daemon_signalhandler);

      /* mark the server as running */
      ant_server_running = 1;

      /* run the server process */
      ant_server_run();
   } else {

      ant_log("server process is %d", pid);

      ant_server_pid = pid;
   }

   return 0;
}

/** */
int ant_server_startd(void) {
   pid_t pid, sid;

   /* 1. fork off the parent process */
   pid = fork();

   /* if process failed to created, bail out with failure */
   if (pid < 0) {
      exit(EXIT_FAILURE);
   }

   /* if the pid is good, terminate the parent ok */
   if (pid > 0) {
      exit(EXIT_SUCCESS);
   }

   /* 2. change the file mode mask (umask) */
   umask(0);

   /* 3. open logs for writing (syslog) */
   /* openlog(daemon_name, LOG_PID, LOG_DAEMON); */

   /* 4. set the session id for the daemon */
   sid = setsid();

   /* bug out with failure if we couldn't set the new process group */
   if (sid < 0) {
      exit(EXIT_FAILURE);
   }

   /* 5. change the current working directory to a "safe" place */
   if ((chdir("/")) < 0) {
      exit(EXIT_FAILURE);
   }

   /* 6. close all standard file handles */
   close(STDIN_FILENO);
   close(STDOUT_FILENO);
   close(STDERR_FILENO);

   /* attach the signal handlers now */
   signal(SIGCHLD, SIG_IGN);
   signal(SIGTSTP, SIG_IGN);
   signal(SIGTTOU, SIG_IGN);
   signal(SIGTTIN, SIG_IGN);
   signal(SIGHUP, daemon_signalhandler);
   signal(SIGTERM, daemon_signalhandler);

   /* mark the server as now running */
   ant_server_running = 1;

   /* run the actual server process */
   ant_server_run();

   return 0;
}

/** */
void daemon_signalhandler(int sig) {

   ant_log("server received signal %d", sig);

   switch (sig) {

      case SIGHUP:
         ant_log("handling hangup signal");
         /* this should just refresh configs and restart */
         ant_server_running = 0;
         break;

      case SIGTERM:
         ant_log("handling term signal");
         /* mark the server as no longer running */
         ant_server_running = 0;
         break;
   }

}

