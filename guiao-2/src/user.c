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
   unsigned short int followers; // since it never goes below 0
   int *followers_list;
   unsigned short int following; // since it never goes below 0
   int *following_list; 
   unsigned short int public_gists; // since it never goes below 0
   unsigned short int public_repos; // since it never goes below 0
};

/**
 * @brief  Function that initializes the USER struct
 * @return u -> the struct USER already initiliazed
 */
USER *init_users(){
   USER *u = malloc(30 * sizeof(struct user));
   return u;
}

/**
 * @brief  Function that resizes the block of memory earlier allocated for the array
 * @param s struct that we're working on
 * @param n integer that we're using in order to help increase the memory allocated for this struct
 * @return the array with the block of memory on the heap already allocated for it.
 */
USER *realloc_users(USER *s, int *n){
   (*n)++;
   s = realloc (s, 30  * (*n)* sizeof(struct user));
   return s;
}

/**
 * @brief  Function that gets the field that we desire in each position of the array
 * @param line line of the file we're evaluating
 * @return 0
 */
static USER associa_linha_users (char *line){
   USER u;
   u.id = atoi(strsep(&line,";"));
   u.login = strdup(strsep(&line,";"));
   u.type =  strdup(strsep(&line,";")); 
   strsep(&line,";");
   u.followers = ( unsigned short int) atoi(strsep(&line,";"));
   u.followers_list = str_array(strsep(&line,";"),u.followers); 
   u.following = ( unsigned short int)atoi(strsep(&line,";"));
   u.following_list = str_array(strsep(&line,";"),u.following); 
   return u;
}

/**
 * @brief  Function that sets the value of each field
 * @param u Struct we're working on
 * @param size size of the user 
 * @param line line of the file we're evaluating
 * @return u -> USER already filled
 */
static USER *set_value_user(USER *u, int *size, char *line)
{
    u[*size] = associa_linha_users(line);
    (*size)++;
    return u;
}
/**
 * @brief  Function that returns the total followers of an given user
 * @param u Struct we're working on
 * @param ind position within the array
 * @return the total followers of the given user
 */
static int return_followers(USER *u,int ind)
{
    int followers = u[ind].followers;
    return followers;
}


/**
 * @brief  Function that returns the total of following of an given user
 * @param u Struct we're working on
 * @param ind position within the array
 * @return the number of those who the given user follows
 */
static int return_following(USER *u,int ind)
{
    int following = u[ind].following;
    return following;
}

/**
 * @brief  Function that returns the array with the ids of those who the given user follows
 * @param u Struct we're working on
 * @param i position within the array
 * @return the array
 */
static int* return_following_list (USER *u, int i) {
    int asize = u[i].following;
    int *a= malloc(sizeof(int)*asize);
    copyArray(u[i].following_list, asize-1);
    return a;
}

/**
 * @brief  Function that returns the array with the ids of those who follow the given user 
 * @param u Struct we're working on
 * @param i position within the array
 * @return the array
 */
static int* return_followers_list (USER *u, int i) {
    int asize = u[i].followers;
    int *a= malloc(sizeof(int)*asize);
    copyArray(u[i].following_list, asize);
    return a;
}

/**
 * @brief  Function that returns the ID of an given user
 * @param c Struct we're working on
 * @param i position within the array
 * @return the id of the given user
 */
static int returnID (USER *c, int i) {
    int id = c[i].id;
    return id;
}
/**
 * @brief  Function that returns the TYPE of an given user
 * @param c Struct we're working on
 * @param i position within the array
 * @return the type of the given user
 */
char* returnTypes (USER *c, int i) {
    char* type = strdup(c[i].type);
    return type;
}

/**
 * @brief  Function that starts the Array_Users with its elements
 * @param s size
 * @param u_aux UTYPESTATS struct we're filling with info from the file
 * @param uc_aux CONNECTION struct we're filling with info from the file
 * @param ts_aux TOTALSTATS struct we're filling with info from the file
 * @param connection_size size of the CONNECTION struct
 */
