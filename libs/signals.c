/**
* \file signals.c
* \brief signals library
* \author BUFFO Pierre, DA SILVA Gabriel, MEHMED Blazevic
* \version 1.0
* \date 25.01.2017
*/

#include "signals.h"


/**
 * thread which control the signals received, here we use 4 signals:
 * SIGINT,SIGTSTP, SIGQUIT and SIGALRM
 * SIGINT  - used to control the wheels (stop them)
 * SIGTSTP - used to start the game (insert coin)
 * SIGQUIT - used to quit the game
 * SIGALRM - used to wait 5 seconds at the end of a party and for playing at the
 *    place of the gamer, if he doesn't play about 3 seconds
 * @param threadData - struct containing the datas of the programm
 * @return NULL
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
            case SIGINT:  // stop the current wheel and start the alarm
                if (tdata->gameState == ROLLING) {
                    tdata->wheels[0].condMutex->var++;
                    pthread_cond_broadcast(&tdata->wheels[0].condMutex->cond);
                }
                alarm(TIMEBEFOREWHEELTIMOUT);
                break;
            case SIGTSTP: // insert coin, start the game and the alarm
                tdata->gameState = ROLLING;
                pthread_mutex_lock(&(tdata->wheels[0].condMutex->m));
                tdata->wheels[0].condMutex->var = 0;
                // liberate the wheels
                pthread_cond_broadcast(&tdata->wheels[0].condMutex->cond);
                pthread_mutex_unlock(&(tdata->wheels[0].condMutex->m));
                tdata->coins++;
                alarm(TIMEBEFOREWHEELTIMOUT);
                break;
            case SIGQUIT: // quit the game
                quit = 1;
                break;
            case SIGALRM: // alarm about 3 or 5 seconds
                alarm(0); // disable the pending alarm 
                // if the 3 wheels aren't set (stoped)
                if (tdata->wheels[0].condMutex->var != NBRWHEELS) {
                    kill(getpid(), SIGINT);
                } else {
                    sleep(5);
                    tdata->gameState = WAITING;
                }
                break;
        }
    } while (quit == 0);
    // finish the programm properly
    pthread_mutex_lock(&(tdata->wheels[0].condMutex->m));
    tdata->wheels[0].condMutex->var = FINISHEDPROGRAM;
    pthread_cond_broadcast(&(tdata->wheels[0].condMutex->cond));
    pthread_mutex_unlock(&(tdata->wheels[0].condMutex->m));
    return NULL;
}
