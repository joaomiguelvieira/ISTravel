#include "WeightedInteger.h"

struct WeightedInteger_
{
	int integer;
	int weight;
};

WeightedInteger * newWeightedInteger( int integer , int weight )
{
	WeightedInteger * new;
	
	new = ( WeightedInteger * ) malloc( sizeof( WeightedInteger ) );
	if( new == ( WeightedInteger * ) NULL )
		makeException( ERROR_MEMORY_ALLOCATION );
	
	( new -> integer ) = integer;
	( new -> weight ) = weight;
	
	return new;
}

void freeWeightedInteger( Item weighted_integer )
{
	free( ( WeightedInteger * ) weighted_integer );
	
	return;
}

int lessWeightWeightedInteger( Item integer1 , Item integer2 )
{
	if( ( ( ( WeightedInteger * ) integer1 ) -> weight ) < ( ( ( WeightedInteger * ) integer2 ) -> weight ) )
		return 1;
	else
		return 0;
}

int lessValueWeightedInteger( Item integer1 , Item integer2 )
{
	if( ( ( ( WeightedInteger * ) integer1 ) -> integer ) < ( ( ( WeightedInteger * ) integer2 ) -> integer ) )
		return 1;
	else
		return 0;
}
