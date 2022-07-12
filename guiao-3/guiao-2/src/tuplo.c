#include "../include/tuplo.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @struct Struct of Typedef tuplo.
 */
struct tuplo{
    char *str;
    int num;
};

/**
 * @brief Allocate memory to array TUPLO.
 * @return Tuplo alocated.
 */
TUPLO* init_tuplo()
{
    TUPLO *t = malloc(30 * sizeof(struct tuplo));
    return t;
}

/**
 * @brief Reallocate memory to array TUPLO.
 * @param as Tuplo that we want to reallocate.
 * @param N Pointer that has a number that will define the size of Tuplo result memory.
 * @return Tuplo reallocated.
 */
static TUPLO* realloc_tuplo(TUPLO *as, int *N)
{
    (*N)++;
    as = realloc(as, (*N) * 30 * sizeof(struct tuplo));
    return as;
}

/**
 * @brief Checks if a string exists on TUPLO.
 * @param a Tuplo that we will search string.
 * @param str string that we want to check if it exist on Tuplo.
 * @param size size of Tuplo.
 * @return The Index if the string exist, -1 if not.
 */
static int exist_language_tuplo(TUPLO *a, char*str, int size)
{
    int i;
    for(i = 0; i < size; i++)
        if(strcmp(a[i].str, str) == 0) return i;
    return -1;
}

/**
 * @brief Add an element on TUPLO.
 * @param a Tuplo we want to add an element.
 * @param s String to add on a[size].str .
 * @param num Number to add on a[size].num .
 * @param N pointer to help us if it is necessary to reallocate the Tuplo.
 * @param size Size of Tuplo.
 * @return 0.
 */
TUPLO *add_elem_tuplo(TUPLO *a, char *s,int num, int *N,int size)
{
    if((*N) * 30 <= size + 1) a = realloc_tuplo(a,N);
    a[size].str = strdup(s);
    a[size].num = num;
    return a;
}

/**
 * @brief Add a string on TUPLO, depending if it exists or not.
 * @param a Tuplo to add a string.
 * @param N pointer to help us if it is necessary to reallocate the Tuplo.
 * @param size Size of Tuplo.
 * @param num Number to add on a[size].num .
 */
TUPLO* add_tuplo(TUPLO *a, char *str, int *N,int size,int num, int *inc)
{
    int ind = exist_language_tuplo(a,str,size);
    if(ind != -1) a[ind].num++;
    else {
        (*inc)++;
        a = add_elem_tuplo(a,str,num,N,size);
    }
    return a;
}

/**
 * @brief Compare two elements of TUPLO, in order to sort it.
 * @param a Pointer Tuplo 1.
 * @param b Pointer Tuplo 2.
 * @return The diference between 1 and 2.
 */
static int cmpfunc_tuplo (const void *a, const void *b) {
    TUPLO *t1 = (TUPLO *) a;
    TUPLO *t2 = (TUPLO *) b;
    return (t2->num - t1->num);
}
/**
 * @brief Sort TUPLO.
 * @param a Tuplo that we want to sort.
 * @param size Size of tuplo.
 * @return 0.
 */
int sort_tuplo(TUPLO *a,int size)
{
    qsort(a,size,sizeof(struct tuplo), cmpfunc_tuplo);
    return 0;
}

/**
 * @brief Returns the number of some element of tuplo.
 * @param a Tuplo we want to get the number.
 * @param ind Index where the number is on tuplo.
 * @return THe number.
 */
static int return_tuplo_int(TUPLO *a, int ind)
{
    return(a[ind].num);
}
/**
 * @brief Returns the string of some element of tuplo.
 * @param a Tuplo we want to get the string.
 * @param ind Index where the string is on tuplo.
 * @return THe string.
 */
char *return_tuplo_str(TUPLO *a, int ind)
{
    char *aux;
    aux = a[ind].str;
    if(aux) return(strdup(aux));
    else return NULL;
}

/**
 * @brief Free all the elements of Tuplo.
 * @param a Tuplo we want to free.
 * @param size Size of tuplo.
 * @return 0.
 */ 
int free_tuplo(TUPLO *a, int size)
{
    int i;
    for(i = 0; i < size; i++) free (a[i].str);
    free (a);
    return 0;
}

/**
 * @brief Add content to a File, printing all the fields from Tuplo.
 * @param t Array Tuplo.
 * @param size Size of array tuplo.
 * @param num Top n elements to print.
 * @param File File to add content.
 * @return 0.
 */
int add_content_tuplo (TUPLO *t, int size, int num, void* File, void *query8file)
{
    FILE *newFile = (FILE *) File;
    FILE *queryfile = (FILE *) query8file;
    for(int i = 0; i < size; i++)
    {
        char *desc = return_tuplo_str(t,i);
        int id = return_tuplo_int(t,i);
        if(i < num)
            fprintf(newFile,"%s\n",desc);
        fprintf(queryfile,"%s;%d\n",desc,id);
        free(desc);
    }
    fclose(newFile);
    fclose(queryfile);
    free_tuplo(t,size);
    return 0;
}

/**
 * @brief Add content to a File, printing only 2 of the fields from Tuplo.
 * @param t Array Tuplo.
 * @param size Size of array tuplo.
 * @param num Top n elements to print.
 * @param File File to add content.
 * @return 0.
 */
int add_content_tuplo2 (TUPLO *t, int size, void* File, void *query7file)
{
    FILE *newFile = (FILE *) File;
    FILE *queryfile = (FILE *) query7file;
    for(int i = 0;i < size; i++)
    {
        int id = return_tuplo_int(t,i);
        char *desc = return_tuplo_str(t,i);
        fprintf(newFile,"%d;%s",id,desc);
        fprintf(queryfile,"%d;%s",id,desc);
        free(desc);
    }
    fclose(newFile);
    fclose(queryfile);
    free_tuplo(t,size);
    return 0;
}

/**
 * @brief Binary search for Tuplos.
 * @param t Array of Tuplo.
 * @param inf Inferior index.
 * @param sup Superior index.
 * @param id Id to search if it exist.
 * @return The index or -1 if it didn't exist.
 */
int pesquisa_bin_tuplo(TUPLO *t,int inf, int sup, int id)
{
    int meio;
    while(inf <= sup)
    {
        meio = (inf + sup)/2;
        if(id == t[meio].num) return meio;
        if(id > t[meio].num) sup = meio + 1;
        else inf = meio - 1;
    }
    return -1;
}

