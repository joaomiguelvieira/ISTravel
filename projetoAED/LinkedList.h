/**
 * @file LinkedList.h
 * @brief This file contains header of the class LinkedList.
 * 
 * @author João Miguel Morgado Pereira Vieira, nº 79191, MEEC
 * @author Tomás Miguel Donga Cardoso, nº 79007, MEEC
 * 
 * @date December 5th, 2014
 * */

#ifndef LinkedListHeader
#define	LinkedListHeader

#include <stdlib.h>
#include <stdio.h>
#include "Defs.h"

/**
 * @typedef struct LinkedList_ LinkedList
 * @brief Giving the name LinkedList to the struct LinkedList_.
 * */
typedef struct LinkedList_ LinkedList;

LinkedList * initList();

LinkedList * insertUnsortedItemList( LinkedList * list , Item item );

LinkedList * insertSortedItemList( LinkedList * list , Item item , int ( * lessThan )( Item , Item ) );

LinkedList * getNextNodeList( LinkedList * node );

LinkedList * getPreviousNodeList( LinkedList * list , LinkedList * node );

Item getItemNode( LinkedList * node );

void freeList( LinkedList * list , void ( * freeStructure )( Item ) );

void forEach( LinkedList * list , void ( * function )( Item ) );

int getListLenght( LinkedList * list );

void insertWithNoReturn( LinkedList * list , Item item );

#endif
