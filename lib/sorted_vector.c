/**
 * Contains functions for the sorted vector struct
 *
 * @author: Najib Mosquera
 * @class: CS 5008
 * @term: Fall 2025
**/

#include "vector.h"
#include "movie.h"
#include <string.h>
#include <stdlib.h>


// creating a helper function for binary search to find the lower bound index
static int lower_bound_by_title(SortedMovieVector *vector, const char *key_title) {
    int low = 0;
    // search in the half-open range [low, high)
    int high = vector->size;

    while (low < high) {
        // avoiding overflow so we use (low+high)/2
        int middle = low + (high - low) / 2;
        Movie *middle_movie = vector->movies[middle];

        int comparison = strcasecmp(middle_movie->title, key_title);

        if (comparison < 0) {
            // middle_movie->title is less than key_title
            // so insertion point must be to the right of middle
            low = middle + 1;
        } else {
            // middle_movie -> title is greater or equal to key_title
            // so the insertion point is at middle or to the left of middle
            high = middle;
        }
    }

    // when loop ends, low == high == the first index where title >= key_title
    // or size meaning insert is at the end
    return low;
}

/**
 * adds a movie to the sorted vector.
 * 
 * Based on the movie (compare_movies), it will find the correct index
 * using a linear search.
 * 
 * The moment it finds that the movie to add is greater than the
 * current movie, it will insert it at that next index calling vector_insert.
 * 
 * 
 * @param vector the vector to add the movie to
 * @param movie the movie to add
*/
void add_to_sorted_vector(SortedMovieVector * vector, Movie * movie) {
    int insert_index = lower_bound_by_title(vector, movie->title);
    vector_insert(vector, movie, insert_index);
}

/**
 * Finds a movie in the sorted vector based on the title only of the movie.
 *
 * strcasecmp is used to compare the titles, so the search is case insensitive.
 *
 * For example: int cmp = strcasecmp(title, movie->title);
 *
 * You will want to implement this as a binary search. It can be done with a loop
 * or using a helper recursive function (your choice). You are free
 * to add the helper function above if you need one. 
 *
 * @param vector the vector to search
 * @param title the title of the movie to find
 * @return the movie if found, NULL otherwise
 */
Movie * find_in_sorted_vector(SortedMovieVector * vector, const char * title) {
    if (vector == NULL || vector->size == 0) {
        return NULL;
    }

    int index = lower_bound_by_title(vector, title);

    if (index < vector->size && strcasecmp(vector->movies[index]->title, title) == 0) {
        // exact match
        return vector->movies[index];
    }

    return NULL; // not found
}


/**
 * Checks if the sorted vector contains a movie with the given title.
 *
 * Very similar to find_in_sorted_vector, but instead of just finding
 * the movie will call vector_remove(vector, index) to remove the movie
 * returning the resulted removed movie.
 *
 * You will want to implement this as a binary search. It can be done with a loop
 * or using a helper recursive function (your choice). You are free
 * to add the helper function above if you need one.
 *
 * @param vector the vector to check
 * @param title the title to check for
 * @return the movie removed, NULL otherwise
 */
Movie* sorted_vector_remove(SortedMovieVector *vector, const char *title){
    if (vector == NULL || vector->size == 0) {
        return NULL;
    }

    int index = lower_bound_by_title(vector, title);

    if (index < vector->size && strcasecmp(vector->movies[index]->title, title) == 0) {
        return vector_remove(vector, index);
    }
    // not found
    return NULL;
}
