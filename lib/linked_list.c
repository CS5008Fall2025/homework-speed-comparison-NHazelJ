/**
 * Singly linked list implementation.
 *
 * @author: Najib Mosquera
 * @class: CS 5008
 * @term: Fall 2025
 */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "movie.h"
#include "linked_list.h"

// helper function to create a new node
// allocating memory for a node, store the movie pointer, and set next to NULL
static node *make_new_node(Movie *movie) {
    node *new_node = (node *)malloc(sizeof(node));
    new_node->movie = movie;
    new_node->next = NULL;
    return new_node;
}

/** 
 * Creates a new linked list node.
*/
node * __ll__new_node(Movie *movie) {
    node *new_node = (node *) malloc(sizeof(node));
    new_node->movie = movie;
    new_node->next = NULL;
    return new_node;
}

/**
 * Creates a new linked list.
 * 
 * @return a pointer to the new linked list
 */
LinkedList *new_linked_list() {
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

/**
 * Frees the memory associated with a linked list.
 * 
 * Frees just the linked list and nodes, the movies
 * stored are not freed. 
 * @param list the linked list to free
 */
void free_linked_list(LinkedList *list) {
    node *curr = list->head;
    node *next;
    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }
    free(list);
}

/**
 * Frees the memory, including memory allocated
 * to movies stored in the link list. 
 * 
 * @param list the linked list to free
*/
void clear_and_free_linked_list(LinkedList *list) {
    node *curr = list->head;
    node *next;
    while (curr != NULL) {
        next = curr->next;
        free_movie(curr->movie);
        free(curr);
        curr = next;
    }
    free(list);
}

/**
 * Adds a movie to the front of a linked list.
 * 
 * Don't forget to update the tail pointer if the list is empty,
 * as when there is a single node, head and tail should both point
 * towards it.
 * 
 * @param list the linked list to add to
 * @param movie the movie to add
 */
void ll_add_front(LinkedList *list, Movie *movie) {
    if (list == NULL){
        return;
    }
    node *new_node = make_new_node(movie);
    // new node points to former head
    new_node->next = list->head;
    // head becomes new node
    list->head = new_node;

    if (list->size == 0) {
        // if list was empty tail also points to new_node
        list->tail = new_node;
    }

    list->size++;
}

/**
 * Adds a movie to the back of a linked list.
 *
 * Don't forget to update the head pointer if the list is empty,
 * as when there is a single node, head and tail should both point
 * towards it.
 *
 * @param list the linked list to add to
 * @param movie the movie to add
 */
void ll_add_back(LinkedList *list, Movie *movie) {
    if (list == NULL) {
        return;
    }
    node *new_node = make_new_node(movie);

    if (list->size == 0) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        // link old tail to new node
        list->tail->next = new_node;
        // move tail to new node  
        list->tail = new_node;
    }

    list->size++;
}



/**
 * Inserts a movie into a linked list at a given index.
 * 
 * if n == 0, safe to call ll_add_front, if n == list->size, safe to call ll_add_back
 * 
 * if n is out of bounds, do nothing (return early)
 * 
 * @param list the linked list to insert into
 * @param movie the movie to insert
 * @param n the index to insert at
 */
void ll_insert(LinkedList *list, Movie *movie, int n) {
   if (list == NULL) {
    return;
   }
    if (n < 0 || n> list->size){
        // out of bounds -> ignore
        return;
    }

    if (n== 0) {
        ll_add_front(list, movie);
        return;
    }
    if (n == list->size) {
        ll_add_back(list, movie);
        return;
    }

    node *previous = list->head;
    for (int i = 0; i < n - 1; i++) {
        // move to node at position index - 1
        previous = previous->next;
    }

    node *new_node = make_new_node(movie);
    // new node points to the old index node
    new_node->next = previous->next;
    // previous now links to new node
    previous->next = new_node;
    list->size++;
}


/**
 * Removes the first movie from a linked list.
 * 
 * Don't forget if there is only one item in the list, and it is removed,
 * to update the tail pointer.
 * 
 * @param list the linked list to remove from
 * @return the movie that was removed
 */
Movie * ll_remove_front(LinkedList *list) {
    // The movie will return at the end
    Movie *movie = NULL;
    // f the list doesn’t exist or is empty there’s nothing to remove
    if (list == NULL || list->size == 0) {
        return movie;
    }
    // save the current head node (the first node)
    node *old_head = list->head;

    // save the Movie* from that node
    movie = old_head->movie;

    // move the head pointer to the next node
    list->head = old_head->next;
    // free the memory used by the old head node
    free(old_head);
    // decrease the list size by 1
    list->size--;

    // if the list is now empty make sure tail = NULL too
    if (list->size == 0) {
        list->tail = NULL;
    }
    // return the Movie that was stored in the removed node
    return movie;
}


