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

Graph *graphInit(int vertices, int bridges, void ( *freeWeight )(Item));

void graphLinkInsert(Graph *graph, int city1, int city2, Item weight);

void freeGraph(Graph *graph);

Link *newLink(int vertice, Item weight);

void dijkstra(Graph *graph, int origin, int *shortest_path_tree, Item *bridges,
              int ( *weigh )(int, Item, Item *), int *weights, Heap *priority_queue);

int getVertice(Link *link);

Item getWeight(Link *link);

int getNumberOfVertices(Graph *graph);

void printGraph(Graph *graph);

LinkedList *getAdjacencies(Graph *graph, int vertice);

void setWeight(Link *link, Item weight);

#endif
