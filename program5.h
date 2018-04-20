#ifndef _PROGRAM5_H_
#define _PROGRAM5_H_

#include <map>
#include <string>
#include <fstream>
#include <csignal>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/inotify.h>

#include <tclap/CmdLine.h>
#include <rude/config.h>

#include "InotifyFunctions.h"

using namespace std;

//Functions
void parseCmdLine(int, char**);
void parseConfigFile(void);
void signalHandling(InotifyFunctions&);
void processControl(InotifyFunctions&);

//Helper functions
void log(string);
inline bool doesFileExist(string);

//Variables/Objects
extern map<int, string> cmdArgs;
enum cmdKeys {DAEMON, CONFIG_FILE};

extern map<int, string> configParams;
enum configKeys {VERBOSE, LOG_FILE, PASSWORD, NUM_VERSIONS, WATCH_DIR};

extern bool isLogCreated;
#endif //_PROGRAM5_H_
