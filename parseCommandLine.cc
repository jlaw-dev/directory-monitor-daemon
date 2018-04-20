// Jonathan Lawrence
// jml160230@utdallas.edu
// CS3377.501
// Code to parse cmdline in program5

#include "program5.h"

map<int,string> cmdArgs;

void parseCmdLine(int argc, char** argv){
  try {
    TCLAP::CmdLine cmd("cs3377dirmond Directory Monitor Daemon", ' ', "1.0");
    TCLAP::SwitchArg daemonSwitch("d", "daemon", "Run in daemon mode", cmd, false);
    TCLAP::UnlabeledValueArg<string> configArg("config", "The name of the configuration file", true,
					       "cs3377dirmond.conf", "config filename", false);
    cmd.add(configArg);
    
    // Parse cmd line
    cmd.parse(argc, argv);
    
    //daemon switch
    if (daemonSwitch.getValue())
      cmdArgs[DAEMON] = "true";
    else
      cmdArgs[DAEMON] = "false";

    //config file
    cmdArgs[CONFIG_FILE] = configArg.getValue();

    //testing 
    //    cout << cmdArgs[DAEMON] << endl;
    //  cout << cmdArgs[CONFIG_FILE] << endl;
  }
  catch (TCLAP::ArgException &e){
    cerr << "Error: " << e.error() << " for arg " << e.argId() << endl;
  }
}
