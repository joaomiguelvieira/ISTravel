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

/* Inicia uma nova lista */
LinkedList * initList();

/* Insere um elemento no inicio da lista */
LinkedList * insertUnsortedItemList( LinkedList * list , Item item );

/* Insere um elemento na lista segundo um criterio de ordenacao */
LinkedList * insertSortedItemList( LinkedList * list , Item item , int ( * lessThan )( Item , Item ) );

/* Retorna o elemento seguinte */
LinkedList * getNextNodeList( LinkedList * node );

/* Retorna o elemento anterior */
LinkedList * getPreviousNodeList( LinkedList * list , LinkedList * node );

/* Retorna o conteudo de um elemento */
Item getItemNode( LinkedList * node );

/* Liberta uma lista */
void freeList( LinkedList * list , void ( * freeStructure )( Item ) );

/* Itera uma lista */
void forEach( LinkedList * list , void ( * function )( Item ) );

/* Retorna o tamanho de uma lista */
int getListLenght( LinkedList * list );

/* Insere um elemento na segunda posicao de uma lista (nao altera o inicio) */
void insertWithNoReturn( LinkedList * list , Item item );

#endif