/**
 * Removes the last movie from a linked list.
 * 
 * Don't forget if there is only one item in the list, and it is removed,
 * to update the head pointer.
 * 
 * @param list the linked list to remove from
 * @return the movie that was removed
 */
Movie * ll_remove_back(LinkedList *list) {
    // return the removed movie pointer
    Movie *movie = NULL;
    // if the list doesn't exist or is empty, nothing to remove
    if (list == NULL || list->size == 0) {
        return movie; // NULL
    }
    // if there is only one node, removing the back is same as removing the front
    if (list->size == 1) {
        return ll_remove_front(list);
    }
    // otherwise we need to find the node just BEFORE the tail
    node *previous_to_tail = list->head;
    while (previous_to_tail->next != list->tail) {
        previous_to_tail = previous_to_tail->next;
    }
    // previous_to_tail now points to the node right before the tail
    node *old_tail = list->tail;
    // save the movie to return
    movie = old_tail->movie;
    // unlink and free the old tail node
    previous_to_tail->next = NULL;
    // tail moves back by one
    list->tail = previous_to_tail;
    free(old_tail);
    // decrease size
    list->size--;

    return movie;
}


/**
 * Removes a movie from a linked list at a given index.
 * 
 * if n == 0, safe to call ll_remove_front, if n == list->size - 1, safe to call ll_remove_back
 * 
 * if n is out of bounds, return NULL
 * 
 * @param list the linked list to remove from
 * @param n the index to remove at
 * @return the movie that was removed
 */
Movie * ll_remove(LinkedList *list, int n) {
    // the movie will return NULL if nothing removed
    Movie * movie = NULL;
    // validate inputs and bounds
    if (list == NULL || n < 0 || n >= list->size) {
        return movie; // NULL
    }
    // If removing the first element, reuse front remover
    if (n == 0) {
        return ll_remove_front(list);
    }
    // if removing the last element reuse back remover
    if (n == list->size - 1) {
        return ll_remove_back(list);
    }
    // otherwise, walk to the node just BEFORE index n
    node *previous = list->head;
    for (int i = 0; i < n - 1; i++) {
        previous = previous->next;
    }
    // target is the node at position n that we want to remove
    node *target = previous->next;
    // save the movie pointer to return
    movie = target->movie;
    // unlink 'target' from the list
    previous->next = target->next;
    // free the removed node NOT the movie
    free(target);
    // decrease size
    list->size--;

    return movie;
}

/**
 * Gets a movie from a linked list at a given index.
 * 
 * if n is out of bounds, return NULL
 * 
 * @param list the linked list to get from
 * @param n the index to get at
 * @return the movie at the given index
 */
Movie* ll_get(LinkedList *list, int n) {
    node *curr = list->head;
    if (n < 0 || n >= list->size) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        curr = curr->next;
    }
    return curr->movie;
}

/**
 * Checks if a linked list contains a given movie.
 * 
 * Rare if a linked list contains a movie more than once, but
 * if so, just immediately return true.
 * 
 * @param list the linked list to check
 * @param movie the movie to check for
 * @return true if the linked list contains the movie, false otherwise
 */
bool ll_contains(LinkedList *list, Movie *movie) {
    node *curr = list->head;
    while (curr != NULL) {
        if (curr->movie == movie) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

/**
 * Checks if a linked list is empty.
 * 
 * @param list the linked list to check
 * @return true if the linked list is empty, false otherwise
 */
bool ll_is_empty(LinkedList *list) {
    return list->size == 0;
}

/**
 * Converts a linked list to a string representation.
 * 
 * @param list the linked list to convert
 * @return a string representation of the linked list
 */
char* ll_to_str(LinkedList *list) {
    
    char *str = (char *)malloc(sizeof(char) * (MAX_MOVIE_STR_LEN + 3) * list->size);
    if (list->size == 0) {
        strcpy(str, "[]");
        return str; // early exit
    }
    // implied else
    strcpy(str, "[");
    node *curr = list->head;
    while (curr != list->tail) {
        char *movie_str = movie_to_str(curr->movie);
        strcat(str, movie_str);
        strcat(str, ", ");
        free(movie_str);
        curr = curr->next;
    }
    // now add the tail
    char *movie_str = movie_to_str(curr->movie);
    strcat(str, movie_str);
    free(movie_str);
    strcat(str, "]");

    return str;
}

