/**
 * @file Utilities.c
 * @brief This file contains the implementation of the interface 
 * 		"Utilities". This interface in nothing else than some general
 * 		operations executed in the main program that are descripted here
 * 		in order to organize the code.
 * 
 * @author João Miguel Morgado Pereira Vieira, nº 79191, MEEC
 * @author Tomás Miguel Donga Cardoso, nº 79007, MEEC
 * 
 * @date December 5th, 2014
 * */

#include "Utilities.h"

/**
 * @fn usage
 * @brief Remembers user how to call correctly the program. It is only
 * 		called when something went wrong calling the application (the 
 * 		arguments inserted are not enought or not valid).
 * @param char ** argv
 * 		List of arguments when the program was called.
 * @return None.
 * */
void usage(char **argv) {
    fprintf(stderr, "[USAGE]: %s <map_file>.map <client_file>.cli\n", argv[0]);

    makeException(ERROR_USAGE);
}

/**
 * @fn equalExtentions
 * @brief The function equalExtentions verifies if some string have a
 * 		specific extention passed through parameter.
 * @param char * string
 * 		
 * */
int equalExtentions(char *string, char *extention) {
    return (strcmp((string + (strlen(string) - strlen(extention))), extention) == 0) ? 1 : 0;
}

/**
 * @fn saveString
 * @brief This function has the hability of allocating just the necessary
 * 		memory for storage a string passed by parameter and saves it.
 * @param char * string
 * 		String we want to save.
 * @return char *
 * 		Pointer to the saved string.
 * */
char *saveString(char *string) {
    char *saved_string;

    saved_string = (char *) malloc((strlen(string) + 1) * sizeof(char));
    if (saved_string == (char *) NULL)
        makeException(ERROR_MEMORY_ALLOCATION);

    strcpy(saved_string, string);

    return saved_string;
}

/**
 * @fn getOutputFileName
 * @brief This function computes the output file name by removing the
 * 		extention of the input file name and adding the output extention.
 * @param char * input_filename
 * 		Name of the input file. The output file name will be based on it.
 * @param char * input_file_extention
 * 		Extention to remove.
 * @param char * output_file_extention
 * 		Extention to add.
 * @return char *
 * 		Pointer to the output file name.
 * */
char *getOutputFileName(char *input_filename, char *input_file_extention, char *output_file_extention) {
    char *output_filename;
    char aux[LINEWIDTH];

    /* Allocating the required memory for output file name. */
    output_filename = (char *) malloc((strlen(input_filename) -
                                       strlen(input_file_extention) + strlen(output_file_extention) + 1) *
                                      sizeof(char));
    if (output_filename == (char *) NULL)
        makeException(ERROR_MEMORY_ALLOCATION);

    /* Copying the input file name for manipulation. */
    strcpy(aux, input_filename);

    /* Removing the input extention. */
    aux[strlen(input_filename) - strlen(input_file_extention)] = '\0';

    /* Copying the file name to its final position and adding the output
     * extention. */
    strcpy(output_filename, aux);
    strcat(output_filename, output_file_extention);

    return output_filename;
}

/**
 * @fn getMapFromFile
 * @brief This function reads a file that admits a certain structure and
 * 		builds the graph codifyed on it.
 * @param char * map_filename
 * 		Name of the file containing the graph.
 * @return Graph *
 * 		Pointer to the graph built by this function.
 * */
