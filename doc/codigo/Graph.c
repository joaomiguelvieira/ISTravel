/**
 * @file Graph.c
 * @brief This file contains all the structures and methods for 
 * 		Graph's class. It also contains several algorithms in order to
 * 		manipulate and analyse graphs.
 * 
 * @author João Miguel Morgado Pereira Vieira, nº 79191, MEEC
 * @author Tomás Miguel Donga Cardoso, nº 79007, MEEC
 * 
 * @date December 5th, 2014
 * */

#include <stdlib.h>
#include "Graph.h"

/**
 * @struct Graph_
 * @brief This structure is the main structure of the graph it has just
 * 		three fields as we can see and they represent the quantity of
 * 		vertices numbered from 0 to N-1 in the graph, the number of
 * 		links connecting them and the description of this links.
 * */
struct Graph_
{
	int vertices;
	int bridges;
	LinkedList ** adjacencies;
};

/**
 * @struct Link_
 * @brief The structure link is coupled by the some list in the
 * 		adjacencies field of a graph. This structure has two general 
 * 		fields in it: an integer that points the vertice connected to
 * 		the one that this link refers and a field called weight which is
 * 		the ponderation of this bridge. This last type of data is unknown
 * 		by the graph and it doesn't know how to operate it (it must be
 * 		operated externaly of this class).
 * */
struct Link_
{
	int vertice;
	Item weight;
};

/* Pointer to the function that has the hability of freeing the weight
 * camps in camps of type Link. The fact that this is a static variable
 * causes that no matters how many graphs we have in our workspace: they
 * all have to admit the same type of link's weight. */
static void ( * freeWeight )( Item );

/**
 * @fn newLink
 * @brief Constructor for Link structures. It also sets its values.
 * @param int vertice
 * 		Vertice linked to the one this link will refers to.
 * @param Item weight
 * 		Ponderation of this link. Once more its structure is unknown at
 * 		this level.
 * @return Link *
 * 		Pointer to the new Link.
 * */
Link * newLink( int vertice , Item weight )
{
	Link * new;
	
	/* Allocating the necessary memory. */
	new = ( Link * ) malloc( sizeof( Link ) );
	if( new == ( Link * ) NULL )
		makeException( ERROR_MEMORY_ALLOCATION );
	
	/* Setting the values of the link. */
	( new -> vertice ) = vertice;
	( new -> weight ) = weight;
	
	return new;
}

/**
 * @fn graphInit
 * @brief Constructor for Graph structures. It also sets its values.
 * @param int vertices
 * 		Number of vertices in this graph.
 * @param int bridges
 * 		Number of links between the vertices (they are given right in
 * 		the beggining of this process but it doesn't have to be that way).
 * @param void ( * freeWeight_ )( Item )
 * 		Pointer to function which implements the method of freeing
 * 		structures of type weight in Links.
 * @return Graph *
 * 		Pointer to the new Graph.
 * */
Graph * graphInit( int vertices , int bridges , void ( * freeWeight_ )( Item ) )
{
	Graph * new;
	int i;
	
	/* Allocating the required memory. */
	new = ( Graph * ) malloc( sizeof( Graph ) );
	if( new == ( Graph * ) NULL )
		makeException( ERROR_MEMORY_ALLOCATION );
	
	/* Setting values of the new Graph. */
	( new -> vertices ) = vertices;
	( new -> bridges ) = bridges;
	freeWeight = freeWeight_;
	
	/* Initilising the vector of adjacencies' lists. */
	( new -> adjacencies ) = ( LinkedList ** ) malloc( vertices * sizeof( LinkedList * ) );
	if( ( new -> adjacencies ) == ( LinkedList ** ) NULL )
		makeException( ERROR_MEMORY_ALLOCATION );
	
	/* Initializing all the adjacencies' lists. */
	for( i = 0 ; i < vertices ; i++ )
		( new -> adjacencies )[i] = initList();
	
	return new;
}

/**
 * @fn graphLinkInsert
 * @brief This function inserts a bidirectional link between two
 * 		vertices in the graph.
 * @param Graph * graph
 * 		Graph where we want to make the connection.
 * @param int vertice1
 * 		First vertice involved in the connection.
 * @param int vertice2
 * 		Second vertice involved int the connection.
 * @param Item weight
 * 		Ponderance of the bridge. As the bridge is bidirectional this
 * 		field is common to both directions of the link.
 * @return None.
 * */
