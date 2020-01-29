#include "Heap.h"

struct Heap_
{
	int ( * less )( Item , Item );
	void ( * print )( Item );
	int n_elements;
	int size;
	Item * heapdata;
};

void ( * PrintItem )( Item );

int PrintHeap( Heap * h )
{
	int i;

	if ( ( h -> n_elements ) == 0 )
	{
		printf( "Heap is empty.\n" );
		return 0;
	}

	printf( "\n" );
	for( i = 0 ; i < ( h -> n_elements ) ; i++ )
		printf( "+-----" );
	
	printf( "+\n" );

	for( i = 0 ; i < ( h -> n_elements ) ; i++ )
		printf( "| %3d " , i );

	printf( "|\n" );

	for( i = 0 ; i < ( h -> n_elements ) ; i++ )
		printf( "+-----" );

	printf( "+\n" );

	for( i = 0 ; i < ( h -> n_elements ) ; i++ )
	{
		printf( "| " );
		( h -> print )( ( h -> heapdata )[ i ] );
		printf( " " );
	}
	
	printf( "|\n" );

	for (i = 0; i < h->n_elements; i++)
		printf("+-----");

	printf("+\n");

	return ( h -> n_elements );
}

void FixUp( Heap * h , int k )
{
	while ( ( k > 0 ) && ( h -> less )( ( h -> heapdata )[ ( k - 1 ) / 2] , ( h -> heapdata )[ k ] ) )
	{
		EXCH( ( h -> heapdata )[ k ] , ( h -> heapdata )[ ( k - 1 ) / 2 ] );
		k = ( k - 1 ) / 2;
	}

	return;
}

void FixDown( Heap * h , int k )
{
	int j;

	while( ( 2 * k + 1 ) < ( h -> n_elements ) )
	{
		j = 2 * k + 1;
		
		if( ( ( j + 1 ) < ( h -> n_elements ) ) && ( h -> less )( ( h -> heapdata )[ j ] , ( h -> heapdata )[ j + 1 ] ) )
			j++;
		
		if( !( h -> less )( ( h -> heapdata )[ k ] , ( h -> heapdata )[ j ] ) )
			break;
			
		EXCH( ( h -> heapdata )[ k ] , ( h -> heapdata )[ j ] );
		k = j;
	}

	return;
}

Heap * NewHeap( int size , int ( * less )( Item , Item ) , void ( * print )( Item ) )
{
	Heap * h;

	h = ( Heap * ) malloc( sizeof( Heap ) );
	if( h == ( ( Heap * ) NULL ) )
		makeException( ERROR_MEMORY_ALLOCATION );

	( h -> n_elements ) = 0;
	( h -> less ) = less;
	( h -> print ) = print;
	( h -> size ) = size;

	( h -> heapdata ) = ( Item * ) malloc( size * sizeof( Item ) );
	if( ( h -> heapdata ) == ( ( Item * ) NULL ) )
		makeException( ERROR_MEMORY_ALLOCATION );

	return h;
}

void FreeHeap( Heap * h )
{
	int i;
	
	for( i = 0 ; i < ( h -> n_elements ) ; i++ )
		free( ( h -> heapdata )[i] );
	
	free( h -> heapdata );
	free( h );
	
	return;
}

int Insert(Heap * h, Item element)
{
	if( ( h -> n_elements ) == h -> size )
	{
		printf( "Heap full (size = %d) !\n" , h -> size );
		return 0;
	}
	
	( h -> heapdata )[ h -> n_elements ] = element;

	h -> n_elements++;
	FixUp( h , h -> n_elements - 1 );

	return 1;
}

int Direct_Insert( Heap * h , Item element )
{
	if( ( h -> n_elements ) == h -> size )
	{
		printf( "Heap full (size = %d) !\n" , h -> size );
		return 0;
	}

	( h -> heapdata )[ h -> n_elements ] = element;

	h -> n_elements++;

	return 1;
}

void Modify( Heap * h , int index , Item newvalue )
{
	if( index > ( ( h -> n_elements ) - 1 ) )
	{
		printf( "Index out of range (index = %d) !\n" , index );
		return;
	}
	
	if( ( h -> less )( newvalue , ( h -> heapdata )[ index ] ) )
	{
		free( ( h -> heapdata )[ index ] ) ;
		( h -> heapdata )[ index ] = newvalue;
		FixDown( h , index );
	}
	else
	{
		free ( ( h -> heapdata )[ index ] );
		( h -> heapdata )[ index ] = newvalue;
		FixUp( h , index );
	}

	return;
}

Item RemoveMax( Heap * h )
{
	Item t;
	
	if( ( h -> n_elements ) > 0 )
	{
		t = ( h -> heapdata )[ 0 ];
		EXCH( ( h -> heapdata )[ 0 ] , ( h -> heapdata )[ ( h -> n_elements ) - 1 ] );
		( h -> n_elements )--;
		FixDown( h , 0 );
		return t;
	}

	return ( Item * ) NULL;
}

void CleanHeap( Heap * h )
{
	int i;
	
	for( i = 0 ; i < ( h -> n_elements ) ; i++ )
		free( ( h -> heapdata )[i] );
	
	h -> n_elements = 0;
	
	return;
}

int VerifyHeap( Heap * h )
{
	int i;
	
	for( i = ( ( h -> n_elements ) - 1 ) ; i > 0 ; i-- )
		if( ( h -> less )( ( h -> heapdata )[ ( i - 1 ) / 2 ] , ( h -> heapdata )[i] ) )
			return 0;
	
	return 1;
}

void HeapSort( Heap * h )
{
	int backup = h -> n_elements;
	Item aux;
	
	Heapify( h );
	
	while( h -> n_elements > 0 )
	{
		aux = ( h -> heapdata )[0];
		( h -> heapdata )[0] = ( h -> heapdata )[h -> n_elements - 1];
		( h -> heapdata )[h -> n_elements - 1] = aux;
		
		( h -> n_elements )--;
		
		FixDown( h , 0 );
	}
	
	( h -> n_elements ) = backup;
	
	return;
}

void Heapify( Heap * h )
{
	int i;
	
	for( i = ( ( ( h -> n_elements ) - 1 ) / 2 ) ; i >= 0 ; i-- )
		FixDown( h , i );
	
	return;
}

int isHeapEmpty( Heap * heap )
{
	return ( heap -> n_elements == 0 ) ? 1 : 0;
}
