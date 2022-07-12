#include "../include/quadruplo.h"
#include "../include/tuplo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/**
 * @struct Struct used to store information needed on query 10, in this struct we can store four items,the id and login of a user, the quantity of commits made by that user and the id of the repo where the user makes commits
 */
struct quadruplo{
    int id;
    char *login;
    int qtty;
    int repo_id;
};

/**
 * @brief Function that initializes the array of QUADRUPLO elements
 * @return  The array initialized with memory for 30 elements
 */
QUADRUPLO* init_quadruplo() {
    QUADRUPLO *tr = malloc(30 * sizeof(struct quadruplo));
    return tr;    
}

/**
 * @brief Function that resizes the block of memory earlier allocated for the quadruplo array
 * @param tr QUADRUPULO array
 * @param n Buffer
 * @return The quadruplo array with the block of memory on the heap already allocated for it
 */
static QUADRUPLO* realloc_quadruplo(QUADRUPLO *tr, int *n){
    (*n)++;
    tr = realloc(tr,(*n)*30*sizeof(struct quadruplo));
    return tr;
}

/**
 * @brief Auxiliary function to add an element to the QUADRUPLO array
 * @param atr quadruplo array
 * @param id id of the new element
 * @param login login of the new element
 * @param qtty qtty of the new element
 * @param size size of the QUADRUPLO array 
 * @param N integer pointer
 * @param repo_id repoId of the new element
 * @return 0
 */
QUADRUPLO* add_elem_quadruplo(QUADRUPLO *atr, int id, char *login, int qtty, int size,int *N ,int repo_id){
    if(size + 1 >= (*N) *  30) atr = realloc_quadruplo(atr,N);
    atr[size].id = id; 
    atr[size].login = strdup(login); 
    atr[size].qtty = qtty;
    atr[size].repo_id = repo_id;
    return atr;
}

/**
 * @brief Auxiliary function of sort_quadruplo, it compares two void pointers that represents QUADRUPLO structs
 * @param a void pointer
 * @param b void pointer
 * @return the result of subtracting the quantities of the two QUADRUPLO structs
 */
static int cmpfunc_quadruplo (const void *a, const void *b) {
    QUADRUPLO *t1 = (QUADRUPLO *) a;
    QUADRUPLO *t2 = (QUADRUPLO *) b;
    return (t2->repo_id - t1->repo_id);
}

/**
 * @brief Function that sorts an array of QUADRUPLO elements
 * @param atr QUADRUPLO array
 * @param size size of the quadruplo array
 * @return 0
 */
int sort_quadruplo(QUADRUPLO *atr, int size){
    qsort(atr,size, sizeof(struct quadruplo), cmpfunc_quadruplo);
    return 0;
}

/**
 * @brief Funtion that returns the id field of a quadruplo
 * @param t QUADRUPLO
 * @param indice position of the quadruplo in a quadruplo array
 * @return the id of the selected quadruplo
 */
static int return_id_quadruplo(QUADRUPLO *t, int indice){
    return t[indice].id;
}

/**
 * @brief Funtion that returns the login field of a quadruplo's id
 * @param t QUADRUPLO
 * @param indice position of the quadruplo in a quadruplo array
 * @return the login of the selected quadruplo
 */
static char *return_login_quadruplo(QUADRUPLO *t, int indice){
    return strdup(t[indice].login);
}

/**
 * @brief Funtion that returns the qtty of a quadruplo's id
 * @param t QUADRUPLO
 * @param indice position of the quadruplo in a quadruplo array
 * @return the qtty of the selected quadruplo
 */
static int return_qtty_quadruplo(QUADRUPLO *t, int indice){
    return t[indice].qtty;
}

/**
 * @brief Funtion that returns the repoid of a quadruplo's id
 * @param t QUADRUPLO
 * @param indice position of the quadruplo in a quadruplo array
 * @return the repoid of the selected quadruplo
 */
static int return_repo_id (QUADRUPLO *t, int ind)
{
    return t[ind].repo_id;
}

/**
 * @brief Funtion that changes the string field on the indice position of a Quadruplo array
 * @param t QUADRUPLO array struct
 * @param indice position of a QUADRUPLO whose string field we want to change
 * @param str new string that will replace the old one
 * @return 0;
 */
static int set_str_quadruplo(QUADRUPLO *t, int indice, char *str)
{
    t[indice].login = strdup(str);
    return 0;
}


/**
 * @brief Function that frees the memory allocated to an array of QUADRUPLO
 * @param t QUADRUPLO array struct
 * @param size size of the array
 * @return 0
 */
int free_quadruplo(QUADRUPLO *t, int size)
{
    int i;
    for(i = 0; i < size; i++){
        free (t[i].login);
    }
    free (t);
    return 0;
}

/**
 * @brief Function that adds the content from a QUADRUPLO array into the answer files
 * @param t QUADRUPLO array
 * @param size Size of the QUADRUPLO array
 * @param num Number of the QUADRUPLO array
 * @param File Output file
 * @return 0
 */
int add_content_quadruplo (QUADRUPLO *t, int size, int num, void* File, void *File_query)
{
    FILE *newFile = (FILE *) File;
    FILE *query = (FILE *) File_query;
    for(int i = 0;i < size; i++)
    {
        int id = return_id_quadruplo(t,i);
        char *desc = return_login_quadruplo(t,i);
        int qtty = return_qtty_quadruplo(t,i);
        int ri = return_repo_id(t,i);
        if(i < num) 
            fprintf(newFile,"%d;%s;%d;%d\n",id,desc,qtty,ri);
        fprintf(query,"%d;%s;%d;%d\n",id,desc,qtty,ri);
        free(desc);
    }
    fclose(newFile);
    fclose(query);
    return 0;
}


/**
 * @brief Function that sorts a certain part of an array of quadruplo.
 * @param t Array to sort.
 * @param j Lower index.
 * @param i Upper index.
 * @return 0.
 */
static int sort_quadruplo2(QUADRUPLO *t, int j, int i)
{
    qsort(t+j,i-j,sizeof(QUADRUPLO),cmpfunc_quadruplo);
    return 0;
}

/**
 * @brief Function that sorts a certain part of an array of quadruplo.
 * @param size Size of the array.
 * @return 0.
 */
QUADRUPLO *sort_aux(QUADRUPLO *t, int size)
{
    int i,j = 0;
    int ri = return_repo_id(t,0);
    for(i = 1;  i < size; i++)
    {
        int ra = return_repo_id(t,i);
        if(ri != ra)
        {
            if(i -j != 1) sort_quadruplo2(t,j,i);
            ri = ra;
            j = i;
        }
    }
    if(j!= i && i -j != 1) sort_quadruplo2(t,j,i);
    return t;
}

/**
 * @brief Function that complete the information from quadruplo based of one Tuplo.
 * @param s_tr Size of the array Quadruplo.
 * @param tu Array tuplo to get information.
 * @param s_tu Size of the array Tuplo.
 * @return The Quadruplo sorted.
 */
QUADRUPLO *complete_quadruplo_tuplo(QUADRUPLO *tr, int s_tr, void *tu, int s_tu)
{
    int i;
    for(i = 0 ; i < s_tr; i++)
    {
        int ri = return_id_quadruplo(tr,i);
        int ind = pesquisa_bin_tuplo(tu,0,s_tu,ri);
        if(ind != -1)
        {
            char *login = return_tuplo_str(tu,ind);
            set_str_quadruplo(tr,i,login);
            free(login);
        }
    }
    return tr;
}