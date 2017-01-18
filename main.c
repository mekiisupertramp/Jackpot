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
    controller controllerData = malloc(sizeof(controller));
    pthread_t wheelsT[NBRWHEELS];
    bool running = true;

    while (running){
        for (int i = 0; i < NBRWHEELS; ++i) {
            controllerData.wheels[i].id = i;
            controllerData.wheels[i].value = 0;
            controllerData.wheels[i].timeBase = BASETIME;
        }



        //si fin de jeu passer running à false
    }
    free(controllerData);


    printf("derp\n");
    return 0;
}