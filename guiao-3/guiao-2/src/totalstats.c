#include "../include/commit.h"
#include "../include/totalstats.h"
#include "../include/user.h"
#include "../include/aux.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * \brief Struct that handles the information related to the total number of diferent fields - used in queries
 */
struct total_stats {
    int bot_ids;
    int colaboradores_total;
    int repos_total;
    int commits_total;
    int users_total;
    int *bots_array_ids;
};


/**
 * @brief  Function that initializes the TOTALSTATS struct
 * @return t -> the struct TOTALSTATS already initiliazed
 */
static TOTALSTATS init_total_stats() {
   TOTALSTATS t = malloc (sizeof(struct total_stats));
   t->colaboradores_total = 0;
   t->commits_total = 0;
   t->repos_total = 0;
   t->users_total = 0;
   t->bots_array_ids =malloc(2000* sizeof (int));
   return t;
}

/**
 * @brief  Function that starts the TOTALSTATS related catalog
 * @return ts 
 */
TOTALSTATS start_totalstats(){
    TOTALSTATS ts = init_total_stats();
    FILE *ficheiro;
    ficheiro = fopen("entrada/users-g3-filter.csv","r");
    char *line = malloc(200000 * sizeof (char));
    char *type;
    line = fgets(line,200000,ficheiro);
    int ind = 0;
    while(fgets(line,200000,ficheiro)){
        type =returnTypes_line (line);
        if (strcmp(type,"Bot")==0){
            int id1 = returnID_line(line); 
            add_elem_to_array (ts,ind,id1);
            ind++;
        }
   }
  
   qsort(ts->bots_array_ids,ind,sizeof(int),compareInts);
   add_elem_to_array(ts,ind,-1);
   fclose(ficheiro);
   free (line);
   return ts;}

/**
 * @brief  Function that returns the total of colaboradores 
 * @param ts Struct we're working on
 * @param n integer 
 * @param id the position
 * @return ts
 */
TOTALSTATS add_elem_to_array (TOTALSTATS ts,int n,int id){
    int narray= 1;
    if (narray + 1> narray *30) ts->bots_array_ids = realloc (ts->bots_array_ids,narray*sizeof (int));
    ts->bots_array_ids[n]=id;
    narray++;
    return ts;
}

/**
 * @brief Function that sets a value to colaboradores_total field of Totalstats.
 * @param t Struct we're working on
 * @param n value to set
 * @return 0.
 */
static int set_colaboradores (TOTALSTATS t, int n)
{
    t->colaboradores_total = n;
    return 0;
}
/**
 * @brief Function that sets a value to commits_total field of Totalstats.
 * @param t Struct we're working on
 * @param n value to set
 * @return 0.
 */
static int set_commits (TOTALSTATS t, int n)
{
    t->commits_total = n;
    return 0;
}
/**
 * @brief Function that sets a value to repos_total field of Totalstats.
 * @param t Struct we're working on
 * @param n value to set
 * @return 0.
 */
static int set_repos (TOTALSTATS t, int n)
{
    t->repos_total = n;
    return 0;
}

/**
 * @brief  Function that fills the users_total field within the TOTALSTATS struct
 * @param t Struct we're working on
 * @param n the number of users_total 
 * @return 0
 */
static int set_user (TOTALSTATS t, int n)
{
    t->users_total = n;
    return 0;
}

/**
 * @brief  Function that returns the total of colaboradores 
 * @param stats Struct we're working on
 * @return n -> total of colaboradores users
 */
int returnColaboradores (TOTALSTATS stats) {
    int n = stats-> colaboradores_total;
    return n;
}

/**
 * @brief  Function that returns the number of repositories 
 * @param stats Struct we're working on
 * @return n -> total of repositories
 */
int returnRepos (TOTALSTATS stats) {
    int n = stats-> repos_total;
    return n;
}

/**
 * @brief  Function that returns the number of commits made
 * @param stats Struct we're working on
 * @return n -> total of commits
 */
int returnCommits (TOTALSTATS stats) {
    //printf ("commits antes do return: %d\n",stats-> commits_total );
    int n = stats->commits_total;
    //printf ("commits do return: %d\n", n);
    return n;
}

/**
 * @brief  Function that returns the number of users_total from the stats struct
 * @param stats Struct we're working on
 * @return n -> users_total
 */
int returnUsers (TOTALSTATS stats) {
    int n = stats-> users_total;
    return n;
}

/**
 * @brief  Function that returns the number of BotsIds from the stats struct
 * @param stats Struct we're working on
 * @return n -> users_total
 */
int returnBotIds (TOTALSTATS stats){
    int n = stats->bot_ids;
    return n;
}

/**
 * @brief Function that counts the number of contributors that are bots.
 * @param ts_aux  TOTALSTATS struct
 * @return The number of bot contributors.
  */
int get_bot_ids(void *ts_aux)
{
    TOTALSTATS ts = (TOTALSTATS) ts_aux;
    int *bot = ts->bots_array_ids;
    int n = bot_repos(bot);
    free(bot); //printf("BOTS: %d\n",n);
    return n;
}

/**
 * @brief Function that sets a value to bot_ids field of Totalstats.
 * @param t Struct we're working on
 * @param n the number of users_total 
 * @return 0.
 */
static int set_bot_ids (TOTALSTATS t, int n)
{
    t->bot_ids = n;
    return 0;
}
/**
 * @brief Function that sets a value to all the fields of Totalstats.
 * @param t Struct we're working on
 * @param col colaboradores value
 * @param com commiters value
 * @param rep repositorios value
 * @param use user value
 * @param bi bots ids value
 * @return 0.
 */
int set_total_stats(TOTALSTATS t, int col, int com, int rep, int use,int bi)
{
    set_colaboradores(t,col);
   // printf ("commits: %d\n", com);
    set_commits(t,com);
    //printf ("commits_after_set: %d\n", returnCommits(t));
    set_repos(t,rep);
    set_user(t,use);
    set_bot_ids(t,bi);
    return 0;
}


/**
 * @brief Function that frees the memory blocks previously allocated for stats related elements.
 * @param t TOTALSTATS data that we want to deallocate.
 * @return 0
 */
int free_TotalStats( TOTALSTATS t)
{
        free (t);
        return 0;

}

