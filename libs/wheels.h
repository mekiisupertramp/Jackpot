//
// Created by Shinra on 18.01.17.
//

#ifndef JACKPOT_WHEELS_H
#define JACKPOT_WHEELS_H

#include "timing.h"

typedef struct wheel_t {
    int id;
    int value;
    int timeBase;
} wheel;

void* spinner(void* threadData);

#endif //JACKPOT_WHEELS_H
