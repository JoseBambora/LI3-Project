#include "../include/repo.h"
#include "../include/aux.h"
#include "../include/tuplo.h"
#include "../include/stringarray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @struct Struct used to store information from one repo
 */
struct repo {
    int id;
    char *description;
    char *language;
};

/**
 * @brief Allocate memory to array REPOS.
 * @return Repo allocated.
 */
REPO *init_repo()
{
    REPO *r = malloc(30 * sizeof(struct repo));
    return r;
}

/**
 * @brief Reallocate memory to array REPOS.
 * @param r Repo that we want to reallocate.
 * @param n Pointer that has a number that will define the size of REPO result memory.
 * @return Repo reallocated.
 */
static REPO *realloc_repo(REPO *r, int *n)
{
    (*n)++;
    r = realloc(r, 30 * (*n) * sizeof(struct repo));
    return r;
}

/**
 * @brief Convert a line from the file repos-g2.csv to an element of the array REPOS.
 * @param r Repo that we want to add information.
 * @param line Line that we want to convert.
 * @param size size of Repo r.
 * @return 0.
 */
static REPO associa_linha_repo (char *line)
{
    REPO r;
    char *aux;
    r.id = strtol(strsep(&line,";"),&aux,10);
    strsep(&line,";");
    strsep(&line,";");
    strsep(&line,";");
    strsep(&line,";");
    r.description = strdup(strsep(&line,";"));
    r.language = strdup(strsep(&line,";"));
    return r;
}

/**
 * @brief Function that set a value on the last element of arry Repo.
 * @param size Pointer to the real size of array Repo.
 * @param line Line with all the information.
 * @return Array Repo after the addition.
 */
static REPO *set_value_repo(REPO *r, int *size, char *line)
{
    r[*size] = associa_linha_repo(line);
    (*size)++;
    return r;
}
/**
 * @brief Function that will save all the information.
 * @param s pointer to save the size of Repo Array.
 * @return Repo array.
 */
REPO *start_repo (int *s)
{
    REPO* r = init_repo();
    FILE *ficheiro = fopen("entrada/repos-g2.csv","r");
    char *line = malloc(300000 * sizeof (char));
    line = fgets(line,300000,ficheiro);
    int size = 0, n = 1;
    while(fgets(line,300000,ficheiro))
    {
        if(size + 1 > n * 30) r = realloc_repo(r,&n);
        r = set_value_repo(r,&size,line);
    }
    fclose(ficheiro);
    free(line);
    (*s) = size;
    return r;
}

/**
 * @brief Gets the string language from repo.
 * @param r Repos that we want to get the language.
 * @param ind The location of the Repo that we want to get the string.
 * @return The language of repo[ind].
 */
static char *return_language (REPO *r, int ind)
{
    char *lan = strdup(r[ind].language);
    return lan;
}

/**
 * @brief Gets the integer id from repo.
 * @param r Repos that we want to get is own id.
 * @param ind The location of the Repo that we want to get the id.
 * @return The id of repo[ind].
 */
static int return_repo(REPO *r,int ind)
{
    int repo_id = r[ind].id;
    return repo_id;
}

/**
 * @brief Gets the string description from repo.
 * @param r Repos that we want to get the description.
 * @param ind The location of the Repo that we want to get the string.
 * @return The description of repo[ind].
 */
static char *return_desc(REPO *r,int ind)
{
    char *desc = strdup(r[ind].description);
    return desc;
}

/**
 * @brief Function that free all the pointer from 1 element of repo.
 * @param r Repo element that we want to free.
 * @return 0.
 */
static int free_elem_repo (REPO r)
{
    free(r.description);
    free(r.language);
    return 0;
}

/**
 * @brief Function that free repo.
 * @param r Repo that we want to free.
 * @return 0.
 */
int free_repo(REPO *r, int size)
{
    int i;
    for(i = 0; i < size; i++)
        free_elem_repo(r[i]);
    free(r);
    return 0;
}

