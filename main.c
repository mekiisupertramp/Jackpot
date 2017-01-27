/**
* \file main.c
* \brief programm's entry point
* \author BUFFO Pierre, DA SILVA Gabriel, MEHMED Blazevic
* \version 1.0
* \date 25.01.2017
*/

#include "libs/header.h"
#include "libs/structThreads.h"
#include "libs/display.h"
#include "libs/wheels.h"

int main(int argc, char** argv){

    cond_t condVar;
    condVar.var = 0;
    condVar.m = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_init(&condVar.cond,NULL);

    controller_t controllerData;
    pthread_t wheelsT[NBRWHEELS];
    pthread_t disp;
    controllerData.gameState = WAITING;
    controllerData.win = FULLWIN;
    controllerData.coinsWin = 0;
    controllerData.coins = 12;

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
			fprintf(stderr, "wheel_t pthread_create failed !\n");
			return EXIT_FAILURE;
		}



    return 0;
}
