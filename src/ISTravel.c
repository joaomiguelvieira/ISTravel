/**
 * @file ISTravel.c
 * @brief This file contains the main program of ISTravel. This project
 * 		is the final project of algorithms and data's structure project.
 * 
 * @author João Miguel Morgado Pereira Vieira, nº 79191, MEEC
 * @author Tomás Miguel Donga Cardoso, nº 79007, MEEC
 * 
 * @date December 5th, 2014
 * */

#include <stdlib.h>
#include <stdio.h>
#include "Defs.h"
#include "Utilities.h"
#include "Graph.h"

int main(int argc, char **argv) {
    /* Here goes the declaration of the variables. */
    char *map_filename = "\0";
    char *client_filename = "\0";
    char *output_filename = "\0";

    Graph *map;

    /* It has to be verified if the program was called with the correct
     * arguments. */
    if (argc < 3)
        usage(argv);

    /* The program will read the files' names and store them in the
     * correct strings. */
    while (*(++argv)) {
        if (equalExtentions((*argv), EXTENTION_CLIENT))
            client_filename = saveString((*argv));
        else if (equalExtentions((*argv), EXTENTION_MAP))
            map_filename = saveString((*argv));
        else
            makeException(ERROR_FILE_EXTENTION);
    }

    /* Storages the map from the file in the structure. */
    map = getMapFromFile(map_filename);

    /* This variable shall be freed as the program don't need it anymore. */
    free(map_filename);

    /* The program will create the output filename based on the client's
     * input filename removing the input extention and adding the output
     * extention to it. */
    output_filename = getOutputFileName(client_filename, EXTENTION_CLIENT, EXTENTION_OUTPUT);

    /* Now the map is already available. The program already have all
     * the needed information to start solving the main problem. */
    computeBestPath(map, client_filename, output_filename);

    /* Free all the allocated memory before exiting. */
    freeGraph(map);
    free(client_filename);
    free(output_filename);

    return 0;
}
