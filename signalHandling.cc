// Jonathan Lawrence
// jml160230@utdallas.edu
// CS3377.501
// signalHandling - deals with intercepting signals from the user

#include "program5.h"
#include "InotifyFunctions.h"
using namespace std;

extern map<int, string> cmdArgs;
extern map<int, string> configParams;

void killDaemon(void);
void reparseConfigFile(void);

InotifyFunctions inotifFunc;

/*
  FUNCTION: signalHandler

  This function is called when a signal is detected
  Based on what signal is detected, a different 
  operation occurs.
*/

void signalHandler(int sigNum) {
  switch(sigNum) {
  case SIGINT:
    system("rm -f cs3377dirmond.pid");
    log("Removed PID file.\n");
    log("Ending process.\n");
    inotifFunc.endWatch();
    killDaemon();
    break;
  case SIGTERM:
    system("rm -f cs3377dirmond.pid");
    log("Removed PID file.\n");
    log("Ending process.\n");
    inotifFunc.endWatch();
    killDaemon();
    break;
  case SIGHUP:
    log("Received SIGHUP signal, detecting changes made in the config file.\n");
    reparseConfigFile();
    break;
  default:
    break;
  }
}

void signalHandling(InotifyFunctions &inotify) {
  inotifFunc = inotify;
  signal (SIGINT, signalHandler);
  signal (SIGTERM, signalHandler);
  signal (SIGHUP, signalHandler);
}
