#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "signal.h"

#include <signal.h>

int main(int argc, char **argv){

  sigset_t mask;
  sigfillset(&mask);
  pthread_sigmask(SIG_SETMASK,&mask,NULL); // block all signals

  pthread_t tSignal;
  if(pthread_create(&tSignal,NULL,signalReceiver,NULL) != 0){
		fprintf(stderr, "signal thread failed !\n");
		return EXIT_FAILURE;
	}
  sleep(1);
  alarm(3);

  if (pthread_join(tSignal,NULL) != 0) {
		perror("displayer pthread_join");
		return EXIT_FAILURE;
	}
  return 0;
}
