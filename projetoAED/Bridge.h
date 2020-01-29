/**
 * @file Bridge.h
 * @brief This file is the header of the class Bridge. Here we find the
 * 		declaration of all structures and methods related to this class.
 * 
 * @author João Miguel Morgado Pereira Vieira, nº 79191, MEEC
 * @author Tomás Miguel Donga Cardoso, nº 79007, MEEC
 * 
 * @date December 5th, 2014
 * */

#ifndef BridgeHeader
#define BridgeHeader

#include <stdlib.h>
#include <stdio.h>
#include "Defs.h"

/**
 * @typedef Bridge
 * @brief Naming the struct Bridge_ Bridge.
 * */
typedef struct Bridge_ Bridge;

/* Constructor for the class bridge. */
Bridge * newBridge( int transportation , int duration , int price , int first_travel , int no_more_travels , int period );

/* Eraser of bridges. */
void freeBridge( Item bridge );

/* Getters for the camps of the structure. As this is a private class,
 * direct attribution is not possible neither desired. */

int getTransportation( Bridge * bridge );

int getDuration( Bridge * bridge );

int getPrice( Bridge * bridge );

int getFirstTravel( Bridge * bridge );

int getNoMoreTravels( Bridge * bridge );

int getPeriod( Bridge * bridge );

#endif
