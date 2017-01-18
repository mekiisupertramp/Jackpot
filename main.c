//
// Created by pierre.buffo on 11.01.17.
//

#include "libs/header.h"
#define NBRWHEELS 3
#define BASETIME 120

typedef struct controller_t{
    wheel wheels[NBRWHEELS];
    //struct pour gérer les signaux à ajouter ici
    int coins;
    int win;
    int gameState;
} controller;

int main(int argc, char** argv){
    controller controllerData;
    pthread_t wheelsT[NBRWHEELS];
    bool running = true;

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

        //si fin de jeu passer running à false
    }


    printf("derp\n");
    return 0;
}