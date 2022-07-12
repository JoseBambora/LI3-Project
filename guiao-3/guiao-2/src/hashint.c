#include <stdio.h>
#include "../include/hashint.h"
#include <stdlib.h>

typedef struct nodo {
    int id;
    struct nodo *prox;
} Nodo;

int size = 1000000;

/**
 * @brief Function that returns the key
 * @param repo The integer to find the key
 * @param size Size of the hashtable
 * @return The key
 */
static int hash(int repo)
{
    return repo % size;
} 

/**
 * @brief Function that initialize a Hashtable
 * @return The hashtable empty
 */
THash init_hash()
{
    THash r = malloc(sizeof(Nodo) * size);
    for(int i = 0; i <  size; i++)
        r[i] = NULL;
    return r;
}

/**
 * @brief Function that inserts an element to the hashtable
 * @param t Hashtbale to insert
 * @param re Integer to insert
 * @param size Size of the Hashtable
 */
void insert_hash (THash t, int re)
{
    int ind = hash(re);
    Nodo *n = t[ind];
    Nodo *r = malloc(sizeof(Nodo));
    r->id = re;
    r->prox = n;
    t[ind] = r;
}

/**
 * @brief Function that sees if an integer already exist on the hastable
 * @param t Hashtable
 * @param repo The integer to see if it exist
 * @param size Size of the hashtable
 * @return 1 if it exist, 0 if not.
 */
int exist_elem_hash(THash t, int re)
{
    int key = hash(re);
    Nodo * aux = t[key];
    while(aux)
    {
        if(aux->id == re) return 1; 
        aux = aux->prox;
    }
    return 0;
}

/**
 * @brief Function frees the memory allocated for hastable
 * @param t Hashtable
 * @param size Size of the hashtable
 */
void free_hash(THash t)
{
    for(int i = 0; i < size; i++)
    {
        Nodo * aux = t[i];
        while(aux)
        {
            Nodo *aux2 = aux;
            aux = aux->prox;
            free(aux2);
        }
    }
    free(t);
}