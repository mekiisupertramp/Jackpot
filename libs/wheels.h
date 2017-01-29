/**
 * \file wheels.h
 * \brief wheels's prototypes
 * \author BUFFO Pierre, DA SILVA Gabriel, MEHMED Blazevic
 * \version 1.0
 * \date 25.01.2017
 */

#ifndef JACKPOT_WHEELS_H
#define JACKPOT_WHEELS_H

#include "header.h"
#include "structThreads.h"

double waitAMoment(struct timespec* start, struct timespec* finish, int time);
void* spinner(void* threadData);
int GetWin(controller_t controllerData);

#endif //JACKPOT_WHEELS_H
