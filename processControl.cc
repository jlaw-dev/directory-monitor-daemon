// Jonathan Lawrence
// jml160230@utdallas.edu
// CS3377.501
// processControl - deals with daemon startup and termination

#include "program5.h"
using namespace std;

inline bool doesFileExist(string filename) {
  struct stat buffer;
  return (stat(filename.c_str(), &buffer) == 0);
}

/*
  FUNCTION: createPIDFile
  
  The function will create a PID file that stores the
  process ID of the process running, whether it is a
  daemon or a console-bounded process.
*/

void createPIDFile() {
  if(doesFileExist("cs3377dirmond.pid")){
    log("ERROR: a PID file still exists in the current directory\n");
    log("Delete the PID file before attempting to start a process\n");
    exit(1);
  }
  else {
    log("Creating the PID file and storing the PID value\n");
    system("touch cs3377dirmond.pid");

    stringstream ss;

    ss << getpid();
    string pid(ss.str());

    ofstream pidFile;
    pidFile.open("cs3377dirmond.pid");
    pidFile << pid;
    pidFile.close();
  }
}

/*
  FUNCTION: createVersionsDir
  
  The function will create a .versions folder
  in the watch directory
*/

void createVersionsDir(){
  int status;
  string path = configParams[WATCH_DIR] + "/.versions";
  status = mkdir (path.c_str(), S_IRWXU | S_IRWXG);

  if(status == (ENOTDIR | EACCES | EROFS | ENOENT)){
    log("ERROR: could not create .versions sub-folder\n");
    log("Ending process now\n");
  }
  log("The .versions sub-directory has been created in the watch directory\n");
}


/*
  FUNCTION: startDaemon

  The function will use the fork() function to
  detach a child process from the console if
  the DAEMON flag is passed into the command
  line.
*/

int startDaemon() {
  //fork() only when running in daemon mode            
  if(cmdArgs[DAEMON] == "true") {

    pid_t pid;

    //Attempts the fork() operation
    pid = fork();

    //Exits on failed fork
    if(pid < 0) {
      cerr << "Fork operation has failed\n";
      return -1;
    }
    //Parent process closes
    else if(pid > 0) {
      cerr << "Parent process ends, the daemon process will start running in the background.\n";
      exit(0);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    log("Closed standard file descriptors\n");
 
    //Daemon would have been created at this point
  }
  return 0;
}


/*            
  FUNCTION: killDaemon

  The function will kill the daemon process using  
  the PID.           
*/

void killDaemon() {
  stringstream ss;

  ss << getpid();
  string pid(ss.str());

  string kill9 = "kill -9 " + pid;

  system(kill9.c_str());
  return;
}

/*            
  FUNCTION: reparseConfigFile

  This function will execute when changes
  are made to the config file.
*/

void reparseConfigFile() {
  //Save the password and watch directory
  string password = configParams[PASSWORD];
  string watchDir = configParams[WATCH_DIR];

  //Parses the config file again
  parseConfigFile();

  //Will not allow changes to Password or the Watch Directory           
  configParams[PASSWORD] = password;
  configParams[WATCH_DIR] = watchDir;

  return;
}


void processControl(InotifyFunctions& inotif) {
  startDaemon();
  createPIDFile();
  createVersionsDir();
  inotif.startWatch();
  while(1) {
    log("Looping...\n");
    inotif.pollWatch();
    sleep(5);
  }
}
