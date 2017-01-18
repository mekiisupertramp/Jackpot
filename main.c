//
// Created by pierre.buffo on 11.01.17.
//

#include "libs/header.h"
#define NBRWHEELS 3
#define BASETIME 120

int main(int argc, char** argv){
    wheel wheels[NBRWHEELS];
    bool running = true;

    while (running){
        for (int i = 0; i < NBRWHEELS; ++i) {
            wheels[i] = malloc(sizeof(wheel));
            wheels[i].id = i;
            wheels[i].value = 0;
            wheels[i].timeBase = BASETIME;
        }
    }

    printf("derp\n");
    return 0;
}