// Jonathan Lawrence
// CS3377.501
// jml160230@utdallas.edu
// Config file parser using RudeConfig

#include "program5.h"
using namespace rude;

map<int, string> configParams;

void parseConfigFile(void) {

  // Create config obj
  Config config;

  // Load config file from map
  config.load(cmdArgs[CONFIG_FILE].c_str());
  
  // Set section to Parameters
  config.setSection("Parameters");
  
  // Check if Verbose ID exists 
  if(config.exists("Verbose"))
    configParams[VERBOSE] = config.getStringValue("Verbose");
  else {
    cerr << config.getError() << endl;
    exit(1);
  } 
    
  // Check if LogFile ID exists
  if(config.exists("LogFile"))
    configParams[LOG_FILE] = config.getStringValue("LogFile");
  else {
    cerr << config.getError() << endl;
    exit(1);
  }

  // Check if Password ID exists
  if(config.exists("Password"))
    configParams[PASSWORD] = config.getStringValue("Password");
  else {
    cerr << config.getError();
    exit(1);
  }

  // Check if NumVersions ID exists
  if(config.exists("NumVersions"))
    configParams[NUM_VERSIONS] = config.getStringValue("NumVersions");
  else {
    cerr << config.getError();
    exit(1);
  }

  // Check if WatchDir ID exists
  if(config.exists("WatchDir"))
    configParams[WATCH_DIR] = config.getStringValue("WatchDir");
  else {
    cerr << config.getError();
    exit(1);
  }

  // Testing
  // cout << configParams[VERBOSE] << endl;
  // cout << configParams[LOG_FILE] << endl;
  // cout << configParams[PASSWORD] << endl;
  // cout << configParams[NUM_VERSIONS] << endl;
  // cout << configParams[WATCH_DIR] << endl;

}
