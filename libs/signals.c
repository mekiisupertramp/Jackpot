/**
* \file signals.c
* \brief signals library
* \author BUFFO Pierre, DA SILVA Gabriel, MEHMED Blazevic
* \version 1.0
* \date 25.01.2017
*/

#include "signals.h"


/**
 * thread which control the signals received
 * @param threadData - struct containing the datas
 * @return
 */
void *signalReceiver(void *threadData) {
    controller_t *tdata = (controller_t *) (threadData);
    int signal;
    int quit = 0;

    sigset_t mask, maskold;
    if (sigfillset(&mask) == -1) fprintf(stderr, "sigfillset problem"); // all signals blocked
    if (pthread_sigmask(SIG_SETMASK, &mask, &maskold) != 0) {
        fprintf(stderr, "pthread_sigmask problem");
    }

    do {
        sigwait(&mask, &signal); // waiting for a signal
        switch (signal) {
            case SIGINT:  // stop the current wheel
                if (tdata->gameState == ROLLING) {
                    tdata->wheels[0].condMutex->var++;
                    pthread_cond_broadcast(&tdata->wheels[0].condMutex->cond);
                }
                break;
            case SIGTSTP: // insert coin
                tdata->gameState = ROLLING;
                pthread_mutex_lock(&(tdata->wheels[0].condMutex->m));
                tdata->wheels[0].condMutex->var=0;
                pthread_cond_broadcast(&tdata->wheels[0].condMutex->cond);
                pthread_mutex_unlock(&(tdata->wheels[0].condMutex->m));
                tdata->coins++;
                break;
            case SIGQUIT:
                quit = 1;
                break;
            case SIGALRM:
                sleep(5);
                tdata->gameState = WAITING;
                break;
        }
    } while (quit == 0);
    pthread_mutex_lock(&(tdata->wheels[0].condMutex->m));
    tdata->wheels[0].condMutex->var = FINISHEDPROGRAM;
    pthread_cond_broadcast(&(tdata->wheels[0].condMutex->cond));
    pthread_mutex_unlock(&(tdata->wheels[0].condMutex->m));

    return NULL;
}
