/**
* \file signals.c
* \brief signals library
* \author BUFFO Pierre, DA SILVA Gabriel, MEHMED Blazevic
* \version 1.0
* \date 25.01.2017
*/

#ifndef SIGNAL_H
#define  SIGNAL_H

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <pthread.h>

void *signalReceiver(void *datas);

#endif
