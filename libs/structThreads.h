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
#define NRBSYMBOLS 10
#define BASETIME 12000  //time in miliseconds to wait before turn
#define FREQUENCY 30    // screen refresh frequency
#define INITIALANTE 1   // (mise initiale)
#define INITIALCOINS 10 // Initial coins in the machine
#define TIMEBEFOREWHEELTIMOUT 3 // time before a wheel stop spinning by itself

#define WAITING  0 	// the game is waiting for a coin
#define ROLLING  1	// the game is turning
#define FINISHED 2	// the game is finished and the scores are given
#define ENDMSG   3  // the game is finished too, show the end message

#define LOST 0		  // the user lost the party
#define DOUBLEWIN 1	// the user made a double win
#define FULLWIN 2	  // the user won

#define FINISHEDPROGRAM -1 // the user decided to quit the game

/**
 * \struct cond
 * \brief contain condition's variable and the mutex
 */
typedef struct cond_t{
    int var;                    /*<! shared variable */
    pthread_mutex_t m;          /*<! shared mutex */
    pthread_cond_t  cond;       /*<! shared condition variable */
}cond_t;

/**
 * \struct wheel_t
 * \brief contain wheel_t's data such as id, current value and timeBase
 */
typedef struct wheel_t{
    int id;                     /*<! id of the wheel */
    int value;                  /*<! value of the wheel */
    int timeBase;               /*<! time divided by the id is the time for the wheel to wait before next change */
    cond_t* condMutex;          /*<! structure containing the condition variable with mutex */
} wheel_t;

/**
 * \struct controller_t
 * \brief structure given to the threads, contain all game data
 */
typedef struct controller_t{
    wheel_t wheels[NBRWHEELS];  /*<! struct pour gérer les signaux à ajouter ici */
    int gameState;              /*<! WAITING, ROLLING, FINISHED */
    int win;                    /*<! LOST, DOUBLEWIN, FULLWIN */
    int coinsWin;               /*<! coins win by the player */
    int coins;                  /*<! coins left in the machine */
} controller_t;

#endif
