#include "signal.h"

void *signalReceiver(void *datas){
  int signal;
  int quit = 0;
  sigset_t mask, maskold;
  if(sigfillset(&mask) == -1) exit(1); // all signals blocked
  if(pthread_sigmask(SIG_SETMASK,&mask,&maskold) != 0) exit(1);

  do {
    sigwait(&mask,&signal); // waiting for a signal
    switch (signal) {
      case SIGINT:
          printf("%s\n", "SIGINT RECEIVED");
        break;
      case SIGTSTP:
          printf("%s\n", "SIGTSTP RECEIVED");
        break;
      case SIGQUIT:
          printf("%s\n", "SIGQUIT RECEIVED");
          quit = 1;
        break;
    }
  } while((quit == 0));


  printf("%s\n", "hello");
  return NULL;
}