void graphLinkInsert( Graph * graph , int vertice1 , int vertice2 , Item weight )
{	
	/* Inserting the second vertice in adjacencies' list of the first... */
	( graph -> adjacencies )[vertice1] = insertUnsortedItemList( ( graph -> adjacencies )[vertice1] , 
		( Item ) newLink( vertice2 , weight ) );
	
	/* ... and the first in the adjacencies of the second. */
	( graph -> adjacencies )[vertice2] = insertUnsortedItemList( ( graph -> adjacencies )[vertice2] , 
		( Item ) newLink( vertice1 , weight ) );
	
	return;
}

/**
 * @fn freeGraph
 * @brief This function has the hability of freeing all the memory
 * 		involved in some graph by knowing the structurs it has to free
 * 		and, in case of not knowing their contents, some other functions
 * 		that are able of freeing them.
 * @param Graph *
 * 		Graph we want to erase.
 * @return None.
 * */
void freeGraph( Graph * graph )
{
	int i;
	LinkedList * aux;
	
	/* In first place we have to free all the adjacencies lists and the
	 * structures connected to them. */
	for( i = 0 ; i < ( graph -> vertices ) ; i++ )
	{	
		/* We have N vertices in the graph, so we have also N adjacencies'
		 * lists on it. */
		for( aux = ( graph -> adjacencies )[i] ; aux != ( LinkedList * ) NULL ; aux = getNextNodeList( aux ) )
			
			/* We shall not forget that all the links are bidirectional
			 * but they have the same weight, i. e., the memory
			 * of both weights are the same. One way of making sure that
			 * it is just freed once is freeing it just if the vertice
			 * is greater than the one it is connected to (it is the same
			 * of just freeing a half matrix). */
			if( ( ( ( Link * ) getItemNode( aux ) ) -> vertice ) < i )
				freeWeight( ( ( ( Link * ) getItemNode( aux ) ) -> weight ) );
		
		/* Now we are sure all the weights were successfuly freed, so the
		 * adjacencies list can be freed as the links inside of it. */
		freeList( ( graph -> adjacencies )[ i ] , free );
	}
	
	/* The only thing left to free inside the graph is the vector of
	 * adjacencies list. After freeing it we can finally free the graph. */
	free( graph -> adjacencies );
	free( graph );
	
	return;
}

/**
 * @def VERTICE
 * @brief This macro refers to the vertice on some link that is stored
 * 		in a list.
 * */
#define VERTICE( A ) ( ( ( Link * ) getItemNode( A ) ) -> vertice )

/**
 * @def WEIGHT
 * @brief This macro refers to the ponderation of some bridge.
 * */
#define WEIGHT( A , B ) weigh( weights[ A ] , B -> weight , &bridge )

/**
 * @fn dijkstra
 * @brief The famous dijkstra's algorithm is one of the most popular
 * 		strategies in graph's theory to calculate, in some graph, the
 * 		best path from some vertice to all the others. This implementation
 * 		is a variant from the original one. In this function an addictional
 * 		vector of bridges is defined for foreign use. It also returns the
 * 		costs' vector calculated by dijkstra algorithm and the whole
 * 		method uses heaps in order to make the process faster.
 * */
