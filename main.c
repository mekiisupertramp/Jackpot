/**
* \file main.c
* \brief programm's entry point
* \author BUFFO Pierre, DA SILVA Gabriel, MEHMED Blazevic
* \version 1.0
* \date 25.01.2017
*/

#include <math.h>
#include "libs/header.h"
#include "libs/structThreads.h"
#include "libs/display.h"
#include "libs/wheels.h"
#include "libs/signals.h"

int main(int argc, char **argv) {

    cond_t condVar;
    //condVar.var = NBRWHEELS+1;
    condVar.var = 0;
    condVar.cond = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
    condVar.m = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;

    controller_t controllerData;
    pthread_t wheelsT[NBRWHEELS];
    pthread_t disp;
    pthread_t sign;
    controllerData.gameState = WAITING;
    controllerData.win = LOST;
    controllerData.coinsWin = 0;
    controllerData.coins = INITIALCOINS;


    // blocking all the signals for heritage
    sigset_t mask;
    sigfillset(&mask);
    pthread_sigmask(SIG_SETMASK, &mask, NULL); // block all signals

    //init wheels data
    for (int i = 0; i < NBRWHEELS; ++i) {
        controllerData.wheels[i].id = i;
        controllerData.wheels[i].value = 0;
        controllerData.wheels[i].timeBase = BASETIME;
        controllerData.wheels[i].condMutex = &condVar;
        // create the wheels threads
        if (pthread_create(&wheelsT[i], NULL, spinner, &controllerData.wheels[i]) != 0) {
            fprintf(stderr, "wheel_t pthread_create failed !\n");
            return EXIT_FAILURE;
        }
    }
    // create the display threads
    if (pthread_create(&disp, NULL, display, &controllerData) != 0) {
        fprintf(stderr, "disp pthread_create failed !\n");
        return EXIT_FAILURE;
    }

    // create the signal threads
    if(pthread_create(&sign,NULL,signalReceiver,&controllerData) != 0){
      fprintf(stderr, "sign pthread_create failed !\n");
      return EXIT_FAILURE;
    }

    pthread_mutex_lock(&condVar.m);
    while (condVar.var != FINISHEDPROGRAM) {

        while (condVar.var != NBRWHEELS && condVar.var != FINISHEDPROGRAM) {
            pthread_cond_wait(&condVar.cond, &condVar.m);
        }
        controllerData.gameState = FINISHED;
        controllerData.win = GetWin(controllerData);
        int tempCoins;
        switch (controllerData.win) {
            case FULLWIN:
                tempCoins = (int) floor(controllerData.coins / 2);
            break;
            case DOUBLEWIN:
                tempCoins = INITIALANTE * 2;
            break;
            case LOST:
                tempCoins = 0;
            break;
        }

        // avoiding to win more coins that stocked in the machine
        if (tempCoins <= controllerData.coins)
            controllerData.coinsWin = tempCoins;
        else
            controllerData.coinsWin = controllerData.coins;
        // updating the coins stayed in the machine
        controllerData.coins -= controllerData.coinsWin;
        kill(getpid(),SIGALRM);

        // waiting for restart
        while (condVar.var == NBRWHEELS && condVar.var != FINISHEDPROGRAM)
            pthread_cond_wait(&condVar.cond, &condVar.m);
    }
    pthread_mutex_unlock(&condVar.m);

    for (int i = 0; i < NBRWHEELS; ++i) {
        // create the wheels threads
        if (pthread_join(wheelsT[i], NULL) != 0) {
            fprintf(stderr, "wheelsT pthread_join failed !\n");
            return EXIT_FAILURE;
        }
    }

    if (pthread_join(disp, NULL) != 0) {
        fprintf(stderr, "disp pthread_join failed !\n");
        return EXIT_FAILURE;
    }

    if(pthread_join(sign,NULL) != 0){
        fprintf(stderr, "sign pthread_join failed !\n");
        return EXIT_FAILURE;
    }

    pthread_cond_destroy(&(condVar.cond));
    pthread_mutex_destroy(&(condVar.m));
    return 0;
}
