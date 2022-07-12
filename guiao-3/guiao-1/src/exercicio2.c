/**
 * @file exercicio2.c
 * @brief This file contains the functions related to exercice 2
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "../include/exercicio1.h"
#include "../include/exercicio2.h"
#include "../../guiao-2/include/aux.h"

/**
 * @brief Function that adds an element from a string separated by ';' to an array
 * @param line char
 * @param users_id integer array
 * @param n integer - size of the array
 * @return 0
 */
int add_elem_g1(char *line, int *users_ID,int n)
{
    char *strID;
    strID = strsep(&line,";");
    users_ID[n] = atoi(strID);
    return 0;
}
/**
 * @brief Function that alocates memory for an array 
 * @return array
 */
int *alocaMemArray ()
{
    int *array = malloc(300 * sizeof(int));
    return array;
}

/**
 * @brief Auxiliary function that that compares two void pointers by converting them into integer pointers
 * @return array
 */
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

/**
 * @brief Function that stores the ID from the users-ok.csv file within a parameter of our struct Array_IDS
 * @return The struct with the stored information
 */
Array_IDS getUsersId(){
    Array_IDS users_ID;
    users_ID.id_users = malloc(300 * sizeof (int));
    FILE *ficheiro; 
    ficheiro = fopen ("guiao-1/saida/users-ok.csv","r");
    if(!ficheiro) printf("Não tem users-ok.csv\n");
    char *line = malloc(2000 * sizeof (char));
    char *s = malloc(2000 * sizeof (char));
    s = fgets (line, 2000, ficheiro);
    int j = 0, num = 1;
    while (s!=NULL)
    {
        if(num * 300 < j)  
        {
            num++;
            users_ID.id_users = realloc(users_ID.id_users,num*300*sizeof(int));
        }
        s = fgets(line,2000,ficheiro);
        if (s != NULL){
            add_elem_g1(line,users_ID.id_users,j);
            j++;
        }
    }
    free(line);
    free(s);
    users_ID.userSize = j;
    fclose(ficheiro);
    return users_ID;
}

/**
 * @brief Function that stores the ID from the repos-ok.csv file within a parameter of our struct Array_IDS
 * @param idRepos Array_IDS structure
 * @return The struct with the stored information
 */
Array_IDS getRepoId(Array_IDS idRepos){
    idRepos.id_repos = malloc(300 * sizeof (int));
    FILE *ficheiro; 
    ficheiro = fopen ("guiao-1/saida/repos-ok.csv","r");
    if(!ficheiro) printf("Não tem repos-ok.csv\n");
    char *line = malloc(2000 * sizeof (char));
    char *s = malloc(2000 * sizeof (char));
    s = fgets (line, 2000, ficheiro);
    int j = 0, num = 1;
    while (s!=NULL)
    {
        if(num * 300 < j)  
        {
            num++;
            idRepos.id_repos = realloc(idRepos.id_repos,num*300*sizeof(int));
        }
        s = fgets(line,2000,ficheiro);
        add_elem_g1(line,idRepos.id_repos,j);
        j++;
    }
    free(line);
    free(s);
    idRepos.repoSize = j;
    fclose(ficheiro);
    return idRepos;
}

/**
 * @brief Funtion that gets the n parameter separated by ";" in a given string
 * @param line char
 * @param n integer
 * @return The element on the desired position
 */
char *getNElement(char *line, int n){
    int count = 0;
    while (count < n-1)
    {
        if (*line == ';') count ++;
        line++;
    }
    char *r;
    r = strsep(&line,";");
    return r;
}

/**
 * @brief Function that validates if a line from the commits-ok.csv file must be included on commits-final.csv
 * @param line string
 * @param aux string
 * @param arrayID Array_IDS structure
 */
int verifyIDLine(char *line, char *aux, Array_IDS arrayID){
    char *r1,*r2,*r3;
    r1 = getNElement(line,1);
    strcpy(line,aux);
    r2 = getNElement(line,2);
    strcpy(line,aux);
    r3 = getNElement(line,3);
    int repo_id = atoi(r1);
    int author_id = atoi(r2);
    int commiter_id = atoi(r3);
    int r = pesquisaBinaria(arrayID.id_users,author_id,arrayID.userSize);
    if(r == 1 && author_id != commiter_id) r = pesquisaBinaria(arrayID.id_users,commiter_id,arrayID.userSize);
    if(r == 1) r = pesquisaBinaria(arrayID.id_repos,repo_id,arrayID.repoSize);
    return r;
}


/**
 * @brief Function that validates if a line from the repos-ok.csv file must be included on repos-final.csv
 * @param line string
 * @param reposID Array_IDS structure
 */
int verifyRepoIDLine(char *line,Array_IDS reposID){
    if (line == NULL) return 0;
    int repo_id = atoi(getNElement(line, 2));
    int r = pesquisaBinaria(reposID.id_users,repo_id,reposID.userSize);
    return r;
}

/**
 * @brief Function that checks if the repo from a line on repos-ok.csv has commits on commits-ok.csv
 * @param line string
 * @param commitsID Array_IDS structure
 * @return 1 if the repo has commits 0 if not
 */
