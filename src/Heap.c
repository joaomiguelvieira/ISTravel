/**
 * @file Heap.c
 * @brief This file contains the implementation of Heap's class. It
 * 		contains the structure's declaration, their methods and some other
 * 		functions based on them.
 * 
 * @author João Miguel Morgado Pereira Vieira, nº 79191, MEEC
 * @author Tomás Miguel Donga Cardoso, nº 79007, MEEC
 * 
 * @date December 5th, 2014
 * */

#include "Heap.h"

/* As we can see this heap is built strictly for integers type. This
 * option was taken based on the nature of manipulating data. The type
 * of elements in this heap will be very peculiar: they are integers, 
 * all greater than zero, there are no repeated elements on the heap and
 * the greatest element that can be on the heap is equal to the major
 * index of it. It becomes clear that we can easily storadge the 
 * positions of the elements on the heap and then we can manipulate them
 * easier. */

/**
 * @struct Heap_
 * @brief Structure that storadges all the information of an heap.
 * */
struct Heap_ {
    int *priority;        /* Table of integers containing the weights of the elements. */
    int *heapdata;        /* Elements of the heap. */
    int *positions;    /* Positions of the elements contained in the heap. */
    int n_elements;        /* Actual number of elements in the heap. */
    int size;            /* Maximum capacity of the heap. */
};

/**
 * @fn fixUp
 * @brief Fixes the position of some element in the heap up.
 * @param Heap * h
 * 		Heap we want to fix.
 * @param int k
 * 		Element we think that has to be moved.
 * @return None.
 * */
void fixUp(Heap *h, int k) {
    /* While we haven't reached the top of the heap and the father is
     * weaker than his soon... */
    while ((k > 0) && LESS((h->heapdata)[(k - 1) / 2], (h->heapdata)[k])) {
        /* ... exchange the father and the soon in the heap... */
        EXCH((h->heapdata)[k], (h->heapdata)[(k - 1) / 2]);

        /* ... exchange its positions in position table... */
        EXCH((h->positions)[(h->heapdata)[k]], (h->positions)[(h->heapdata)[(k - 1) / 2]]);

        /* ... and do the same procedure now for the grandfather and so on. */
        k = (k - 1) / 2;
    }

    return;
}

/**
 * @fn fixDown
 * @brief This function do the same thing than fixUp but insted of
 * 		fixing the heap up it fixes it down, comparing the actual element
 * 		with its children.
 * @param Heap * h
 * 		Heap we want to fix.
 * @param int k
 * 		Element we suspect that has to be moved.
 * @return None.
 * */
void fixDown(Heap *h, int k) {
    int j;

    /* While we do not reach the end of the heap... */
    while ((2 * k + 1) < (h->n_elements)) {
        /* ... find the first son of k. */
        j = 2 * k + 1;

        /* If the second son is greater we must consider it instead the
         * first son. */
        if (((j + 1) < (h->n_elements)) && LESS((h->heapdata)[j], (h->heapdata)[j + 1]))
            j++;

        /* The heap's condition is established again if the father is
         * greater than the son... */
        if (!LESS((h->heapdata)[k], (h->heapdata)[j]))
            break;

        /* ... otherwise we have to keep exchanging it until we
         * establish the heap's condition again. */
        EXCH((h->heapdata)[k], (h->heapdata)[j]);
        EXCH((h->positions)[(h->heapdata)[k]], (h->positions)[(h->heapdata)[j]]);

        k = j;
    }

    return;
}

/**
 * @fn newHeap
 * @brief Constructor for structures of type Heap.
 * @param int size
 * 		Maximum size we wish for this heap.
 * @param int * priority
 * 		Pointer to a integers table that represents the priority in the
 * 		queue. This memory shall be changed outside the funcions of this
 * 		class.
 * @return Heap *
 * 		Pointer to the new Heap.
 * */
