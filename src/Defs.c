/**
 * @file Defs.c
 * @brief This file contains the implementation of some general
 * 		functions that were used in other existing functions in this
 * 		project.
 * 
 * @author João Miguel Morgado Pereira Vieira, nº 79191, MEEC
 * @author Tomás Miguel Donga Cardoso, nº 79007, MEEC
 * 
 * @date December 5th, 2014
 * */

#include "Defs.h"

/**
 * @fn makeException
 * @brief Deals with errors. Kills the program with some specified
 * 		error's code.
 * @param int error_code
 * 		Code passed by parameter to function exit() at the end.
 * @return None.
 * */
void makeException(int error_code) {
    /* If the program is working in a real machine, it can produce
     * outputs, otherwise, in a simulation, for example, it leads with
     * the errors by just quitting the application with code 0. */
#ifdef REAL_MACHINE
    fprintf( stderr , "[ERROR] " );

    switch( error_code )
    {
        case ERROR_USAGE:
            fprintf( stderr , "Bad usage.\n" );
            break;
        case ERROR_FILE_MAN:
            fprintf( stderr , "File manipulation.\n" );
            break;
        case ERROR_FILE_EXTENTION:
            fprintf( stderr , "Different extention from expected.\n" );
            break;
        case ERROR_MEMORY_ALLOCATION:
            fprintf( stderr , "Could not allocate the required memory.\n" );
            break;
        case ERROR_UNINITIALIZED_STRUCTURE:
            fprintf( stderr , "You are attempting to manipulate structures that where not initialized yet.\n" );
            break;
        case ERROR_CAMP_NOT_EXPECTED:
            fprintf( stderr , "Was received a nonexpected camp while processing data. This may have to do with corrupted input data!\n" );
            break;
        case ERROR_FULL_MEMORY:
            fprintf( stderr , "A certain quantity of allocated memory was exceded. Don't know what to do.\n" );
            break;
        case ERROR_OUT_OF_RANGE:
            fprintf( stderr , "Attempting to access memory out of range.\n" );
            break;
        default:
            fprintf( stderr , "Unknown error.\n" );
    }

    exit( error_code );
#endif

    /* In case of outputs are not allowed. */
    exit(0);
}

/**
 * @fn getTransportationFromString
 * @brief This function receives one of four possible strings as
 * 		parameter and does nothing but convert it to a number in order
 * 		to its manipulation become more confortable.
 * @param char * transportation_s
 * 		String that contains the information about the transportation.
 * @return int
 * 		Code of the transportation passed by parameter.
 * */
int getTransportationFromString(char *transportation_s) {
    if (strcmp(transportation_s, "autocarro") == 0)
        return BUS;
    else if (strcmp(transportation_s, "aviao") == 0)
        return PLANE;
    else if (strcmp(transportation_s, "comboio") == 0)
        return TRAIN;
    else if (strcmp(transportation_s, "barco") == 0)
        return BOAT;
    else
        makeException(ERROR_CAMP_NOT_EXPECTED);

    return 0;
}

/**
 * @fn getRestriction
 * @brief This function receives a string as argument and discovers
 * 		what is the retsriction it reffers to.
 * @param char * restriction_s
 * 		String that contains the description of the restriction to
 * 		evaluate.
 * @return int
 * 		Code of the restriction passed by parameter.
 * */
int getRestriction(char *restriction_s) {
    if (strcmp(restriction_s, "A1") == 0)
        return A1;
    else if (strcmp(restriction_s, "A2") == 0)
        return A2;
    else if (strcmp(restriction_s, "A3") == 0)
        return A3;
    else if (strcmp(restriction_s, "B1") == 0)
        return B1;
    else if (strcmp(restriction_s, "B2") == 0)
        return B2;
    else
        return -1;
}

/**
 * @fn getOptimizationCriterium
 * @brief This function receives the criterium collected in the file
 * 		and codifies it in order to make easier its manipulation.
 * @param char * criterium
 * 		String that describes the chosen criterium.
 * @return int
 * 		Codification of the chosen criterium.
 * */
int getOptimizationCriterium(char *criterium) {
    if (strcmp(criterium, "tempo") == 0)
        return TIME;
    else if (strcmp(criterium, "custo") == 0)
        return COST;
    else
        makeException(ERROR_CAMP_NOT_EXPECTED);

    return 0;
}
