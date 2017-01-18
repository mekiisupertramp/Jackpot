//
// Created by Shinra on 18.01.17.
//

#ifndef JACKPOT_CONTROLLER_H
#define JACKPOT_CONTROLLER_H

#include "wheels.h"
#define NBRWHEELS 3
#define BASETIME 120

typedef struct display_t{
    wheel wheels[NBRWHEELS];
} display;

#endif //JACKPOT_CONTROLLER_H
