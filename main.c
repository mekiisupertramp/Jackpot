//
// Created by pierre.buffo on 11.01.17.
//

#include "libs/header.h"
#include "libs/structThreads.h"
#include "libs/display.h"
#include "libs/wheels.h"

int main(int argc, char** argv){	
/*
 * Si vous voulez tester la fonction display alors mettez tout
 *  en commentaire et décommenter ce bloc
	controller con;
	con.gameState = FINISHED;
	con.wheels[0].value = 5;
	con.wheels[1].value = 7;
	con.wheels[2].value = 2;
	con.win = FULLWIN;
	con.coinsWin = 6;
	con.coins = 12;
	
	display((void*)&con);
	*/
	
    controller controllerData;
    pthread_t wheelsT[NBRWHEELS];
    pthread_t disp;
    bool running = true;
    controllerData.gameState = WAITING;
    
    while (running){

        //init wheels data
        for (int i = 0; i < NBRWHEELS; ++i) {
            controllerData.wheels[i].id = i;
            controllerData.wheels[i].value = 0;
            controllerData.wheels[i].timeBase = BASETIME;
            // create the wheels threads
            if(pthread_create(&wheelsT[i],NULL,spinner,&controllerData) != 0){
                fprintf(stderr, "wheel pthread_create failed !\n");
                return EXIT_FAILURE;
            }
        }
        // create the display threads
		if(pthread_create(&disp,NULL,display,&controllerData) != 0){
			fprintf(stderr, "wheel pthread_create failed !\n");
			return EXIT_FAILURE;
		}

        //si fin de jeu passer running à false
    }
    return 0;
}
