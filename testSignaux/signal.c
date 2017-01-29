#include "signal.h"

void *signalReceiver(void *datas){
  int signal;
  int quit = 0;

  sigset_t mask, maskold;
  if(sigfillset(&mask) == -1) fprintf(stderr, "sigfillset problem"); // all signals blocked
  if(pthread_sigmask(SIG_SETMASK,&mask,&maskold) != 0){
    fprintf(stderr,"pthread_sigmask problem");
  }

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
      case SIGALRM:
          printf("%s\n", "SIGALRM RECEIVED");
        break;
    }
  } while((quit == 0));


  printf("%s\n", "hello");
  return NULL;
}
