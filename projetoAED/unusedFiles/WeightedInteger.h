#ifndef WeightedIntegerHeader
#define WeightedIntegerHeader

#include <stdlib.h>

typedef WeightedInteger_ WeightedInteger;


WeightedInteger * newWeightedInteger( int integer , int weight );

void freeWeightedInteger( Item weighted_integer );

int lessWeightWeightedInteger( Item integer1 , Item integer2 );

int lessValueWeightedInteger( Item integer1 , Item integer2 );

#endif