void dijkstra( Graph * graph , int origin , int * shortest_path_tree ,
	Item * bridges , int ( * weigh )( int , Item , Item * ) , int * weights ,
	Heap * priority_queue )
{
	int v , i , efective_weight;
	LinkedList * aux;
	Item bridge;
	
	for( i = 0 ; i < ( graph -> vertices ) ; i++ )
	{
		/* As any path was not stablished yet, the vector of positions shall
		 * be initialized with -1 flag, the bidges vector shell be set
		 * NULL and the distance from the origin to all vertices is now
		 * infinity. */
		shortest_path_tree[i] = -1;
		bridges[i] = ( Item ) NULL;
		weights[i] = INT_MAX;
		
		/* We perform a simple insertion of the vertices in the graph as
		 * they all have the same weight now (infinity). */
		if( !directInsert( priority_queue , i ) )
			makeException( ERROR_UNKNOWN );
	}
	
	/* The distance of the origin to itself is, by definition, zero, so
	 * we set it so. */
	weights[origin] = 0;
	
	/* Now the priority of the origin's vertice is greater than all the
	 * others, so it shall be updated on the graph. */
	incPriority( priority_queue , origin );
	
	/* While the heap is not empty, there is vertices we have not analysed yet. */
	while( !isHeapEmpty( priority_queue ) )	
	
		/* If the distance of the vertice that is closer to the graph is
		 * minor than infinity... */
		if( weights[ v = removeMax( priority_queue ) ] != INT_MAX )
		{
			/* ... we check all its adjacencies... */
			for( aux = ( graph -> adjacencies )[ v ] ; aux != ( LinkedList * ) NULL ; aux = getNextNodeList( aux ) )
				
				/* ... and in its adjacencies, if we find some bridge that
				 * minimizes the distance of some other vertice in the
				 * graph... */
				if( ( ( efective_weight = WEIGHT( v , ( ( Link * ) getItemNode( aux ) ) ) ) != INT_MAX ) && 
					( weights[ i = ( VERTICE( aux ) ) ] > weights[ v ] + efective_weight ) )
				{	
					/* ... that connection replaces the previous one if
					 * it exists... */
					bridges[i] = bridge;
					weights[i] = weights[ v ] + efective_weight;
					
					/* ... and the vertice which is now closer to the
					 * shortest path tree has now a greater condition,
					 * which means that it has to be fixed on the heap. */
					incPriority( priority_queue , i );
					shortest_path_tree[i] = v;
				}
		}
		else
		{	
			/* If we extract some element from the heap that has infinite
			 * weight we shall know that is nothing more to look at because
			 * all the remaining vertices have no conection with the source. */
			cleanHeap( priority_queue );
			
			break;
		}
	
	/* A vector of weights found while the algorithm was running is returned
	 * for foreign use. */
	return;
}

/**
 * @fn printGraph
 * @brief This function prints on the screen the list of adjacencies of
 * 		each vertice, however it does not print the weights.
 * @param Graph * graph
 * 		Graph we want to print.
 * @return None.
 * */
void printGraph( Graph * graph )
{
	#ifdef REAL_MACHINE
		int i;
		LinkedList * aux;
		
		for( i = 0 ; i < graph -> vertices ; i++ )
		{
			printf( "[%d]: " , i );
			
			for( aux = ( graph -> adjacencies )[i] ; aux != ( LinkedList * ) NULL ; aux = getNextNodeList( aux ) )
				printf( "%d " , ( ( Link * ) getItemNode( aux ) ) -> vertice );
			
			printf( "\n" );
		}
	#endif
	
	return;
}

/**
 * @fn getNumberOfVertices
 * @brief This function is a getter for the number of vertices of some
 * 		graph.
 * @param Graph * graph
 * 		Graph we want to count the vertices.
 * @return int
 * 		Number of vertices in the graph passed by parameter.
 * */
int getNumberOfVertices( Graph * graph )
{
	return ( graph -> vertices );
}

/**
 * @fn getVertice
 * @brief Getter for the field vertice of some link.
 * @param Link * link
 * 		Link that we are interested to analyse.
 * @return int
 * 		Vertice which the link refers to.
 * */
int getVertice( Link * link )
{
	return ( link -> vertice );
}

/**
 * @fn getWeight
 * @brief This is a getter for the field weight of some link.
 * @param Link * link
 * 		Link we are interested of knowing the weight.
 * @return Item
 * 		Pointer to the structure that represents the weight of this
 * 		link.
 * */
Item getWeight( Link * link )
{
	return ( link -> weight );
}

/**
 * @fn getAdjacencies
 * @brief This function returns the adjacencies' list of some vertice.
 * @param Graph * graph
 * 		Graph where are the vertices we want to know its adjacencies.
 * @param int vertice
 * 		Vertice we want to know the adjacencies of.
 * @return LinkedList *
 * 		List of adjacencies.
 * */
LinkedList * getAdjacencies( Graph * graph , int vertice )
{
	return ( graph -> adjacencies )[vertice];
}
