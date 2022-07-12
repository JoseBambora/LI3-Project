#include "../include/stringarray.h"
#include "../include/tuplo.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Array of strings.
 */
struct stringarray{
    char *str;
};

/**
 * @brief Function that allocate memory for an array of strings.
 * @return Array allocated.
 */
STRARRAY* init_strarray()
{
    STRARRAY *sa = malloc(30 * sizeof(struct stringarray));
    return sa;
}
/**
 * @brief Function that reallocate memory for an array of strings.
 * @return Array reallocated.
 */
static STRARRAY* realloc_strarray(STRARRAY *sa, int *N)
{
    (*N)++;
    sa = realloc(sa,(*N) * 30 * sizeof(struct stringarray));
    return sa;
}

/**
 * @brief Function that adds an element to a Array of strings.
 * @param sa Array to add a string.
 * @param str String to add.
 * @param N Pointer to see if we have to realloc.
 * @param size Size of the array of strings.
 * @return Array after the addition.
 */
STRARRAY *add_elem_strarray (STRARRAY *sa, char *str, int *N, int size)
{
    if((*N) * 30 <= size +1) sa = realloc_strarray(sa, N);
    if(str) sa[size].str = strdup(str);
    else sa[size].str = NULL;
    return sa;
}

/**
 * @brief Funtion that returns copy of some element of the array of Strings.
 * @param sa Array of strings.
 * @param ind Index.
 * @return The copy of the string on index ind of sa.
 */

static char* return_str_strarray (STRARRAY *sa, int ind)
{
    return(strdup(sa[ind].str));
}

/**
 * @brief Funtion that frees the allocated memmory for Array of strings.
 * @param sa Pointer to array to free.
 * @param size Size of array.
 * @return 0.
 */
int free_str_array(STRARRAY *sa, int size)
{
    for(int i = 0; i < size; i++)
        free(sa[i].str);
    return 0;
}

/**
 * @brief Function that transfers information from an String array to an array of tuplos.
 * @param sa String array to convert.
 * @param size Its size.
 * @param s_tuplos Pointer to save the final size of the array tuplo.
 * @return Final array TUPLO
 */
void *strarray_language_qtty(STRARRAY *sa, int size, int *s_tuplo)
{
    TUPLO* as = init_tuplo();
    int size_tuplo = 0;
    int i, n = 1;
    for(i = 0; i < size; i++)
    {
        int inc = 0;
        char *lan = return_str_strarray(sa,i);
        as = add_tuplo(as,lan,&n,size_tuplo,1,&inc);
        if(inc) size_tuplo ++;
        free(lan);
    }
    sort_tuplo(as,size_tuplo);
    (*s_tuplo) = size_tuplo; 
    free_str_array(sa,size);
    return as;
}