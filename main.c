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

int main(int argc, char** argv){

    cond_t condVar;
    condVar.var = 0;
    condVar.cond =  (pthread_cond_t)PTHREAD_COND_INITIALIZER;
    condVar.m = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;

    controller_t controllerData;
    pthread_t wheelsT[NBRWHEELS];
    pthread_t disp;
    controllerData.gameState = WAITING;
    controllerData.win = LOST;
    controllerData.coinsWin = 0;
    controllerData.coins = 12;


    // blocking all the signals for heritage
    sigset_t mask;
    sigfillset(&mask);
    pthread_sigmask(SIG_SETMASK,&mask,NULL); // block all signals

    //init wheels data
    for (int i = 0; i < NBRWHEELS; ++i) {
        controllerData.wheels[i].id = i;
        controllerData.wheels[i].value = 0;
        controllerData.wheels[i].timeBase = BASETIME;
        controllerData.wheels[i].condMutex = &condVar;
        // create the wheels threads
        if(pthread_create(&wheelsT[i],NULL,spinner,&controllerData.wheels[i]) != 0){
            fprintf(stderr, "wheel_t pthread_create failed !\n");
            return EXIT_FAILURE;
        }
    }
    // create the display threads
		if(pthread_create(&disp,NULL,display,&controllerData) != 0){
			fprintf(stderr, "disp pthread_create failed !\n");
			return EXIT_FAILURE;
		}

/*
    // create the signal threads
if(pthread_create(&sign,NULL,TAFONCTION,&controllerData) != 0){
  fprintf(stderr, "sign pthread_create failed !\n");
  return EXIT_FAILURE;
}
*/


    pthread_mutex_lock(&condVar.m);
    while (condVar.var != FINISHEDPROGRAM){

        // ************** insert a coin donc normalement on doit faire
        // ************** controllerData.coins += 1;

      while(condVar.var != NBRWHEELS)
        pthread_cond_wait(&condVar.cond,&condVar.m);

      controllerData.gameState = FINISHED;
      //controllerData.win = GetWin(); ********** PIERRE ***********************
      int tempCoins;
      switch(controllerData.win){
        case FULLWIN: tempCoins = (int)floor(controllerData.coins/2);
          break;
        case DOUBLEWIN: tempCoins = INITIALANTE*2;
          break;
        case LOST: tempCoins = 0;
          break;
      }

      // avoiding to win more coins that stocked in the machine
      if(tempCoins <= controllerData.coins)
         controllerData.coinsWin = tempCoins;
      else
         controllerData.coinsWin = controllerData.coins;
      // updating the coins stayed in the machine
      controllerData.coins -= controllerData.coinsWin;

      // lance timer 5s
      //***** au bout de 5 secondes le signal ou je sais pas quoi met la variable gameState
      //***** à WAINTING (c'est le mode qui affichera le message "Insert a coin")

      // waiting for restart
      while(condVar.var == NBRWHEELS)
        pthread_cond_wait(&condVar.cond,&condVar.m);
    }
    pthread_mutex_unlock(&condVar.m);

    for (int i = 0; i < NBRWHEELS; ++i) {
        // create the wheels threads
        if(pthread_join(wheelsT[i],NULL) != 0){
            fprintf(stderr, "wheelsT pthread_join failed !\n");
            return EXIT_FAILURE;
        }
    }
    if(pthread_join(disp,NULL) != 0){
        fprintf(stderr, "disp pthread_join failed !\n");
        return EXIT_FAILURE;
    }
      /*
    if(pthread_join(sign,NULL) != 0){
        fprintf(stderr, "sign pthread_join failed !\n");
        return EXIT_FAILURE;
    }
      */

    return 0;
}
