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

/* Constroi uma nova estrutura */
Bridge *newBridge(int transportation, int duration, int price, int first_travel, int no_more_travels, int period);

/* Liberta memoria de uma estrutura */
void freeBridge(Item bridge);

/* Getter para o tipo de transporte de um peso */
int getTransportation(Bridge *bridge);

/* Getter para a duracao de um peso */
int getDuration(Bridge *bridge);

/* Getter para o preco de um peso */
int getPrice(Bridge *bridge);

/* Getter para o horario da primeira viagem */
int getFirstTravel(Bridge *bridge);

/* Getter para o tempo a partir do qual nao existem mais viagens */
int getNoMoreTravels(Bridge *bridge);

/* Getter para o periodo entre viagens */
int getPeriod(Bridge *bridge);

#endif
