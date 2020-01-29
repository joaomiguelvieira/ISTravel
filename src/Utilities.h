/**
 * @file Utilities.h
 * @brief This file is the header of Utilities interface. Here we see
 * 		declared all the functions headers.
 * 
 * @author João Miguel Morgado Pereira Vieira, nº 79191, MEEC
 * @author Tomás Miguel Donga Cardoso, nº 79007, MEEC
 * 
 * @date December 5th, 2014
 * */

#ifndef UtilitiesHeader
#define UtilitiesHeader

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Defs.h"
#include "Graph.h"
#include "Bridge.h"
#include "LinkedList.h"

void usage( char ** argv );

int equalExtentions( char * string , char * extention );

char * saveString( char * string );

char * getOutputFileName( char * input_filename , char * input_file_extention , char * output_file_extention );

Graph * getMapFromFile( char * map_filename );

void computeBestPath( Graph * map , char * client_filename , char * output_filename );

int weigh( int counter , Item bridge , Item * efective_weight );

int getTime( int counter , Bridge * bridge );

void printPath( FILE * output_file , int * shortest_path_tree , Bridge ** bridges , int destination , int origin );

int getTotalPrice( int * shortest_path_tree , Bridge ** bridges , int origin , int destination );

int getTotalTime( int * shortest_path_tree , Bridge ** bridges , int origin , int destination );

int followRestrictionsA( Bridge * bridge );

int followRestrictionsB( int weight );

void defineRestriction( char * restriction , char * value );

void freeWeight( Item weight );

#endif
