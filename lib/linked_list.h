/**
 * Simple Linked list implementation
 *
 * @author: Najib Mosquera
 * @class: CS 5008
 * @term: Fall 2025
 */
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdbool.h>
#include "movie.h"

typedef struct snode {
    Movie * movie;
    struct snode *next;
} node;

typedef struct linked_list {
    node *head;
    node *tail;
    int size;
} LinkedList;

// __ means this should be a hint that it is internal to the linked list implementation, 
// added here, so sorted_list.c can use it
node * __ll__new_node(Movie *movie); 

LinkedList *new_linked_list();
void free_linked_list(LinkedList *list);
void clear_and_free_linked_list(LinkedList *list);
void ll_add_front(LinkedList *list, Movie *movie);
void ll_add_back(LinkedList *list, Movie *movie);
void ll_insert(LinkedList *list, Movie *movie, int n);
Movie * ll_remove_front(LinkedList *list);
Movie * ll_remove_back(LinkedList *list);
Movie * ll_remove(LinkedList *list, int n);
Movie * ll_get(LinkedList *list, int n);
bool ll_is_empty(LinkedList *list);
char* ll_to_str(LinkedList *list);


/************************* SortedList Struct and Helper Function *******/

typedef LinkedList SortedList; // SortedList is just a LinkedList with a few specific functions
// yes, the above code doesn't really do 'anything', but it does make external code
// a little more readable as it helps get across intent (that we are using a linked list
// as a sorted list)

void add_to_sorted_list(SortedList *list, Movie *movie);
Movie* find_in_sorted_list(SortedList *list, const char * title);
Movie* sorted_list_remove(SortedList *list, const char * title);

// these functions are just for convience in naming, they are the same as the linked list functions
#define sorted_list_to_str ll_to_str
#define free_sorted_list free_linked_list
#define new_sorted_list new_linked_list

#endif