Graph *getMapFromFile(char *map_filename) {
    FILE *file_map;

    char line[LINEWIDTH];

    Graph *map;

    int i;

    int vertices;
    int bridges;
    int city1;
    int city2;
    Bridge *weight;
    char transportation_s[LINEWIDTH];
    int transportation;
    int time;
    int cost;
    int first_travel;
    int no_more_travels;
    int period;

    LinkedList *aux;

    /* Opening the source. */
    file_map = fopen(map_filename, "r");
    if (file_map == (FILE *) NULL)
        makeException(ERROR_FILE_MAN);

    /* Before anything the file provides a line containing the number of
     * vertices and the number of links that the program will read. */
    if ((fgets(line, LINEWIDTH, file_map) == NULL) ||
        sscanf(line, "%d %d", &vertices, &bridges) != 2)
        makeException(ERROR_CAMP_NOT_EXPECTED);

    /* We are ready to build the graph. */
    map = graphInit(vertices, bridges, freeWeight);

    /* The file starts to be processed and the specifications of each bridge
     * will be now read. */
    for (i = bridges; i > 0; i--) {
        /* Obtaining the lecture of a line. */
        if ((fgets(line, LINEWIDTH, file_map) == NULL) ||
            sscanf(line, "%d %d %s %d %d %d %d %d", &city1, &city2,
                   transportation_s, &time, &cost, &first_travel, &no_more_travels, &period) != 8)
            makeException(ERROR_CAMP_NOT_EXPECTED);

        /* The cities are numbered from 1 to N, however in C arrays go from
         * index 0, so we have to decrement the number of the cities and
         * increment them again before producing the output. */
        city1--;
        city2--;

        /* Codifying the transportation in an integer. */
        transportation = getTransportationFromString(transportation_s);

        /* Building the structure that will storage the information of
         * bridge's weight. */
        weight = newBridge(transportation, time, cost, first_travel, no_more_travels, period);

        /* If the bridge already exists, we have only to add this weight... */
        for (aux = getAdjacencies(map, city1); aux != (LinkedList *) NULL; aux = getNextNodeList(aux))
            if (getVertice((Link *) getItemNode(aux)) == city2) {
                insertWithNoReturn(((LinkedList *) getWeight((Link *) getItemNode(aux))), (Item) weight);
                break;
            }

        /* If it don't exist we insert it. */
        if (aux == (LinkedList *) NULL) {
            aux = initList();
            aux = insertUnsortedItemList(aux, weight);
            graphLinkInsert(map, city1, city2, aux);
        }
    }

    /* The program already read the file and loaded the map to the
     * system. We are ready to close the file. */
    fclose(file_map);

    printGraph(map);

    return map;
}

/**
 * @var int optimization, int ready_from, int restrictions_A[3],
 * 		int restrictions_B[2]
 * @brief This variables are declared as static and contain, respectively:
 * 		the optimization criterium of the processing client; the moment
 * 		in which client is ready to leave; values of restrictions of type
 * 		A; values of the restrictions of type B. If the restrictions do
 * 		not exist, the respective field contains INT_MAX (infinity).
 * 		The decision of making this variables static was based in the fact
 * 		that several functions use them, and it's easier declare them
 * 		static than pass them to the all functions that need them.
 * */
static int optimization = 0;
static int ready_from;
static int restrictions_A[3];
static int restrictions_B[2];

/**
 * @fn computeBestPath
 * @brief This function is maybe the most important of the program. It
 * 		implements the solution of the problem (finding the best path)
 * 		using other functions in order to do it.
 * @param Graph * map
 * 		Map that describes all the connections between the cities.
 * @param char * client_filename
 * 		Name of the file that contains the clients' whished paths.
 * @param char * output_filename
 * 		Name of the file that will storage the solution for this problem.
 * @return None.
 * */
