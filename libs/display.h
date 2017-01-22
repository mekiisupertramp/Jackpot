//
// Created by Shinra on 18.01.17.
//

#ifndef _JACKPOT_DISPLAY_H
#define _JACKPOT_DISPLAY_H

#include "header.h"
#include "structThreads.h"


double waitAFrequency(struct timespec* start, struct timespec* finish, int frequency);
void* display(void* threadData);

#endif //JACKPOT_DISPLAY_H
