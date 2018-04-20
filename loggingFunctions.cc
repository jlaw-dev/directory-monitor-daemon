// Jonathan Lawrence
// jml160230@utdallas.edu
// CS3377.501
// Logging Functions - logging functions to abstract logging process

#include "program5.h"
using namespace std;

//Persistant value to determine if a log file has ever been created
bool isLogCreated = false;

void log(string message) {
  
  FILE* file;
  string logFileName = configParams[LOG_FILE];

  if(!isLogCreated) {
    file = fopen(logFileName.c_str(), "w");
    isLogCreated = true;
  }
  else 
    file = fopen(logFileName.c_str(), "a");

  if(file == NULL) {
    if(isLogCreated)
      isLogCreated = false;
    return;
  }
  else {
    fputs(message.c_str(), file);
    fclose(file);
  }
}