void computeBestPath(Graph *map, char *client_filename, char *output_filename) {
    FILE *client_file;
    FILE *output_file;

    /* Here goes the declaration of the variables used in this function.
     * They are a lot but at this level it is worthless try to organize
     * it as we just use this fields like auxiliars. */
    char line[LINEWIDTH];
    int n_clients;
    int client;
    int origin;
    int destination;
    int n_restriction;
    char optimization_string[LINEWIDTH];
    char restriction_1_string[LINEWIDTH];
    char v_restriction_1_string[LINEWIDTH];
    char restriction_2_string[LINEWIDTH];
    char v_restriction_2_string[LINEWIDTH];

    int *shortest_path_tree;
    Bridge **bridges;
    Heap *priority_queue;
    int *weights;

    /* The vector of weights must be allocated... */
    weights = (int *) malloc(getNumberOfVertices(map) * sizeof(int));
    if (weights == (int *) NULL)
        makeException(ERROR_MEMORY_ALLOCATION);

    priority_queue = newHeap(getNumberOfVertices(map), weights);

    /* Allocating the required memory for the shortest path tree. This is
     * a vector of integers that will contain for each index (city) the
     * vertice it is connected to in the shortest path tree. */
    shortest_path_tree = (int *) malloc(getNumberOfVertices(map) * sizeof(int));
    if (shortest_path_tree == (int *) NULL)
        makeException(ERROR_MEMORY_ALLOCATION);

    /* Vector of structures of type bridges. This vector is returned by
     * dijkstra and will be useful when we have to find the complementar
     * weight of the path since we have to specify not only the criterium
     * weight but also the other. */
    bridges = (Bridge **) malloc(getNumberOfVertices(map) * sizeof(Bridge *));
    if (bridges == (Bridge **) NULL)
        makeException(ERROR_MEMORY_ALLOCATION);

    /* Opening the source. */
    client_file = fopen(client_filename, "r");
    if (client_file == (FILE *) NULL)
        makeException(ERROR_FILE_MAN);

    /* Opening the destination file. */
    output_file = fopen(output_filename, "w");
    if (output_file == (FILE *) NULL)
        makeException(ERROR_FILE_MAN);

    /* In first place the  */
    if ((fgets(line, LINEWIDTH, client_file) == NULL) ||
        (sscanf(line, "%d", &n_clients) != 1))
        makeException(ERROR_CAMP_NOT_EXPECTED);

    for (; n_clients > 0; n_clients--) {
        /* Acquiring the information for the processing client. */
        if ((fgets(line, LINEWIDTH, client_file) == NULL) ||
            (sscanf(line, "%d %d %d %d %s %d %s %s %s %s",
                    &client, &origin, &destination, &ready_from,
                    optimization_string, &n_restriction, restriction_1_string,
                    v_restriction_1_string, restriction_2_string,
                    v_restriction_2_string) != (6 + n_restriction * 2)))
            makeException(ERROR_CAMP_NOT_EXPECTED);

        /* The same story as before: When we are programing in C the arrays
         * are numbered from 0, so we have to decrement the number codifying
         * the city. */
        origin--;
        destination--;

        /* Codifying the optimization criterium in a integer. */
        optimization = getOptimizationCriterium(optimization_string);

        /* Initializing all the restrictions with infinity. */
        restrictions_A[0] = restrictions_A[1] = restrictions_A[2] = INT_MAX;
        restrictions_B[0] = restrictions_B[1] = INT_MAX;

        /* We have to find out the restrictions proposed by this client. */
        switch (n_restriction) {
            case 2:
                defineRestriction(restriction_2_string, v_restriction_2_string);
            case 1:
                defineRestriction(restriction_1_string, v_restriction_1_string);
                break;
            default:;
        }

        /* Just a conditional block to follow the program if we need to
         * see the progress or confirm some results. */
#ifdef PROGRESSION
        switch( optimization )
        {
            case TIME:
                printf( "TIME: " );
                break;
            case COST:
                printf( "COST: " );
            default:
                ;
        }

        printf( "Solving client %d (%d <---> %d)\n" , client , ( origin + 1 ) , ( destination + 1 ) );
#endif

        /* Finally! Solving this client problem. The returned vector of
         * weights contains all the path's weights between the origin
         * and the vertices. We will need the destination's weight to
         * export it. */
        dijkstra(map, origin, shortest_path_tree, (Item *) bridges, weigh, weights, priority_queue);

        fprintf(output_file, "%d ", client);

        /* If there is no path to this client or the best path do not follow
         * the restriction of type B imposed by the client ther is no
         * path to be shown. */
        if (shortest_path_tree[destination] == -1 || !followRestrictionsB(weights[destination]))
            fprintf(output_file, "-1");
        else {
            printPath(output_file, shortest_path_tree, bridges, destination, origin);

            switch (optimization) {
                /* Dijkstra's algorithm calculated the weight following
                 * the client criterium, but now it also has to calculate
                 * the weight following the other criterium. */
                case TIME:
                    fprintf(output_file, "%d ", weights[destination]);
                    fprintf(output_file, "%d ", getTotalPrice(shortest_path_tree, bridges, origin, destination));
                    break;
                case COST:
                    fprintf(output_file, "%d ", getTotalTime(shortest_path_tree, bridges, origin, destination));
                    fprintf(output_file, "%d ", weights[destination]);
                    break;
                default:
                    makeException(ERROR_CAMP_NOT_EXPECTED);
            }
        }

        fprintf(output_file, "\n");
    }

    /* In the end of solving problem we can finally free the used memory. */
    free(weights);
    freeHeap(priority_queue);
    free(shortest_path_tree);
    free(bridges);
    fclose(client_file);
    fclose(output_file);

    return;
}

/**
 * @fn freeWeight
 * @brief This function is the destroyer of structures in weight fields
 * 		storaged in the graph.
 * @param Item weight
 * 		Non casted pointer for the weight to free.
 * @return None.
 * */
void freeWeight(Item weight) {
    /* Freeing the list of weights and its containing. */
    freeList((LinkedList *) weight, freeBridge);

    return;
}

/**
 * @fn defineRestriction
 * @brief This function just switches the string restriction to find
 * 		out which restriction we are working on and then it sets the
 * 		value of the restriction found.
 * @param char * restriction
 * 		String that describes the restriction we are working with.
 * @param char * value
 * 		Value of the restriction.
 * @return None.
 * */
