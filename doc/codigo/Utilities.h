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
#include "Heap.h"

/* Mostra ao utilizador a correta utilizacao do programa */
void usage( char ** argv );

/* Verifica se um ficheiro tem uma determinada extensao */
int equalExtentions( char * string , char * extention );

/* Salva uma string noutra */
char * saveString( char * string );

/* Obtem o nome do ficheiro de destino atraves do ficheiro de input */
char * getOutputFileName( char * input_filename , char * input_file_extention , char * output_file_extention );

/* Carrega a estrutura do grafo a partir do ficheiro */
Graph * getMapFromFile( char * map_filename );

/* Resolve sucessivamente os problemas de otimizacao dos clientes do ficheiro de input */
void computeBestPath( Graph * map , char * client_filename , char * output_filename );

/* Pesa uma aresta do grafo e retorna qual dos pesos e mais vantajoso (pode haver mais do que um) */
int weigh( int counter , Item bridge , Item * efective_weight );

/* Retorna o tempo de uma viagem e o tempo de espera */
int getTime( int counter , Bridge * bridge );

/* Imprime o caminho da cidade de origem ate a cidade de destino no ficheiro */
void printPath( FILE * output_file , int * shortest_path_tree , Bridge ** bridges , int destination , int origin );

/* Calcula o preco total de uma viagem */
int getTotalPrice( int * shortest_path_tree , Bridge ** bridges , int origin , int destination );

/* Calcula o tempo total de uma viagem */
int getTotalTime( int * shortest_path_tree , Bridge ** bridges , int origin , int destination );

/* Verifica se uma aresta segue as restricoes do tipo A */
int followRestrictionsA( Bridge * bridge );

/* Verifica se uma aresta segue as restricoes do tipo B */
int followRestrictionsB( int weight );

/* Define uma restricao */
void defineRestriction( char * restriction , char * value );

/* Liberta o peso de uma aresta */
void freeWeight( Item weight );

#endif