int verifyCommitIDLine(char *line,Array_IDS commitsID){
    if (line == NULL) return 0;
    int commit_id = atoi(strsep(&line,";"));
    int r = pesquisaBinaria(commitsID.id_commits,commit_id,commitsID.commitSize);
    return r;
}

/**
 * @brief Function that analyses if a line on repos-ok.csv is valid
 * @param line string
 * @param usersID Array_IDS structure
 * @param line2 sring
 * @return 1 if the line is valid 0 otherwise
 */
int analyseLineRepo (char* line, Array_IDS usersID, char* line2){
    if (line == NULL) return 0;
    int r;
    r = verifyRepoIDLine(line,usersID);
    if(r == 1) r = verifyCommitIDLine(line2,usersID);
    return r;
}

/**
 * @brief Function that filters the entire repos-ok.csv into repos-final.csv
 * @param usersID Array_IDS structure
 * @return 0
 */
int verifyRepoID(Array_IDS usersID){
    FILE *ficheiro, *newFile; 
    ficheiro = fopen("guiao-1/saida/repos-ok.csv","r");
    if(!ficheiro) printf("Não tem repos-ok.csv\n");
    newFile = fopen ("entrada/repos-g3-filter.csv","w");
    char *line = malloc(2000 * sizeof (char));
    char *line2 = malloc(2000 * sizeof (char));
    char *s = malloc(2000 * sizeof (char));
    s = fgets (line, 2000, ficheiro);
    fputs(s,newFile);
    int val = 1;
    while (s != NULL)
    {
        s = fgets(line,2000,ficheiro);
        if(s!= NULL)
        {
            strcpy(line2,s);
            val = analyseLineRepo(s,usersID, line);
            if (val==1) fputs(line2,newFile);   
        }
    
    }
    free(line);
    free(line2);
    free(s);
    fclose(ficheiro);
    fclose(newFile);
    return 0;
}

/**
 * @brief Function that filters the entire commits-ok.csv into commits-final.csv
 * @param usersID Array_IDS structure
 * @return usersID Array_IDS structure after filtering
 */
Array_IDS verifyCommitID(Array_IDS usersID){
    FILE *ficheiro, *ficheiroFinal; 
    ficheiro = fopen ("guiao-1/saida/commits-ok.csv","r");
    if(!ficheiro) printf("Não tem commits-ok.csv\n");
    ficheiroFinal = fopen("entrada/commits-g3-filter.csv","w");
    int r;
    char *line = malloc(2000 * sizeof (char));
    char *line2 = malloc(2000 * sizeof (char));
    char *s = malloc(2000 * sizeof (char));
    s = fgets (line, 2000, ficheiro); 
    fputs(line,ficheiroFinal);
    int i = 0, n = 1;
    usersID.id_commits = alocaMemArray();
    while (s != NULL){
        s = fgets (line, 2000, ficheiro);
        if(s!= NULL)
        {
            strcpy(line2,line);
            r = verifyIDLine(line,line2,usersID);
            if (r == 1) 
            {
                fputs(line2,ficheiroFinal);
                if(i >= n) 
                {
                    usersID.id_commits = realloc(usersID.id_commits,n*300*sizeof(int));
                    n++;
                }
                add_elem_g1(line2,usersID.id_commits,i);
                i++;
            }
        }
    }
    usersID.commitSize = i;
    free(line);
    free(line2);
    free(s);
    fclose(ficheiro);
    fclose(ficheiroFinal);
    return usersID;
}

/**
 * @brief Function that copies users-ok.csv file into users-final.ok
 * @return 0 
 */
int usersFinal(){
    FILE *ficheiro, *ficheiroFinal; 
    ficheiro = fopen ("guiao-1/saida/users-ok.csv","r");
    if(!ficheiro) printf("Não tem users-ok.csv\n");
    ficheiroFinal = fopen("entrada/users-g3-filter.csv","w");
    char *line = malloc(2000 * sizeof (char));
    line = fgets (line, 2000,ficheiro);
    fputs(line,ficheiroFinal);
    while (line != NULL){
        line = fgets (line, 2000, ficheiro);
        if(line!= NULL) fputs(line,ficheiroFinal);
    }
    fclose(ficheiro);
    fclose(ficheiroFinal);
    return 0;
}

/**
 * @brief Function that activates the other functions of the second exercise
 * @return 0
 */
int ex2(){
    Array_IDS arrayID = getUsersId();
    qsort(arrayID.id_users,arrayID.userSize,sizeof(int),cmpfunc);
    arrayID = getRepoId(arrayID);
    qsort(arrayID.id_repos,arrayID.repoSize,sizeof(int),cmpfunc);
    arrayID = verifyCommitID(arrayID);
    qsort(arrayID.id_commits,arrayID.commitSize,sizeof(int),cmpfunc);
    verifyRepoID(arrayID);
    free(arrayID.id_commits);
    free(arrayID.id_repos);
    free(arrayID.id_users);
    usersFinal();
    return 0;
}