void defineRestriction(char *restriction, char *value) {
    switch (getRestriction(restriction)) {
        case A1:
            restrictions_A[0] = getTransportationFromString(value);
            break;
        case A2:
            restrictions_A[1] = atoi(value);
            break;
        case A3:
            restrictions_A[2] = atoi(value);
            break;
        case B1:
            restrictions_B[0] = atoi(value);
            break;
        case B2:
            restrictions_B[1] = atoi(value);
            break;
        default:
            makeException(ERROR_CAMP_NOT_EXPECTED);
    }

    return;
}

/**
 * @fn getTotalPrice
 * @brief This function receives as parameter the shortest path tree, the
 * 		weights between the linked vertices and the origin and destenation
 * 		cities and manipulate its weights in order to compute the all cost
 * 		associated to the path between the origin and the destination.
 * @param int * shortest_path_tree
 * 		Vector of integers containing the shortest path tree generated
 * 		with dijkstra's algorithm.
 * @param Bridge ** bridges
 * 		Table of bridges that contains the respective weights of the
 * 		shortest path tree connections.
 * @param int origin
 * 		City of origin.
 * @param int destination
 * 		City of destination.
 * @return int
 * 		Total cost of the trip.
 * */
int getTotalPrice(int *shortest_path_tree, Bridge **bridges, int origin, int destination) {
    int i, total_price = 0;

    /* Sums all the prices associated with the single trips. */
    for (i = destination; i != origin; i = shortest_path_tree[i])
        total_price += getPrice(bridges[i]);

    return total_price;
}

/**
 * @fn getTotalTime
 * @brief This function receives as parameter the shortest path tree, the
 * 		weights between the linked vertices and the origin and destenation
 * 		cities and manipulate its weights in order to compute the total time
 * 		associated to the path between the origin and the destination.
 * @param int * shortest_path_tree
 * 		Vector of integers containing the shortest path tree generated
 * 		with dijkstra's algorithm.
 * @param Bridge ** bridges
 * 		Table of bridges that contains the respective weights of the
 * 		shortest path tree connections.
 * @param int origin
 * 		City of origin.
 * @param int destination
 * 		City of destination.
 * @return int
 * 		Total time of the trip.
 * */
int getTotalTime(int *shortest_path_tree, Bridge **bridges, int origin, int destination) {
    int total_time;

    /* If the origin city is the destenation it takes time 0 to achieve it. */
    if (origin == destination)
        return 0;

    /* The calculation of the total time is not linear as the cost. It
     * has to consider the time the client arrived to the city, so it
     * must be done strictly from the origin to the end and we only have
     * explicit the way back. So it suggests a recursive function that
     * progrides to the origin and when finds it starts calculating
     * the time it take to achive the next city and so on until it returns
     * to the desteny (where it begins). */
    total_time = getTotalTime(shortest_path_tree, bridges, origin, shortest_path_tree[destination]);

    /* Returns the acomulated time and the time associated to this new bridge. */
    return getTime(total_time % DAY_TIME, bridges[destination]) + total_time;
}

/**
 * @fn weigh
 * @brief This function weighs a bridge and it is sensible to the actual
 * 		criterium. It is used by dijkstra to calculate the weight between
 * 		two vertices.
 * @param int counter
 * 		Weight until this vertice.
 * @param Item bridge
 * 		Bridge to weight.
 * @param Item * efective_weight
 * 		Pointer that will be set by this function and it will points
 * 		the bridge followed in this way.
 * */
int weigh(int counter, Item bridge, Item *efective_weight) {
    int weight = INT_MAX;
    int i;
    LinkedList *aux;

    /* Switches the otimization in order to know the weight it has to
     * calculate. */
    switch (optimization) {
        case TIME:
            /* Between the possible ways between this two vertices, it is
             * chosen the best one and its weight is calculated. */
            for (aux = (LinkedList *) bridge; aux != (LinkedList *) NULL; aux = getNextNodeList(aux))
                if (((i = getTime(counter, (Bridge *) getItemNode(aux))) < weight) &&
                    followRestrictionsA((Bridge *) getItemNode(aux))) {
                    weight = i;
                    (*efective_weight) = (Item) getItemNode(aux);
                }

            break;
        case COST:
            /* The same than the previous comment. */
            for (aux = (LinkedList *) bridge; aux != (LinkedList *) NULL; aux = getNextNodeList(aux))
                if (((i = getPrice((Bridge *) getItemNode(aux))) < weight) &&
                    followRestrictionsA((Bridge *) getItemNode(aux))) {
                    weight = i;
                    (*efective_weight) = (Item) getItemNode(aux);
                }

            break;
        default:
            makeException(ERROR_UNKNOWN);
    }

    return weight;
}

