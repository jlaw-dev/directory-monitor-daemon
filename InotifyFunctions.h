#ifndef _INOTIFYFUNCTIONS_H_
#define _INOTIFYFUNCTIONS_H_

#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN    (1024 * (EVENT_SIZE + 16))

using namespace std;

class InotifyFunctions { 

 private:
  int length, i;
  int fd, wd;
  char buffer[BUF_LEN];

 public:
  void startWatch();
  void pollWatch();
  void endWatch();
};

#endif
