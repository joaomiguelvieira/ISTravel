/**
 * @file Defs.h
 * @brief This is the header of Defs.c. Contains not only the header of
 * 		the functions but a lot of other global declarations that make
 * 		part of other classes' heritage.
 * 
 * @author João Miguel Morgado Pereira Vieira, nº 79191, MEEC
 * @author Tomás Miguel Donga Cardoso, nº 79007, MEEC
 * 
 * @date December 5th, 2014 
 * */

#ifndef DefsHeader
#define DefsHeader

/**
 * @def REAL_MACHINE
 * @brief This define provides the correct working of some outputs that
 * 		shall not be shown in simulater environment.
 * */
/* #define REAL_MACHINE */

/**
 * @def PROGRESSION
 * @brief This define provides outputs that guide the user in the 
 * 		progression of the algorithm.
 * */
/* #define PROGRESSION */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @def 'operational macros'
 * @brief This macros constitutes just a simplification of some basic
 * 		operations as exchange two integers that envolves several
 * 		elementary operations.
 * */
#define EXCH(A, B) { int third; third = A; A = B; B = third; }

/**
 * @def ERROR_<type>
 * @brief Macros used by the fuction makeException. Each macro
 * 		specifies an error's type.
 * */
#define ERROR_UNKNOWN -1
#define ERROR_USAGE 1
#define ERROR_FILE_MAN 2
#define ERROR_FILE_EXTENTION 3
#define ERROR_MEMORY_ALLOCATION 4
#define ERROR_UNINITIALIZED_STRUCTURE 5
#define ERROR_CAMP_NOT_EXPECTED 6
#define ERROR_FULL_MEMORY 7
#define ERROR_OUT_OF_RANGE 8

/**
 * @def 'numerical macros'
 * @brief Macros used in general appliances.
 * */
#define LINEWIDTH 100
#define DAY_TIME 1440

/**
 * @def 'extentions macros'
 * @brief These macros define the accepted extentions for program to
 * 		work on.
 * */
#define EXTENTION_CLIENT ".cli"
#define EXTENTION_MAP ".map"
#define EXTENTION_OUTPUT ".sol"

/**
 * @def 'transportations' codes'
 * @brief Each macro of this represents internaly a kind of 
 * 		transportation.
 * */
#define BUS 1
#define PLANE 2
#define BOAT 3
#define TRAIN 4

/**
 * @def 'optimization's criterium'
 * @brief Each macro of this codifies an optimization's criterium.
 * */
#define TIME 1
#define COST 2

/**
 * @def 'restriction's code'
 * @brief Each macro of this codifies a permited restriction.
 * */
#define A1 1
#define A2 2
#define A3 3
#define B1 4
#define B2 5

/**
 * @typedef void * Item
 * @brief Definition of type Item as a pointer for void.
 * */
typedef void *Item;

void makeException(int error_code);

int getTransportationFromString(char *transportation_s);

int getRestriction(char *restriction_s);

int getOptimizationCriterium(char *criterium);

#endif
