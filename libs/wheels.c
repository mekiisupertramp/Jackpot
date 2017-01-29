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
    wheel_t* tdata = (wheel_t*) threadData;
    clock_gettime(CLOCK_MONOTONIC, &start);
    //bool exitValue = true;

    while(1){
        bool exit = false;
        // the thread sleep if wheel number is smaller or equal to the variable condition
        pthread_mutex_lock(&(tdata->condMutex->m));
        while(tdata->condMutex->var > tdata->id)
            pthread_cond_wait(&(tdata->condMutex->cond),&(tdata->condMutex->m));
        // if var == -1 it's time to go home
        if(tdata->condMutex->var == FINISHEDPROGRAM)
            exit = true;
        pthread_mutex_unlock(&(tdata->condMutex->m));
        // go home
        if(exit) return NULL;

        tdata->value+=1;
        usleep(waitAMoment(&start, &finish, (int)(BASETIME/(tdata->timeBase/(tdata->id+1)))));
        if (tdata->value>=NRBSYMBOLS-1) {
            tdata->value = 0;
        }
    }
    return NULL;
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

int GetWin(controller_t controllerData){
    int winStatus = FULLWIN;
    int provSymbol = controllerData.wheels[0].value;
    int provSymbol2 = -1;
    for (int i = 0; i < NBRWHEELS; ++i) {
        if (provSymbol != controllerData.wheels[i].value){
            winStatus = DOUBLEWIN;
            if (provSymbol2 == -1) {
                provSymbol2 = controllerData.wheels[i].value;
            } else {
                if (provSymbol2 != controllerData.wheels[i].value){
                    return LOST;
                }
            }
        }
    }
    return winStatus;
}
