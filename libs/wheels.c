/**
 * \file wheels.c
 * \brief wheels's functions
 * \author BUFFO Pierre, DA SILVA Gabriel, MEHMED Blazevic
 * \version 1.0
 * \date 25.01.2017
 */

#include "wheels.h"

/**
 * run the wheels, "rien ne va plus"
 * @param threadData - thread's data, containing speed of rotation and current value
 * @return NULL
 */
void* spinner(void* threadData){
    struct timespec start, finish;
    controller* tdata = (controller*) threadData;
    clock_gettime(CLOCK_MONOTONIC, &start);
    //bool exitValue = true;

    while(1){
        tdata->wheels[0].value+=1;
        usleep(waitAMoment(&start, &finish, (int)(BASETIME/tdata->wheels[0].value)));
    }
}

/**
 * calculate the time to wait before the next refresh with the process time
 * @param start - start struct with the timer's begin
 * @param finish - finish struct with the timer's end
 * @param time - time in miliseconds to wait
 * @return time to wait in nanoseconds or 0 if work process too long
 */
 
double waitAMoment(struct timespec* start, struct timespec* finish, int time){

    double sleepTime, deltaT = 0;
    clock_gettime(CLOCK_MONOTONIC, finish);
    deltaT = (*finish).tv_sec - (*start).tv_sec;
    deltaT += ((*finish).tv_nsec - (*start).tv_nsec)/1000000000.0;
    sleepTime = (time/1000.0) - deltaT;
    clock_gettime(CLOCK_MONOTONIC, start);

    return (sleepTime > 0) ? sleepTime : 0;
}
