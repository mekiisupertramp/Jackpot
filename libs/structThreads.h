/**
 * \file structThreads.h
 * \brief threads struct and constants
 * \author BUFFO Pierre, DA SILVA Gabriel, MEHMED Blazevic
 * \version 1.0
 * \date 25.01.2017
 */

#ifndef _STRUCT_
#define _STRUCT_

#define NBRWHEELS 3
#define BASETIME 120 // time in miliseconds to wait before turn
#define FREQUENCY 30 // screen refresh frequency

#define WAITING 0 	// the game is waiting for a coin
#define ROLLING 1	// the game is turning
#define FINISHED 2	// the game is finished and the scores are given

#define LOST 0		// the user lost the party
#define DOUBLEWIN 1	// the user made a double win
#define FULLWIN 2	// the user won

/**
 * \struct wheel
 * \brief contain wheel's data such as id, current value and timeBase
 */
typedef struct wheel_t{
    int id;
    int value;
    int timeBase;
} wheel;

/**
 * \struct wheel
 * \brief structure given to the threads, contain all game data
 */
typedef struct controller_t{
    wheel wheels[NBRWHEELS];
    //struct pour gérer les signaux à ajouter ici
    int gameState; 	// WAITING, ROLLING, FINISHED
    int win; 		// LOST, DOUBLEWIN, FULLWIN
    int coinsWin;	// coins win by the player
    int coins;		// coins left in the machine
} controller;

#endif
