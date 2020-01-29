/**
 * @file LinkedList.c
 * @brief This file contains the attributes and methods for class
 * 		Linkedlist. The manipulating data's type is Item, declared on
 * 		Defs.h.
 * 
 * @author João Miguel Morgado Pereira Vieira, nº 79191, MEEC
 * @author Tomás Miguel Donga Cardoso, nº 79007, MEEC
 * 
 * @date December 5th, 2014
 * */

#include "LinkedList.h"

/**
 * @struct LinkedList_
 * @brief This structure contains the necessary fields of an linked
 * 		list's element.
 * */
struct LinkedList_ {
    Item this;
    LinkedList *next;
};

/**
 * @fn initList
 * @brief Initializes the linked list.
 * @return LinkedList *
 * 		Pointer to the initialized list.
 * */
LinkedList *initList() {
    /* To initilize a list we just have to put its first pointer to NULL
     * as it have no elements. */
    return (LinkedList *) NULL;
}

/**
 * @fn insertUnsortedItemList
 * @brief Inserts an item in the beginning of the list.
 * @param LinkedList * list
 * 		List where it is supposed to insert the item.
 * @param Item item
 * 		Item to be inserted in the list.
 * @return LinkedList *
 * 		Pointer to beginning of the list.
 * */
LinkedList *insertUnsortedItemList(LinkedList *list, Item item) {
    LinkedList *new;

    /* Allocating the memory for the new element. */
    new = (LinkedList *) malloc(sizeof(LinkedList));
    if (new == (LinkedList *) NULL)
        makeException(ERROR_MEMORY_ALLOCATION);

    /* Setting its value. */
    (new->this) = item;

    /* Inserting the new element in the beggining of the list. */
    (new->next) = list;

    return new;
}

/**
 * @fn insertSortedItemList
 * @brief Inserts an item in the list. The position of insertion will
 * 		depend on a comparison between the item and the elements of
 * 		the list.
 * @param LinkedList * list
 * 		Pointer to the list that may be insert the item.
 * @param Item item
 * 		Item to be inserted in the list.
 * @param int ( * lessThan )( Item , Item )
 * 		Pointer to the function that has the hability of comparating two
 * 		items.
 * @return LinkedList *
 * 		Pointer to the beginning of the list.
 * */
LinkedList *insertSortedItemList(LinkedList *list, Item item, int ( *lessThan )(Item, Item)) {
    LinkedList *new, *aux;

    new = (LinkedList *) malloc(sizeof(LinkedList));
    if (new == (LinkedList *) NULL)
        makeException(ERROR_MEMORY_ALLOCATION);

    (new->this) = item;

    /* If the list is empty or the insertion must be performed on the
     * beginning. The same if the new element is greater than the first. */
    if ((list == (LinkedList *) NULL) || (lessThan(item, list->this))) {
        (new->next) = list;
        return new;
    } else {
        /* Otherwise we have to find the right place for the new element
         * in the list. */
        for (aux = list; ((aux->next) != (LinkedList *) NULL &&
                          !lessThan(item, aux->next->this)); aux = (aux->next));

        (new->next) = (aux->next);
        (aux->next) = new;

        return list;
    }
}

/**
 * @fn getNextNodeList
 * @brief Gets the next node of the linked list.
 * @param LinkedList * node
 * 		Reference node to find the next of.
 * @return LinkedList *
 * 		Node which follows the node passed through parameter.
 * */
LinkedList *getNextNodeList(LinkedList *node) {
    return (node == (LinkedList *) NULL) ? (LinkedList *) NULL : (node->next);
}

/**
 * @fn getPreviousNodeList
 * @brief Gets the previous node of the linked list.
 * @param LinkedList * list
 * 		Pointer to the beginning of the list.
 * @param LinkedList * node
 * 		Reference node to find the previous of.
 * @return LinkedList *
 * 		Node which predicts the node passed through parameter.
 * @warning This function is dangerous since its complexity depends on
 * 		the lenght of the list. The list must be iterated from the 
 * 		beginning until we find the node that predicts the one we passed
 * 		as argument. The complexity of this function is O(n).
 * */
LinkedList *getPreviousNodeList(LinkedList *list, LinkedList *node) {
    LinkedList *aux;

    if (node == list || node == (LinkedList *) NULL)
        return (LinkedList *) NULL;

    /* We have to iterate the list until we find the node above the one
     * passed through parameter. */
    for (aux = list; (aux->next) != node; aux = (aux->next));

    return aux;
}

/**
 * @fn getItemNode
 * @brief Gets the value of the camp item in some node os the list.
 * @param LinkedList * node
 * 		Node which item is required.
 * @return Item
 * 		Pointer to item storaged in the node passed by parameter.
 * */
Item getItemNode(LinkedList *node) {
    return (node->this);
}

/**
 * @fn freeList
 * @brief Iterates all the list and frees the structures and its 
 * 		containers.
 * @param LinkedList * list
 * 		Pointer to the beginning of the list.
 * @param void ( * freeStructure )( Item )
 * 		Pointer to the function responsable for free the storage
 * 		structures that are unknown by the list's implementation.
 * @return None.
 * */
void freeList(LinkedList *list, void ( *freeStructure )(Item)) {
    if (list == (LinkedList *) NULL)
        return;

    if ((list->next) != (LinkedList *) NULL)
        freeList(list->next, freeStructure);

    if (freeStructure != NULL)
        freeStructure(list->this);

    free(list);

    return;
}

/**
 * @fn forEach
 * @brief Iterates all the list and perform some operations about each
 * 		item. 
 * @param LinkedList * list
 * 		List for iteration.
 * @param void ( * function )( Item )
 * 		Function to apply to each element of the list.
 * @return None.
 * */
void forEach(LinkedList *list, void ( *function )(Item)) {
    LinkedList *aux;

    for (aux = list; aux != (LinkedList *) NULL; aux = (aux->next))
        function(aux->this);

    return;
}

/**
 * @fn getListLenght
 * @brief Obtains the number of elements stored in a list passed by
 * 		parameter.
 * @param LinkedList * list
 * 		List to obtain the number of elements.
 * @return int
 * 		The number of elements stored by this list.
 * @warning This function iterates all the list to obtain the number of
 * 		elements on it. So the complexity of this function is linear
 * 		O(N).
 * */
int getListLenght(LinkedList *list) {
    int lenght;
    LinkedList *aux;

    /* The list shell be iterated to count the number of elements in it. */
    for ((lenght = 0, aux = list); aux != (LinkedList *) NULL; (aux = (aux->next), lenght++));

    return lenght;
}

/**
 * @fn insertWithNoReturn
 * @brief Sometimes we are no free for changing the pointer to the beginning
 * 		of the list. In that case one solution is to insert the new element
 * 		in the second place (if we are not working with sorted lists) and
 * 		then nothing needs to be set outside.
 * @param List * list
 * 		List where we want to insert
 * @param Item item
 * 		Item we want to insert in the list.
 * */
void insertWithNoReturn(LinkedList *list, Item item) {
    LinkedList *new;

    /* Allocating the memory for the new element. */
    new = (LinkedList *) malloc(sizeof(LinkedList));
    if (new == (LinkedList *) NULL)
        makeException(ERROR_MEMORY_ALLOCATION);

    /* Setting its value. */
    (new->this) = item;

    (new->next) = (list->next);
    (list->next) = new;

    return;
}
