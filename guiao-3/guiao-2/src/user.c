#include "../include/data.h"
#include "../include/tuplo.h"
#include "../include/user.h"
#include "../include/aux.h"
#include "../include/triplo.h"
#include "../include/quadruplo.h"
#include "../include/typesstats.h"
#include "../include/totalstats.h"
#include "../include/connection.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * \brief Struct that handles all the variables within the users file
 */
struct user { 
   int id;
   char *login;
   char *type;
};


/**
 * @brief  Function that gets the field that we desire in each position of the array
 * @param line line of the file we're evaluating
 * @return u
 */
static USER associa_linha_users (char *line){
   USER u;
   u.id = atoi(strsep(&line,";"));
   u.login = strdup(strsep(&line,";"));
   u.type =  strdup(strsep(&line,";")); 
   strsep(&line,";"); 
   return u;
}

/**
 * @brief  Function that provides the necessary information to USER
 * @param u Struct we're working on
 * @param FILE file we're using
 */
static void add_content_user(USER u, FILE *file)
{
    fseek(file,0,SEEK_END);
    fprintf(file,"%d;%s;%s\n",u.id,u.login,u.type);
    free(u.login);
    free(u.type);
}


/**
 * @brief  Function that returns the ID of an given user
 * @param line given line
 * @return the id of the given user
 */
 int returnID_line (char *line) {
    int id = atoi(strsep(&line,";"));
  return id;
}

/**
 * @brief  Function that returns the login of an given user
 * @param line given line
 * @return a copy of the login of the given user
 */
static char *return_login_line (char *line) {
    strsep(&line,";");
    char *login = strsep(&line,";");
    return strdup(login);
}
/**
 * @brief  Function that type of a given user
 * @param line given line
 * @return the type of the given user
 */
 char* returnTypes_line (char *line) {
    int i = 0;
    for (; i <2 ; i++) 
        strsep (&line, ";");
    return strdup(strsep(&line,";"));
}


/**
 * @brief  Function that starts the users related catalog
 * @return the size of the file
 */
int start_user(){
    int size = 0;
    USER aux;
    FILE *user = fopen("catalogo/user.csv","w");
    FILE *ficheiro = fopen("entrada/users-g3-filter.csv","r");
    char *line = malloc(300000 * sizeof (char));
    line = fgets(line,300000,ficheiro);
    while(fgets(line,300000,ficheiro))
    {
        aux = associa_linha_users(line);
        add_content_user(aux,user);
        size++;
    }
    fclose(ficheiro);
    fclose(user);
    free (line);
    return (size);
}

/**
 * @brief Function that puts on one array Tuplo the id user and his / her own login string.
 * @param s Pointer to save the final size of tuplo.
 * @return The array tuplo.
 */
static void *get_info_tuplo(int *s)
{
    FILE *user = fopen("catalogo/user.csv","r");
    char *line = malloc(sizeof(char)*3000000);
    char *str = malloc(300000 * sizeof (char));
    TUPLO *aux = init_tuplo();
    int s_tuplo = 0;
    int n = 1;
    while(fgets(line,3000,user))
    {
        strcpy(str,line);
        int id = returnID_line(line);
        char *login = return_login_line(str);
        aux = add_elem_tuplo(aux,login,id,&n,s_tuplo);
        s_tuplo++;
    }
    sort_tuplo(aux,s_tuplo);
    (*s) = s_tuplo;
    fclose(user);
    free(line);
    free(str);
    return aux;
}

/**
 * @brief Function that completes the TRIPLO - it basically associates the login to the id
 * @param aux_triplo TRIPLO that we want to complete
 * @param s size of the triplo
 * @return t
 */
void *complete_triplo (void*aux_triplo, int s)
{
    int s_tuplo = 0;
    TRIPLO *t = (TRIPLO *) aux_triplo;
    TUPLO *aux = get_info_tuplo(&s_tuplo);
    t = complete_triplo_tuplo(t,s,aux,s_tuplo);
    free_tuplo(aux,s_tuplo);
    return t;
}

/**
 * @brief Function that completes the QUADRUPLO - it basically associates the login to the id.
 * @param aux_quadruplo QUADRUPLO that we want to complete.
 * @param s size of the quadruplo.
 * @return The array Quadruplo with the all the information.
 */
void *complete_quadruplo (void*aux_quadruplo, int s)
{
    int s_tuplo = 0;
    QUADRUPLO *t = (QUADRUPLO *) aux_quadruplo;
    TUPLO *aux = get_info_tuplo(&s_tuplo);
    t = complete_quadruplo_tuplo(t,s,aux,s_tuplo);
    free_tuplo(aux,s_tuplo);
    return t;
}