USER *start_user(int *s, void *u_aux, void *uc_aux, void *ts_aux, int *connection_size){
    UTYPESTATS ut = (UTYPESTATS) u_aux;
    USER*u = init_users();
    CONNECTION *uc = (CONNECTION*) uc_aux; 
    TOTALSTATS ts = (TOTALSTATS) ts_aux;
    FILE *ficheiro;
    ficheiro = fopen("entrada/users-g2.csv","r");
    char *line = malloc(200000 * sizeof (char));
    char *type;
    int amigossize;
    int id;
    line = fgets(line,200000,ficheiro);
    int size = 0, n = 1,n2=1;
    int sc = 0;
    int ind = 0;
    while(fgets(line,200000,ficheiro)){
        if (size + 1> n *30) u = realloc_users(u,&n);
        u = set_value_user(u,&size,line);
        amigossize = (return_followers(u,size-1) + return_following(u,size-1));
        if (amigossize > 0) {
            int elemsize =0;
            int *amigos = malloc (sizeof(int)*amigossize);
            amigos= concatena_arrays( return_followers_list(u,size-1), u[size-1].followers, return_following_list(u,size-1),u[size-1].following);
            id = returnID(u,size-1);
            uc = add_elem_Connection(uc,id,amigos,amigossize,sc,&n2);
            elemsize++;}
        type =returnTypes(u,size-1);
        if (strcmp(type,"Bot")==0)
        {
            incrementaTypes(ut,0);
            int id1 = returnID(u,size-1); 
            add_elem_to_array (ts,ind,id1);
            ind++;
        }
        else if (strcmp(type,"Organization")==0) incrementaTypes(ut,1);
        else if (strcmp(type,"User")==0) incrementaTypes(ut,2);
   }
   add_elem_to_array(ts,ind,-1);
   fclose(ficheiro);
   free (line);
   (*s) = size;
   (*connection_size) = sc;
   return u;
}


/**
 * @brief  Function that returns the LOGIN of an given user
 * @param c Struct we're working on
 * @param i position within the array
 * @return the login of the given user
 */
char* returnLogin (USER *c, int i) {
    char* login = strdup(c[i].login);
    return login;
}

/**
 * @brief Function that frees all the pointer's from an element of user.
 * @param u User element that we want to free.
 * @return 0
 */
static int free_elem_user (USER u)
{
    free(u.login);
    free(u.type);
    free(u.followers_list);
    free(u.following_list);
    //free_data(u.created_at);
    return 0;
}

/**
 * @brief Function that frees the memory blocks previously allocated for user's elements.
 * @param u User that we want to free.
 * @param size total size
 * @return 0
 */
int free_user(USER *u, int size)
{
    int i;
    for(i = 0; i < size; i++)
        free_elem_user(u[i]);
    free(u);
    return 0;
}

/**
 * @brief Function that returns the diference between 2 ids of 2 pointer users
 * @param aux_u1 User 1
 * @param aux_u2 User 2
 * @return r -> the diference between 2 ids of 2 pointer users
 */
static int cmpusers(const void *aux_u1, const void *aux_u2)
{
    USER *u1 = (USER *) aux_u1;
    USER *u2 = (USER *) aux_u2;
    int r = u1->id - u2->id;
    return(r);
}

/**
 * @brief Function that sorts the struct user using the quickSort algorithm 
 * @param u given user array 
 * @param size size of user array
 * @return 0
 */
int sort_user(USER *u,int size)
{
    qsort(u,size,sizeof(struct user),cmpusers);
    return 0;
}

/**
 * @brief Function that sorts by using binary search
 * @param u given user
 * @param inf inferior limit
 * @param sup  superior limit
 * @param id  given user id
 * @return 0
 */
static int  pesbin_id (USER *u, int inf, int sup, int id)
{
    int meio;
    while(inf <= sup)
    {
        meio = (inf + sup)/2;
        if(id == u[meio].id) return meio;
        if(id > u[meio].id) inf = meio + 1;
        else sup = meio - 1;
    }
    return -1;
}

/**
 * @brief Function that completes the TRIPLO - it basically associates the login to the id
 * @param u given user
 * @param size size of the user
 * @param aux_triplo TRIPLO that we want to complete
 * @param s size of the triplo
 * @return 0
 */
void *complete_triplo (USER *u, int size, void*aux_triplo, int s)
{
    TRIPLO *t = (TRIPLO *) aux_triplo;
    int i;
    for(i = 0; i < s; i++)
    {
        int id = return_id_triplo(t,i);
        int ind = pesbin_id(u,0,size-1,id);
        if(ind!= -1) {
            char *login = returnLogin(u,ind);
            set_str_triplo(t,i,login);
            free(login);
        }
    }
    return t;
}

/**
 * @brief Function that completes the QUADRUPLO - it basically associates the login to the id
 * @param u given user
 * @param size size of the user
 * @param aux_quadruplo QUADRUPLO that we want to complete
 * @param s size of the quadruplo
 * @return 0
 */
void *complete_quadruplo (USER *u, int size, void*aux_quadruplo, int s)
{
    QUADRUPLO *t = (QUADRUPLO *) aux_quadruplo;
    int i;
    for(i = 0; i < s; i++)
    {
        int id = return_id_quadruplo(t,i);
        int ind = pesbin_id(u,0,size-1,id);
        if(ind!= -1) {
            char *login = returnLogin(u,ind);
            set_str_quadruplo(t,i,login);
            free(login);
        }
    }
    return t;
}