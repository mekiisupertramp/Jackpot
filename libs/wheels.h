//
// Created by Shinra on 18.01.17.
//

#ifndef JACKPOT_WHEELS_H
#define JACKPOT_WHEELS_H

#include "header.h"
#include "structThreads.h"
//#include "timing.h"

double waitAMoment(struct timespec* start, struct timespec* finish, int time);
void* spinner(void* threadData);

#endif //JACKPOT_WHEELS_H
