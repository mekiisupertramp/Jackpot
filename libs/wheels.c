//
// Created by Shinra on 18.01.17.
//

#include "wheels.h"

void* worker(void* threadData){
    struct timespec start, finish;
    wheel_t* tdata = (wheel_t*) threadData;
    clock_gettime(CLOCK_MONOTONIC, &start);
    bool exitValue = true;

    while(1){
        tdata.value+=1;
        usleep(waitAMoment(&start, &finish, 1/(tdata->timeBase/tdata->value)));
    }
}

/***********************************************************************
 * calculate the time to wait before the next refresh with the process
 *	time
 * @param start 	  - start struct with the timer's begin
 * @param finish 	  - finish struct with the timer's end
 * @param frequency - freq of screen refresh
 * @return time to wait in nanoseconds or 0 if work process too long
 **********************************************************************/
double waitAMoment(struct timespec* start, struct timespec* finish, int frequency){

    double sleepTime, deltaT = 0;
    clock_gettime(CLOCK_MONOTONIC, finish);
    deltaT = (*finish).tv_sec - (*start).tv_sec;
    deltaT += ((*finish).tv_nsec - (*start).tv_nsec)/1000000000.0;
    sleepTime = (1000000.0/frequency) - deltaT;
    clock_gettime(CLOCK_MONOTONIC, start);

    return (sleepTime > 0) ? sleepTime : 0;
}