Heap *newHeap(int size, int *priority) {
    Heap *h;

    /* Allocating the memory for this heap. */
    h = (Heap *) malloc(sizeof(Heap));
    if (h == ((Heap *) NULL))
        makeException(ERROR_MEMORY_ALLOCATION);

    /* Setting the general properties of the heap. */
    (h->n_elements) = 0;
    (h->priority) = priority;
    (h->size) = size;

    /* Initializing the heap's data with the size passed by parameter. */
    (h->heapdata) = (int *) malloc(size * sizeof(int));
    if ((h->heapdata) == ((int *) NULL))
        makeException(ERROR_MEMORY_ALLOCATION);

    /* Initializing the vector of positions the same size as the heap's
     * data. */
    (h->positions) = (int *) malloc(size * sizeof(int));
    if ((h->positions) == ((int *) NULL))
        makeException(ERROR_MEMORY_ALLOCATION);

    return h;
}

/**
 * @fn freeHeap
 * @brief This function is responsable for free the entire heap. As the
 * 		heap's structure contains pointers for dinamicaly allocated
 * 		memory, it shall be freed before free the pointer for the heap.
 * @param Heap * h
 * 		Heap we want to free.
 * @return None.
 * */
void freeHeap(Heap *h) {
    free(h->heapdata);
    free(h->positions);
    free(h);

    return;
}

/**
 * @fn insert
 * @brief This function inserts a new element in the heap and puts it
 * 		in its right position based on comparison criteria.
 * @param Heap * h
 * 		Heap where we want to insert a new element.
 * @param int element
 * 		Element we want to insert in the heap.
 * @return int
 * 		0 if the insertion was not succeded and 1 if it was.
 * */
int insert(Heap *h, int element) {
    /* If the heap is already full we do not dispose of any space further
     * to continue storaging elements in this heap. */
    if ((h->n_elements) == h->size) {
#ifdef REAL_MACHINE
        printf( "Heap full (size = %d) !\n" , h -> size );
#endif
        return 0;
    }

    /* Putting the new element in the end of the end of the heap and
     * declarating its actual position. */
    (h->heapdata)[h->n_elements] = element;
    (h->positions)[element] = (h->n_elements);

    (h->n_elements)++;

    /* Correcting the order of the heap. */
    fixUp(h, h->n_elements - 1);

    return 1;
}

/**
 * @fn directInsert
 * @brief This function is similar to the function insert. The only
 * 		difference between this function and the previous is that this
 * 		one do not fix the order of the heap, just inserts the element
 * 		in the last position of it.
 * @param Heap * h
 * 		Heap in which we want to insert a new element.
 * @param int element
 * 		Element we want to insert (it must be different from all the
 * 		others elements existing in the heap already).
 * @return int
 * 		Returns 1 in case of success and 0 otherwise.
 * */
int directInsert(Heap *h, int element) {
    /* If the heap is already full we cannot keep inserting elements on
     * it. */
    if ((h->n_elements) == h->size) {
#ifdef REAL_MACHINE
        printf( "Heap full (size = %d) !\n" , h -> size );
#endif
        return 0;
    }

    /* Inserting the new element in the heap and declaring its position. */
    (h->heapdata)[h->n_elements] = element;
    (h->positions)[element] = (h->n_elements);

    h->n_elements++;

    return 1;
}

/**
 * @fn removeMax
 * @brief This function removes the element with the greatest priority
 * 		in the heap, fixes the heap, and returns the removed element.
 * @param Heap * h
 * 		Heap which we want the remove the greatest element.
 * @return int
 * 		Grestest element of the heap.
 * */
int removeMax(Heap *h) {
    int aux;

    /* If the heap is not empty... */
    if ((h->n_elements) > 0) {
        aux = (h->heapdata)[0];

        /* ... exchange first and last elements and its positions... */
        EXCH((h->positions)[(h->heapdata)[0]], (h->positions)[(h->heapdata)[(h->n_elements) - 1]]);
        EXCH((h->heapdata)[0], (h->heapdata)[(h->n_elements) - 1]);

        /* ... declare that the heap has one element less... */
        (h->n_elements)--;

        /* ... and organize it again by fixing down the first element. */
        fixDown(h, 0);

        /* Return the greatest element. */
        return aux;
    }

    return -1;
}

