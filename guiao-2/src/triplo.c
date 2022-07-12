#include "../include/triplo.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @struct Struct used to store information needed on certain queries, in this struct we can store three items,the id and login of a user, and the quantity of commits made by that user
 */
struct triplo{
    int id;
    char *login;
    int qtty;
};

/**
 * @brief Function that initializes the array of TRIPLO elements
 * @return  The array initialized with memory for 30 elements
 */
TRIPLO* init_triplo() {
    TRIPLO *tr = malloc(30 * sizeof(struct triplo));
    return tr;    
}

/**
 * @brief Function that resizes the block of memory earlier allocated for the triplo array
 * @param tr Triplo array
 * @param n Buffer
 * @return The triplo array with the block of memory on the heap already allocated for it
 */
TRIPLO* realloc_triplo(TRIPLO *tr, int *n){
    (*n)++;
    tr = realloc(tr,(*n)*30*sizeof(struct triplo));
    return tr;
}

/**
 * @brief Auxiliary function to add an element to the TRIPLO array
 * @param atr triplo array
 * @param id id of the new element
 * @param login login of the new element
 * @param qtty qtty of the new element
 * @param size size of the TRIPLO array 
 * @param N integer pointer
 * @return 0
 */
void* add_elem_triplo(TRIPLO *atr, int id, char *login, int qtty, int size,int *N){
    if(size + 1 >= (*N) *  30) atr = realloc_triplo(atr,N);
    atr[size].id = id; 
    atr[size].login = strdup(login); 
    atr[size].qtty = qtty;
return atr;
}

/**
 * @brief Auxiliary function of sort_triplo, it compares two void pointers that represents TRIPLO structs
 * @param a void pointer
 * @param b void pointer
 * @return the result of subtracting the quantities of the two TRIPLO structs
 */
static int cmpfunc_triplo (const void *a, const void *b) {
    TRIPLO *t1 = (TRIPLO *) a;
    TRIPLO *t2 = (TRIPLO *) b;
    return (t2->qtty - t1->qtty);
}

/**
 * @brief Function that sorts an array of triplos
 * @param atr TRIPLO array
 * @param size size of the triplo array
 * @return 0
 */
int sort_triplo(TRIPLO *atr, int size){
    qsort(atr,size, sizeof(struct triplo), cmpfunc_triplo);
    return 0;
}

/**
 * @brief Funtion that returns the id field of a triplo
 * @param t TRIPLO
 * @param indice position of the triplo in a triplo array
 * @return the id of the selected triplo
 */
int return_id_triplo(TRIPLO *t, int indice){
    return t[indice].id;
}

/**
 * @brief Funtion that returns the login field of a triplo's id
 * @param t TRIPLO
 * @param indice position of the triplo in a triplo array
 * @return the login of the selected triplo
 */
static char *return_login_triplo(TRIPLO *t, int indice){
    return strdup(t[indice].login);
}

/**
 * @brief Funtion that returns the qtty of a triplo's id
 * @param t TRIPLO
 * @param indice position of the triplo in a triplo array
 * @return the qtty of the selected triplo
 */
static int return_qtty_triplo(TRIPLO *t, int indice){
    return t[indice].qtty;
}

/**
 * @brief Funtion that sets the qtty field of a triplo to a new value
 * @param t TRIPLO
 * @param indice position of the triplo in a triplo array
 * @param newQtty new value to insert on qtty
 */
static void set_qtty_triplo (TRIPLO *t, int indice, int newQtty){
    t[indice].qtty = newQtty;
}

/**
 * @brief Funtion that changes the string field on the indice position of a TRIPLO array
 * @param t TRIPLO array struct
 * @param indice position of a TRIPLO whose string field we want to change
 * @param str new string that will replace the old one
 * @return 0;
 */
int set_str_triplo(TRIPLO *t, int indice, char *str)
{
    t[indice].login = strdup(str);
    return 0;
}

/**
 * @brief Function that frees the memory allocated to an array of TRIPLO
 * @param t TRIPLO array struct
 * @param size size of the array
 * @return 0
 */
int free_triplo(TRIPLO *t, int size)
{
    int i;
    for(i = 0; i < size; i++){
        free (t[i].login);
    }
    free (t);
    return 0;
}

/**
 * @brief Function that adds the content from a TRIPLO array into the answer files for query 5 and 6
 * @param t TRIPLO array
 * @param size Size of the TRIPLO array
 * @param num Number of the TRIPLO array
 * @param File Output file
 * @return 0
 */
int add_content_triplo (TRIPLO *t, int size, int num, void* File)
{
    FILE *newFile = (FILE *) File;
    for(int i = 0; i< num && i < size; i++)
    {
        int id = return_id_triplo(t,i);
        char *desc = return_login_triplo(t,i);
        int qtty = return_qtty_triplo(t,i);
        fprintf(newFile,"%d;%s;%d\n",id,desc,qtty);
        free(desc);
    }
    return 0;
}

/**
 * @brief Function that adds the content from a TRIPLO array into the answer files for query 9 and 10
 * @param t TRIPLO array
 * @param size Size of the TRIPLO array
 * @param num Number of the TRIPLO array
 * @param File Output file
 * @return 0
 */
int add_content_triplo2 (TRIPLO *t, int size, int num, void* File)
{
    FILE *newFile = (FILE *) File;
    for(int i = 0; i< num && i < size; i++)
    {
        int id = return_id_triplo(t,i);
        char *desc = return_login_triplo(t,i);
        fprintf(newFile,"%d;%s\n",id,desc);
        free(desc);
    }
    return 0;
}

/**
 * @brief Function that increments the qtty field of an element on a TRIPLO array
 * @param t TRIPLO array
 * @param size Size of the TRIPLO array
 * @param id Id of the element whose qtty field will be increased
 * @return 0
 */
int inc_qtty(TRIPLO *t, int size, int id)
{
    int i;
    for(i = 0; i < size; i++)
    {
        if(return_id_triplo(t,i) == id)
        {
            int q = return_qtty_triplo(t,i) + 1;
            set_qtty_triplo(t,i,q);
            break;
        }
    }
    return 0;
}