/**
 * @fn followRestrictionsA
 * @brief This function looks at the weight of some link between two
 * 		vertices and decides if it follows the defined restrictions of
 * 		type A.
 * @param Bridge * bridge
 * 		Bridge we want to evaluate.
 * @return int
 * 		1 if the bridge follows the restrictions or 0 otherwise.
 * */
int followRestrictionsA(Bridge *bridge) {
    if ((getTransportation(bridge) != restrictions_A[0]) &&
        (getDuration(bridge) <= restrictions_A[1]) &&
        (getPrice(bridge) <= restrictions_A[2]))
        return 1;
    else
        return 0;
}

/**
 * @fn followRestrictionsB
 * @brief This function looks at the weight of some link between two
 * 		vertices and decides if it follows the defined restrictions of
 * 		type B.
 * @param int weight
 * 		Weight of the final path. The optimization criterium will decide
 * 		if it respects to time or cost.
 * @return int
 * 		1 if the bridge follows the restrictions or 0 otherwise.
 * */
int followRestrictionsB(int weight) {
    switch (optimization) {
        case TIME:
            return (weight <= restrictions_B[0]) ? 1 : 0;
        case COST:
            return (weight <= restrictions_B[1]) ? 1 : 0;
        default:
            makeException(ERROR_CAMP_NOT_EXPECTED);
    }

    return 0;
}

/**
 * @fn getTime
 * @brief This function calculates the time spent in one connection since
 * 		the moment the client arrived to some city.
 * @param int counter
 * 		Time spent until now.
 * @param Bridge * bridge
 * 		Connection we want to evaluate.
 * @return int
 * 		Time spent in this connection.
 * */
int getTime(int counter, Bridge *bridge) {
    int total_time;
    int wait = 0;
    int clock_time, i;

    /* The variable total time contains the time passed since the 0 hours
     * of the day the client left the origin city. */
    total_time = ready_from + counter;

    /* The variable clock_time indicates the time line of the day. */
    clock_time = total_time % DAY_TIME;

    do {
        /* If the client arrives to the city after the last transportation
         * left he has to wait at least to the midnight. */
        if (clock_time > getNoMoreTravels(bridge)) {
            wait += (DAY_TIME - clock_time);
            clock_time = 0;
        }

        /* If it is to early, the client has to wait for the first
         * transportation. */
        if (clock_time < getFirstTravel(bridge)) {
            wait += getFirstTravel(bridge) - clock_time;
            clock_time = getFirstTravel(bridge);
        }

        /* If the client arrives in the useful period we have to find
         * out the next travel... */
        for (i = getFirstTravel(bridge); i < clock_time; i += getPeriod(bridge));

        /* But it can hapen that the next travel occurs out of the useful
         * period, and then the client has to wait to the next day. */
        wait += (i <= DAY_TIME) ? (i - clock_time) : (DAY_TIME - clock_time);
        clock_time = (i <= DAY_TIME) ? i : 0;
    } while (clock_time > getNoMoreTravels(bridge) || clock_time < getFirstTravel(bridge));

    /* In pratical terms, the time spent on this travel is the time that
     * client had to wait and the duration of it. */
    return (wait + getDuration(bridge));
}

/**
 * @fn printPath
 * @brief This function prints in the file the path obtained for the
 * 		client.
 * @param FILE * output_file
 * 		Destination file.
 * @param int * shortest_path_tree
 * 		Vector with the shortest path tree for this origin.
 * @param Bridges ** bridges
 * 		Weights of the connections described in the shortest path tree.
 * @param int destination
 * 		Destination city.
 * @param int origin
 * 		Origin city.
 * @return None.
 * */
void printPath(FILE *output_file, int *shortest_path_tree, Bridge **bridges, int destination, int origin) {
    /* Once more we want to walk from origin to the end, but the information
     * we have leads us from destination to the beginning. So it seems
     * that another recursive function is needed!. */
    if (destination == origin) {
        fprintf(output_file, "%d ", (origin + 1));
        return;
    } else
        printPath(output_file, shortest_path_tree, bridges, shortest_path_tree[destination], origin);

    /* Switches the type of transportation and prints the right string
     * in the output file. */
    switch (getTransportation(bridges[destination])) {
        case PLANE:
            fprintf(output_file, "aviao ");
            break;
        case BOAT:
            fprintf(output_file, "barco ");
            break;
        case TRAIN:
            fprintf(output_file, "comboio ");
            break;
        case BUS:
            fprintf(output_file, "autocarro ");
            break;
        default:
            makeException(ERROR_CAMP_NOT_EXPECTED);
    }

    /* Finally it prints the current city in the file. */
    fprintf(output_file, "%d ", (destination + 1));

    return;
}
