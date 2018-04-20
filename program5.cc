// Jonathan Lawrence
// CS3377.501
// jml160230@utdallas.edu
// Driver program for program5

#include "program5.h"

int main (int argc, char** argv) {
  InotifyFunctions inotif;

  parseCmdLine(argc, argv);
  parseConfigFile();
  signalHandling(inotif);
  processControl(inotif);
  return 0;
}
