#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
//#include "signal.h"

#include <signal.h>
static void signalHandler(int signum){
  printf("\n%s\n", "hello");
  if(signum == SIGINT){
    printf("%s\n", "SIGINT RECEIVED");
  }
  if(signum == SIGQUIT){
    printf("%s\n", "SIGQUIT RECEIVED");
  }
  if(signum == SIGTSTP){
    printf("%s\n", "SIGTSTP RECEIVED");
  }
  //  _exit(EXIT_SUCCESS);
}


int main(int argc, char **argv){
/*  sigset_t mask;
  sigfillset(&mask);
  pthread_sigmask(SIG_SETMASK,&mask,NULL); // block all signals
  sigdelset(&mask, SIGINT);
  pthread_sigmask(SIG_SETMASK, &mask, NULL);
  sigdelset(&mask, SIGQUIT);
  pthread_sigmask(SIG_SETMASK, &mask, NULL);
  sigdelset(&mask, SIGTSTP);
  pthread_sigmask(SIG_SETMASK, &mask, NULL);*/

  struct sigaction act;
  act.sa_handler = signalHandler;
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);
  if(sigaction(SIGINT,&act,NULL) == -1){
    perror("sigaction");
    exit(EXIT_FAILURE);
  }
  if(sigaction(SIGQUIT,&act,NULL) == -1){
    perror("sigaction");
    exit(EXIT_FAILURE);
  }
  if(sigaction(SIGTSTP,&act,NULL) == -1){
    perror("sigaction");
    exit(EXIT_FAILURE);
  }

  while(1){pause();}
  return 0;
}