/**
 * @fn cleanHeap
 * @brief This function fully resets the heap (erases it).
 * @param Heap * h
 * 		Heap we want to erase.
 * @return None.
 * */
void cleanHeap(Heap *h) {
    /* In order to erase the heap it is only needed to put its elements
     * equal to zero. All the information yet stored in the vector's
     * positions are now meanless. */
    h->n_elements = 0;

    return;
}

/**
 * @fn verifyHeap
 * @brief This function verifies if the table is a heap, i. e., if the
 * 		table respects the heap's condition.
 * @param Heap * h
 * 		Heap we want to verify.
 * @return int
 * 		1 if table is a heap and 0 otherwise.
 * */
int verifyHeap(Heap *h) {
    int i;

    /* The verification starts in the end of the heap. While the element
     * we are checking is greater than zero we shall verify sequentialy
     * the elements. */
    for (i = ((h->n_elements) - 1); i > 0; i--)
        if (LESS((h->heapdata)[(i - 1) / 2], (h->heapdata)[i]))
            return 0;

    return 1;
}

/**
 * @fn heapSort
 * @brief This function is a sort function based on heaps. It starts by
 * 		arranging a table on a heap and then exchanges the last element
 * 		with the first one, fix it and so on, reducing the table in one
 * 		unity in each iteration. We end up with a ordenated table. The
 * 		complexity of this algorithm is N*log(N).
 * @param Heap * h
 * 		Heap we want to sort.
 * @return None.
 * @warning In spite of the fact that this algorithm has always a
 * 		complexity of N*log(N) its also true that it is not stable,
 * 		i. e., it may exchange the positions of elements with the same 
 * 		weight if they exist.
 * */
void heapSort(Heap *h) {
    /* This is just a cheat to save the real dimention of the Heap. */
    int backup = (h->n_elements);

    /* Before we perform the sort the table has to be a heap. */
    heapify(h);

    /* While the table is not all ordered... */
    while (h->n_elements > 0) {
        /* ... exchange the first element and the last. */
        EXCH((h->heapdata)[0], (h->heapdata)[(h->n_elements) - 1]);

        /* The first element is now in its final position. It shall not
         * be moved anymore. */
        (h->n_elements)--;

        /* Now fix the position of the new first element. */
        fixDown(h, 0);
    }

    (h->n_elements) = backup;

    return;
}

/**
 * @fn heapify
 * @brief This function converts a table in a heap by performing
 * 		successive fixDown to its elements starting in the middle of the
 * 		table until its top.
 * @param Heap * h
 * 		Heap we want to see restored.
 * @return None.
 * */
void heapify(Heap *h) {
    int i;

    for (i = (((h->n_elements) - 1) / 2); i >= 0; i--)
        fixDown(h, i);

    return;
}

/**
 * @fn isHeapEmpty
 * @brief Verifies is the heap has at least one element.
 * @param Heap * heap
 * 		Heap we want to investigate.
 * @return int
 * 		1 if heap is empty or 0 otherwise.
 * */
int isHeapEmpty(Heap *heap) {
    return (heap->n_elements == 0) ? 1 : 0;
}

/**
 * @fn incPriority
 * @brief This function changes the position of some element in the
 * 		heap by locating it in the positions table and fix its position
 * 		based on its weight.
 * @param Heap * heap
 * 		Heap in which we want to increment priority of some element.
 * @param int index
 * 		Element we want to find in the heap and fix it.
 * @return None.
 * */
void incPriority(Heap *heap, int index) {
    fixUp(heap, (heap->positions)[index]);

    return;
}
