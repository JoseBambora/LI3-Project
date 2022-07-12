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
 * @brief Convert a line from the file repos-g2.csv to an element of the array REPOS.
 * @param r Repo that we want to add information.
 * @param line Line that we want to convert.
 * @param size size of Repo r.
 * @return The repo converted.
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
 * @brief Convert a line from the file repos-g2.csv to an element of the array REPOS.
 * @param r Repo that we want to add information.
 * @param line Line that we want to convert.
 * @param size size of Repo r.
 * @return The repo converted.
 */
static REPO associa_linha_repo2 (char *line)
{
    REPO r;
    char *aux;
    r.id = strtol(strsep(&line,";"),&aux,10);
    r.language = strdup(strsep(&line,";"));
    r.description = strdup(strsep(&line,";"));
    return r;
}

/**
 * @brief Auxiliary function to add content from repos-g3-filter.csv to repo.csv.
 * @param r Repo with the information to add content to the File.
 * @param file File to add information.
 */
static void add_content_repo(REPO r, FILE *file)
{
    fseek(file,0,SEEK_END);
    fprintf(file,"%d;%s;%s\n",r.id,r.language,r.description);
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
 * @brief Function that will save all the information of Repo.
 * @return The size of the catalog of Repo.
 */
int start_repo ()
{
    int size = 0;
    REPO aux;
    FILE *ficheiro = fopen("entrada/repos-g3-filter.csv","r");
    FILE *repo = fopen("catalogo/repo.csv","w");
    char *line = malloc(300000 * sizeof (char));
    line = fgets(line,300000,ficheiro);
    while(fgets(line,300000,ficheiro))
    {
        aux = associa_linha_repo(line);
        add_content_repo(aux,repo);
        free_elem_repo(aux);
        size++;
    }
    fclose(ficheiro);
    fclose(repo);
    free(line);
    return (size);
}

/**
 * @brief Function that will get all the repo_ids from a certain language. Query 6.
 * @param lan Language
 * @return Integer array with all the repos_ids froma certain language.
 */
int *repo_language (char * lan)
{
    REPO r;
    FILE *repo = fopen("catalogo/repo.csv","r");
    char *line = malloc(sizeof(char) * 30000);
    int *rlan = malloc(300000* sizeof(int));
    int j = 0;
    while(fgets(line,30000,repo))
    {
        r = associa_linha_repo2(line);
        char *a = strdup(r.language);
        if(strcmp(a,lan) == 0)
        {
            rlan[j] = r.id;
            j++;
        }
        free(a);
        free_elem_repo(r);
    }
    fclose(repo);
    qsort(rlan,j,sizeof(int),compareInts);
    rlan[j] = -1;
    return rlan;
}

/**
 * @brief Function that return a Tuplo with the repos that don't have updates. Query 7.
 * @param not_updated Array with all the repos ids that don't have updates.
 * @param size_no_updated Size of the array not_updated.
 * @param size_tuplo Pointer to save the size of the final tuplo.
 * @return Final array Tuplo.
 */
void *repo_no_updates(int *not_updated, int size_no_updated, int *size_tuplo)
{
    REPO r;
    FILE *repo = fopen("catalogo/repo.csv","r");
    char *line = malloc(sizeof(char) * 30000);
    TUPLO* result = init_tuplo();
    int s = 0;
    int n = 1;
    while(fgets(line,30000,repo))
    {
        r = associa_linha_repo2(line);
        int ri = r.id;
        if(pesquisaBinaria(not_updated,ri,size_no_updated))
        {
            char *description = strdup(r.description);
            result = add_elem_tuplo(result,description,ri,&n,s);
            s++;
            free(description);
        }
        free_elem_repo(r);
    }
    fclose(repo);
    free(line);
    (*size_tuplo) = s;
    return result;
}

/**
 * @brief Gives an STRARRAY with all the language that have their REPOS the date updated_at after the DATA d.
 * @param updated Array with all the repos updated.
 * @param size_updated Size of array updated.
 * @param s Pointer to put the size of STRARRAY.
 * @return STRARRAY with the languages.
 */
static STRARRAY *repo_inf_data(int *updated, int size_updated, int*s)
{
    REPO r;
    FILE *repo = fopen("catalogo/repo.csv","r");
    char *line = malloc(sizeof(char) * 30000);
    STRARRAY *result = init_strarray();
    int size_strarray = 0, n = 1;
    while(fgets(line,30000,repo))
    {
        r = associa_linha_repo2(line);
        int ri = r.id;
        if(pesquisaBinaria(updated,ri,size_updated)) 
        {
            char *lan = strdup(r.language);
            result = add_elem_strarray(result,lan,&n,size_strarray);
            free(lan);
            size_strarray++;
        }
        free_elem_repo(r);
    }
    fclose(repo);
    free(line);
    (*s) = size_strarray;
    return result;
}

/**
 * @brief Gets an TUPLOS which has all the language and their quantity, which updated_at date of REPO is superior to a date given. Query: 8
 * @param updated Array with all the repos updated.
 * @param s Size of the array updated.
 * @return Tuplos with all the language and their quantity repos.
 */
void *repo_language_qtty(int *updated, int s,int *size_tuplos)
{
    int size_strarray = 0;
    STRARRAY *sif = repo_inf_data(updated,s,&size_strarray);
    TUPLO *as = strarray_language_qtty(sif,size_strarray,size_tuplos);
    return as;
}