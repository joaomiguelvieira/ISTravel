/**
 * @file Heap.h
 * @brief This file is the header of heap's class. Here we find declared
 * 		all the methods, defined all the data structures and the class
 * 		defines.
 * 
 * @author João Miguel Morgado Pereira Vieira, nº 79191, MEEC
 * @author Tomás Miguel Donga Cardoso, nº 79007, MEEC
 * 
 * @date December 5th, 2014
 * */

#include <stdlib.h>
#include <stdio.h>
#include "Defs.h"

/* Criterium of comparation between two elements in the heap. */
#define LESS( A , B ) ( ( h -> priority )[ A ] > ( h -> priority )[ B ] )

/**
 * @typedef struct Heap_ Heap
 * @brief Giving the name Heap to the struct Heap_.
 * */
typedef struct Heap_ Heap;

void cleanHeap( Heap * h );

int directInsert( Heap * h , int element );

void fixDown( Heap * h , int k );

void fixUp( Heap * h , int k );

void freeHeap( Heap * h );

void heapSort( Heap * h );

void heapify( Heap * h );

int insert( Heap * h , int element );

Heap * newHeap( int size , int * priority );

int removeMax( Heap * h );

int verifyHeap( Heap * h );

void incPriority( Heap * heap , int index );

int isHeapEmpty( Heap * heap );
