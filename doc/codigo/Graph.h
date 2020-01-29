/**
 * @file Graph.h
 * @brief This is the header of the class Graph. This file contains the
 * 		functions' declarations and all the names of data's types
 * 		manipulated in the class.
 * 
 * @author João Miguel Morgado Pereira Vieira, nº 79191, MEEC
 * @author Tomás Miguel Donga Cardoso, nº 79007, MEEC
 * 
 * @date December 5th, 2014 
 * */

#ifndef GraphHeader
#define GraphHeader

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "Defs.h"
#include "LinkedList.h"
#include "Heap.h"

/**
 * @typedef struct Graph_ Graph
 * @brief Giving the name Graph to the struct Graph_.
 * */
typedef struct Graph_ Graph;

/**
 * @typedef struct Link_ Link
 * @brief Giving the name Link to the struct Link_.
 * */
typedef struct Link_ Link;

/* Iniciliza um grafo */
Graph * graphInit( int vertices , int bridges , void ( * freeWeight )( Item ) );

/* Insere uma aresta */
void graphLinkInsert( Graph * graph , int city1 , int city2 , Item weight );

/* Liberta a memoria associada a um grafo */
void freeGraph( Graph * graph );

/* Cria uma nova aresta */
Link * newLink( int vertice , Item weight );

/* Calcula a arvore de caminhos mais curtos dado um vertice de origem */
void dijkstra( Graph * graph , int origin , int * shortest_path_tree , Item * bridges , int ( * weigh )( int , Item , Item * ) , int * weights , Heap * priority_queue );

/* Getter para o vertice de uma aresta */
int getVertice( Link * link );

/* Getter para o peso de uma aresta */
Item getWeight( Link * link );

/* Getter para o numero de vertices de um grafo */
int getNumberOfVertices( Graph * graph );

/* Imprime as adjacencias de um grafo */
void printGraph( Graph * graph );

/* Getter para as adjacencias de um vertice */
LinkedList * getAdjacencies( Graph * graph , int vertice );

/* Setter para o peso de uma aresta */
void setWeight( Link * link , Item weight );

#endif
