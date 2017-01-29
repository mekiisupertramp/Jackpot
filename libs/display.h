/**
* \file display.h
* \brief graphic library prototypes
* \author BUFFO Pierre, DA SILVA Gabriel, MEHMED Blazevic
* \version 1.0
* \date 25.01.2017
*/

#ifndef _JACKPOT_DISPLAY_H
#define _JACKPOT_DISPLAY_H

#include "header.h"
#include "structThreads.h"


double waitAFrequency(struct timespec* start, struct timespec* finish,
                                                                int frequency);
void* display(void* threadData);

#endif //JACKPOT_DISPLAY_H
