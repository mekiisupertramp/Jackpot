/**
* \file display.c
* \brief graphic library functions
* \author BUFFO Pierre, DA SILVA Gabriel, MEHMED Blazevic
* \version 1.0
* \date 25.01.2017
*/

#include "display.h"

#define CLEARSCREEN "\e[2J" /*<! ANSI code to clear the screen */
#define GOHOME "\e[H"  /*<! ANSI code to move the cursor to 0,0 */

const char* SYMBOLES[] = {"0","1","2","3","4","5","6","7","8","9"};
/***********************************************************************
 * function given to the display thread
 * @param threadData struct containing data to display
 * @return NULL
 **********************************************************************/
void* display(void* threadData){

	controller_t* tdata = (controller_t*)(threadData);
	struct timespec start, finish;
	clock_gettime(CLOCK_MONOTONIC, &start);

	// array with the possible messages
	char* topScreen[3];
	topScreen[WAITING] = "Insert a coin to start a game...";
	topScreen[ROLLING] = "Game started!";
	topScreen[FINISHED] = "Game finished!";

	char* winMessage[3];
	winMessage[LOST] = "You Lost!";
	winMessage[DOUBLEWIN] = "Double win!";
	winMessage[FULLWIN] = "Jackpot!";

	while(1){
		// the text to display is selected in the array
		printf(CLEARSCREEN GOHOME "%s\n",topScreen[tdata->gameState]);
		printf("\n ");
		// print the symbols separated by a space
		for(int i = 0; i < NBRWHEELS; i++)
			printf("%s ",SYMBOLES[tdata->wheels[i].value]);

		printf("\n\n");
		if(tdata->gameState == FINISHED){
			printf("%s\n",winMessage[tdata->win]);
			printf("You won %d coins\n",tdata->coinsWin);
			printf("%d coins left in the machine\n",tdata->coins);
		}
		// waiting before refresh
		usleep(waitAFrequency(&start,&finish,FREQUENCY));

        if (tdata->gameState == FINISHEDPROGRAM){
            return NULL;
        }
	}
	return NULL;
}

/***********************************************************************
 * calculate the time to wait before the next refresh with the time of process
 * @param start Start struct with the timer's begin
 * @param finish Finish struct with the timer's end
 * @param frequency freq of screen refresh
 * @return time to wait in nanoseconds or 0 if work process too long
 **********************************************************************/
double waitAFrequency(struct timespec* start, struct timespec* finish, int frequency){

	double sleepTime, deltaT = 0;
	clock_gettime(CLOCK_MONOTONIC, finish);
	deltaT = (*finish).tv_sec - (*start).tv_sec;
	deltaT += ((*finish).tv_nsec - (*start).tv_nsec)/1000000000.0;
	sleepTime = (1000000.0/frequency) - deltaT;
	clock_gettime(CLOCK_MONOTONIC, start);

	return (sleepTime > 0) ? sleepTime : 0;
}
