#include <stdlib.h>
#include "../include/connection.h"
#include "../include/aux.h"

/**
 * \brief Struct that handles the info related to an user and those who he follows and those who follow him
 */
struct userConnections{
     int idCommiter; // the id of a commiter
     int *idamigos; // amigos are those who he follows and those who follow him
     int size; // size_of_array
};

/**
 * @brief  Function that initializes the userconnections struct
 * @return u -> the struct userconnections already initiliazed
 */
CONNECTION *init_userConnections() {
   CONNECTION *u = malloc (30*sizeof(struct userConnections )); 
   return u;
}

/**
 * @brief  Function that resizes the block of memory earlier allocated for the array
 * @param s struct that we're working on
 * @param n integer that we're using in order to help increase the memory allocated for this struct
 * @return the array with the block of memory on the heap already allocated for it.
 */
CONNECTION *realloc_usersConnections(CONNECTION *s, int *n){
   (*n)++;
   s = realloc (s, 30 * (*n)* sizeof(struct userConnections)); 
   return s;
}

/**
 * @brief Function that adds an element to a CONNECTION struct
 * @param uc pointer to Connection struct
 * @param id id of the commiter
 * @param idA array that contains all the ids of those considered his amigos (those who he follow and those who follow him)
 * @param amigosSize size of the array (the sum of his followers with those who are followed by him)
 * @param size position 
 * @param n integer that we're using in order to help increase the memory allocated for the userconnections struct
 * @return 0
 */
void *add_elem_Connection(CONNECTION *uc, int id, int *idA,int amigosSize, int size, int *n){
   if((size + 1) >= ((*n) *  30)) uc =realloc_usersConnections(uc,n); // if we run out of memory, we'll reallocate the necessary
   uc[size].idCommiter = id;
   uc[size].idamigos = copyArray(idA,amigosSize);
   uc[size].size =amigosSize;
return uc;
}

/**
 * @brief Compare function for CONNECTION structs
 * @param aux_u1 void pointer that represents a CONNECTION struct
 * @param aux_u2 void pointer that represents a CONNECTION struct
 * @return The result of subtracting the idCommiter field form both CONNECTION structs
 */
int cmp_connection(const void *aux_u1,const void *aux_u2)
{
    CONNECTION * u1 = (CONNECTION *) aux_u1;
    CONNECTION * u2 = (CONNECTION *) aux_u2;
    int r = u1->idCommiter - u2->idCommiter;
    return r;
}

/**
 * @brief Function that sorts CONNECTION struct arrays based on idCommiter field
 * @param u CONNECTION struct arrays
 * @param size size of the CONNECTION array
 * @return 0
 */
int sort_connection(CONNECTION * u, int size)
{
    qsort(u,size,sizeof(struct userConnections),cmp_connection);
    return 0;
}

/**
 * @brief Binary Search Function for CONNECTION structs, this function searches for an authorId in the array of friends from a given position
 * @param uc CONNECTION struct array
 * @param authorID authorId to be searched
 * @param ind position of the friend array on the CONNECTION array
 * @return The result of the Binary Search either 1 if the author id exists on the array or 0 if it does not 
 */
int binary_search_amigos (CONNECTION *uc, int authorID, int ind){
   int *amigos =  copyArray(uc[ind].idamigos,uc[ind].size);
   int size = uc[ind].size;
   return pesquisaBinaria(amigos,authorID,size);
}

/**
 * @brief Funtion that finds the postion of a commiter id in a CONNECTION struct array (uc) by comparing a given commiter id with a uc[position].idCommiter
 * @param uc CONNECTION struct array
 * @param commiterID commiter id to be searched
 * @param size size of the CONNECTION array
 * @return the position of the commiter id in the CONNECTION struct array, -1 if the commiter id is not on the array
 */
int find_index_uc(CONNECTION *uc, int commiterID ,int size){
   int inf = 0;
   int sup = size-1;
   while (inf<=sup){
          int mid = (inf + sup)/2;
          if (commiterID == uc[mid].idCommiter) return mid;
          if (commiterID < uc[mid].idCommiter) sup = mid-1;
          else inf = mid+1;
   }
   return -1;
}

/**
 * @brief Function that frees all the pointer's from an element of Connection.
 * @param c CONNECTION element that we want to free.
 * @return 0
 */
static int free_elem_Connection (CONNECTION c)
{
    free(c.idamigos);
    return 0;
}

/**
 * @brief Function that frees the memory blocks previously allocated for user's elements.
 * @param c User that we want to free.
 * @param size total size
 * @return 0
 */
int free_Connection (CONNECTION *c, int size)
{
    int i;
    for(i = 0; i < size; i++)
        free_elem_Connection(c[i]);
    free(c);
    return 0;
}



