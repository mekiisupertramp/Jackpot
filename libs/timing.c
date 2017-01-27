/**
 * \file timing.c
 * \brief timing's functions, allows the user to count the time in secondes, between a start and a stop call.
 * \author BUFFO Pierre, DA SILVA Gabriel, MEHMED Blazevic
 * \version 1.0
 * \date 25.01.2017
 */

#include "timing.h"

//globalss variables
struct timespec start, finish;

/**
 * get the first clock time
 */
void startTime(){
	clock_gettime(CLOCK_MONOTONIC, &start);
}

/**
 * get the second clock time
 */
void stopTime(){
	clock_gettime(CLOCK_MONOTONIC, &finish);
}

/**
 * get the difference between the first and the second clock time in seconds
 * @return elapsed time
 */
double getCntTime(){
	double elapsed = finish.tv_sec - start.tv_sec;
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	return elapsed;
}
