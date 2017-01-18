//
// Created by pierre.buffo on 11.01.17.
//

#include "libs/header.h"


int main(int argc, char** argv){
    display displayData = malloc(sizeof(controller));
    pthread_t wheelsT[NBRWHEELS];
    bool running = true;

    while (running){
        for (int i = 0; i < NBRWHEELS; ++i) {
            controllerData.wheels[i] = malloc(sizeof(wheel));
            controllerData.wheels[i].id = i;
            controllerData.wheels[i].value = 0;
            controllerData.wheels[i].timeBase = BASETIME;
        }



        for (int j = 0; j < NBRWHEELS; ++j) {
            free(controllerData.wheels[i]);
        }
        //si fin de jeu passer running à false
    }
    free(controllerData);


    printf("derp\n");
    return 0;
}