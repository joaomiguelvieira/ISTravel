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

/* Elimina todos os elementos do heap */
void cleanHeap( Heap * h );

/* Insere um elemento no heap sem o reorganizar */
int directInsert( Heap * h , int element );

/* Corrige um elemento em relacao aos seus inferiores */
void fixDown( Heap * h , int k );

/* Corrige um elemento em relacao aos seus superiores */
void fixUp( Heap * h , int k );

/* Liberta o heap */
void freeHeap( Heap * h );

/* Funcao de sorting baseada em acervos */
void heapSort( Heap * h );

/* Converte uma tabela num heap */
void heapify( Heap * h );

/* Insere um elemento no heap e repoe a condicao de acervo */
int insert( Heap * h , int element );

/* Cria um novo heap */
Heap * newHeap( int size , int * priority );

/* Remove o maior elemento do heap */
int removeMax( Heap * h );

/* Verifica se uma tabela e um acervo */
int verifyHeap( Heap * h );

/* Corrige a posicao de um elemento do acervo */
void incPriority( Heap * heap , int index );

/* Verifica se um acervo esta vazio */
int isHeapEmpty( Heap * heap );
