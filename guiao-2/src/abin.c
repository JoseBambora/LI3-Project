#include "../include/abin.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @struct Binary tree struct
 * 
 */
struct btree{
    int nodo;      // Content of the node.
    BTREE esq;     // Tree Left.
    BTREE dir;     // Tree Right.
};

/**
 * @brief Fucntion that initializes a binary tree with a number.
 * @param n number put on a node
 * @return the tree initialized
 */
BTREE init_nodo(int n)
{
    BTREE b = malloc(sizeof(struct btree));
    b->nodo = n;
    b->esq = NULL;
    b->dir = NULL;
    return b;
}

/**
 * @brief Function that adds an element to a Binary tree
 * @param n Binary Tree
 * @param num Numerical element to add to the Binary Tree
 * @return Binary Tree with the element added
 */
BTREE add_elem(BTREE n, int num)
{
    if(!n) return (init_nodo(num));
    if(num < n->nodo) n->esq = add_elem(n->esq,num);
    else n->dir = add_elem(n->dir,num);
    return n;
}

/**
 * @brief Function that checks if a number exists on a Binary Tree
 * @param n Binary Tree
 * @param num Number
 * @return 1 if the number exists 0 if not
 */
int exist_elem (BTREE n, int num)
{
    if(!n) return 0;
    if(n->nodo < num)
    {
        int r = exist_elem(n->dir,num);
        return r == 0 ? 0 : ++r;
    }
    if(n->nodo > num)
    {
        int r = exist_elem(n->esq,num);
        return r == 0 ? 0 : ++r;
    }
    return 1;
}


/**
 * @brief Function that frees memory alocated for a Binary Tree
 * @param bt Binary Tree
 * @return 0
 */
int free_btree (BTREE bt)
{
    if(!bt) return 0;
    free_btree(bt->esq);
    free_btree(bt->dir);
    free(bt);
    return 0;
}
