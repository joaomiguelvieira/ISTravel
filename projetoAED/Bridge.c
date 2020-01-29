/**
 * @file Bridge.c
 * @brief This file contains all the structures and methods for 
 * 		Bridge's class.
 * 
 * @author João Miguel Morgado Pereira Vieira, nº 79191, MEEC
 * @author Tomás Miguel Donga Cardoso, nº 79007, MEEC
 * 
 * @date December 5th, 2014
 * */

#include "Bridge.h"

/**
 * @struct Bridge_
 * @brief This structures storages all the information about the weight
 * 		associated to a edge.
 * */

struct Bridge_
{
	int transportation;
	int duration;
	int price;
	int first_travel;
	int no_more_travels;
	int period;
};

/**
 * @fn getTransportation
 * @brief This functions is a getter for the transportation's type of
 * 		this bridge between two cities.
 * @param Bridge * bridge
 * 		Bridge we want to avaliate.
 * @return int
 * 		Type of transportation involved.
 * */
int getTransportation( Bridge * bridge )
{
	return ( bridge -> transportation );
}

/**
 * @fn getDuration
 * @brief This functions is a getter for the duration of this travel.
 * @param Bridge * bridge
 * 		Bridge we want to avaliate.
 * @return int
 * 		Duration of the travel.
 * */
int getDuration( Bridge * bridge )
{
	return ( bridge -> duration );
}

/**
 * @fn getPrice
 * @brief This is a getter for the price of a travel.
 * @param Bridge * bridge
 * 		Bridge we want to avaliate.
 * @return int
 * 		Price of the travel.
 * */
int getPrice( Bridge * bridge )
{
	return ( bridge -> price );
}

/**
 * @fn getFirstTravel
 * @brief This is a getter to the first daily travel's hour. Indicates
 * 		the hour in which occurs the first connection of this nature.
 * @param Bridge * bridge
 * 		Bridge we want to avaliate.
 * @return int
 * 		First travel's hour.
 * */
int getFirstTravel( Bridge * bridge )
{
	return ( bridge -> first_travel );
}

/**
 * @fn getNoMoreTravels
 * @brief This is a getter to the hour in which does not occur any more
 * 		travel in that day.
 * @param Bridge * bridge
 * 		Bridge we want to avaliate.
 * @return int
 * 		After this hour does not occur more travels.
 * */
int getNoMoreTravels( Bridge * bridge )
{
	return ( bridge -> no_more_travels );
}

/**
 * @fn getPeriod
 * @brief This is a getter for the period of an expecified
 * 		transportation.
 * @param Bridge * bridge
 * 		Bridge we want to avaliate.
 * @return int
 * 		Period of the avaliated connection.
 * */
int getPeriod( Bridge * bridge )
{
	return ( bridge -> period );
}

/**
 * @fn newBridge
 * @brief This function is a constructor for the structure bridge.
 * @param int transportation
 * 		Type of transportation (bus, plane, train, boat).
 * @param int duration
 * 		Duration of this connection.
 * @param int price
 * 		Specifies the price of the travel.
 * @param int first_travel
 * 		This value specifies the time of first daily travel occurence.
 * @param int no_more_travels
 * 		After this hour no more daily travels occur.
 * @param int period
 * 		Period between connections after the first travel and before 
 * 		last one.
 * @return Bridge *
 * 		Returns the correspondent bridge buit with the parameters passed
 * 		by argument.
 * */
Bridge * newBridge( int transportation , int duration , int price ,
	int first_travel , int no_more_travels , int period )
{
	Bridge * new;
	
	/* Allocating the memory for the new bridge. */
	new = ( Bridge * ) malloc( sizeof( Bridge ) );
	if( new == ( Bridge * ) NULL )
		makeException( ERROR_MEMORY_ALLOCATION );
	
	/* Setting all the values of the new bridge. */
	( new -> transportation ) = transportation;
	( new -> duration ) = duration;
	( new -> price ) = price;
	( new -> first_travel ) = first_travel;
	( new -> no_more_travels ) = no_more_travels;
	( new -> period ) = period;
	
	return new;
}

/**
 * @fn freeBridge
 * @brief This function defines how to release the structures of type
 * 		Bridge.
 * @param Item bridge
 * 		Void pointer to a structure of type bridge. To manipulate it
 * 		we need to do a cast.
 * @return None.
 * */
void freeBridge( Item bridge )
{
	/* In this case, the structure bridge does not have any dynamic
	 * memory associated to it, so to release the all structure we just
	 * have to do a simple free of the pointer. */
	free( ( Bridge * ) bridge );
	
	return;
}
