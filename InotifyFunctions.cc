// Jonathan Lawrence
// jml160230@utdallas.edu
// CS3377.501
// inotifyFunctions - uses inotify kernel feature to monitor 

#include "program5.h"
#include "InotifyFunctions.h"

#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN    (1024 * (EVENT_SIZE + 16))

using namespace std;

int length = 0, i = 0;
int fd = 0, wd = 0;
char buffer[BUF_LEN];

void saveFileInVersions(string filename){
  string command = "date +'"+ filename + ".%y.%m.%d-%H:%M:%S'";
  FILE *input;
  input = popen(command.c_str(), "r");
  if(input == NULL) {
    log("ERROR: Backup of '" + filename + "'.\n");
    pclose(input);
    return;
  }
  else {
    string datedFilename;
    char buffer[1024];
    while(fgets(buffer, 1024, input)) {
      datedFilename += string(buffer);
    }
    pclose(input);
    
    string filepath = configParams[WATCH_DIR] + "/" + filename;
    string filepath2 = configParams[WATCH_DIR] + "/.versions/" + datedFilename;
    string mvCmd = "cp " + filepath + " " + filepath2;
    system(mvCmd.c_str());
    log("File has been copied to .version sub-folder\n");
  }

}

void InotifyFunctions::startWatch() {

  //Initializing file descriptor
  fd = inotify_init();

  if(fd < 0) {
    perror("inotify_init");
    log("ERROR: The file descriptor could not be initialized!\n");
    log("Ending process...\n");
    exit(-1);
  }
  
  //Initializing watch
  wd = inotify_add_watch(fd, 
			 configParams[WATCH_DIR].c_str(),
			 IN_MODIFY | IN_CREATE | IN_DELETE |
			 IN_MOVE);
  if(wd < 0){
    perror("inotify_add_watch");
    log("ERROR: The watch descriptor could not be initialized!\n");
    log("Ending process...\n");
    exit(-1);
  }

  log("inotify initialized.\n");
}
  
void InotifyFunctions::pollWatch() {
  i = 0;
  length = read(fd, buffer, BUF_LEN);
    
  if(length < 0) {
    perror("read");
    log("ERROR: The read failed!\n");
    log("Ending process...\n");
    exit(-1);
  }

  while(i < length) {
    struct inotify_event* event = (struct inotify_event *) &buffer[i];
    if(event->len) {
      if(event->mask & IN_MODIFY) {
	string eventName = event->name;

	if(event->mask & IN_ISDIR)
	  log("The directory '" + eventName + "' was changed.\n");
	else {
	  log("The file '" + eventName + "' was changed.\n");
	  saveFileInVersions(eventName);
	}
      }
      else if(event->mask & IN_CREATE) {
	string eventName = event->name;

	if(event->mask & IN_ISDIR)
	  log("The directory '" + eventName + "' was created.\n");
	else {
	  log("The file '" + eventName + "' was created.\n");
	  saveFileInVersions(eventName);
	}
      }  
      else if(event->mask & IN_DELETE) {
	string eventName = event->name;

	if(event->mask & IN_ISDIR)
	  log("The directory '" + eventName + "' was deleted.\n");
	else {
	  log("The file '" + eventName + "' was deleted.\n");
	  saveFileInVersions(eventName);
	}
      }
    }
    i += EVENT_SIZE + event->len;
  }
}

void InotifyFunctions::endWatch() {
  inotify_rm_watch(fd, wd);
  close(fd);
  log("The watch on the directory was removed.\n");
}