/**
 * @brief Function that calculates the diference between two datas of 2 pointers of REPO, in order
 *        to sort it
 * @param r1_aux Pointer 1.
 * @param r2_aux Pointer 2.
 * @return The difference.
 */
static int compare_repo(const void *r1_aux,const void *r2_aux)
{
    REPO *r1 = (REPO *) r1_aux;
    REPO *r2 = (REPO *) r2_aux;
    int r = r2->id - r1->id;
    return (r);
}

/**
 * @brief Function that sort a REPO array, based the repo id
 * @param r Array Repo we want to sort.
 * @param size Size of array.
 */
int sort_repo(REPO *r, int size)
{
    qsort(r,size,sizeof(struct repo),compare_repo);
    return 0;
}

/**
 * @brief Function that will get all the repo_ids from a certain language. Query 6.
 * @param r Array repo.
 * @param size Size of the array Repo.
 * @param lan Language
 * @return Integer array with all the repos_ids froma certain language.
 */
int *repo_language (REPO *r,int size, char * lan)
{
    int *rlan = malloc((size + 1)* sizeof(int));
    int i, j = 0;
    for(i = 0; i < size; i++)
    {
        char *l = return_language(r,i);
        if(strcmp(l,lan) == 0)
        {
            rlan[j] = return_repo(r,i);
            j++;
        }
        free(l);
    }
    qsort(rlan,j,sizeof(int),compareInts);
    rlan[j] = -1;
    return rlan;
}

/**
 * @brief Function that return a Tuplo with the repos that don't have updates. Query 7.
 * @param r Array Repo.
 * @param size Size of the array Repo.
 * @param not_updated Array with all the repos ids that don't have updates.
 * @param size_no_updated Size of the array not_updated.
 * @param size_tuplo Pointer to save the size of the final tuplo.
 * @return Final array Tuplo.
 */
void *repo_no_updates(REPO *r, int size,int *not_updated, int size_no_updated, int *size_tuplo)
{
    TUPLO* result = init_tuplo();
    int s = 0;
    int i, n = 1;
    for(i = 0; i < size; i++)
    {
        int ri = return_repo(r,i);
        if(pesquisaBinaria(not_updated,ri,size_no_updated))
        {
            char *description = return_desc(r,i);
            result = add_elem_tuplo(result,description,ri,&n,s);
            s++;
            free(description);
        }
    }
    (*size_tuplo) = s;
    return result;
}

/**
 * @brief Gives an STRARRAY with all the language that have their REPOS the date updated_at after the DATA d.
 * @param r Array Repo that we want to filter.
 * @param size Repos size.
 * @param updated Array with all the repos updated.
 * @param size_updated Size of array updated.
 * @param s Pointer to put the size of STRARRAY.
 * @return STRARRAY with the languages.
 */
static STRARRAY *repo_inf_data(REPO *r, int size, int *updated, int size_updated, int*s)
{
    STRARRAY *result = init_strarray();
    int i, size_strarray = 0, n = 1;
    for(i = 0; i < size; i++)
    {
        int ri = return_repo(r,i);
        if(pesquisaBinaria(updated,ri,size_updated)) 
        {
            char *lan = return_language(r,i);
            result = add_elem_strarray(result,lan,&n,size_strarray);
            free(lan);
            size_strarray++;
        }
    }
    (*s) = size_strarray;
    return result;
}

/**
 * @brief Gets an TUPLOS which has all the language and their quantity, which updated_at date of REPO is superior to a date given. Query: 8
 * @param r Original array Repo.
 * @param size Size of Array of Repo.
 * @param updated Array with all the repos updated.
 * @param s Size of the array updated.
 * @return Tuplos with all the language and their quantity repos.
 */
void *repo_language_qtty(REPO *r,int size, int *updated, int s,int *size_tuplos)
{
    int size_strarray = 0;
    STRARRAY *sif = repo_inf_data(r,size,updated,s,&size_strarray);
    TUPLO *as = strarray_language_qtty(sif,size_strarray,size_tuplos);
    return as;
}