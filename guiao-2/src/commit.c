#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/commit.h"
#include "../include/data.h"
#include "../include/aux.h"
#include "../include/triplo.h"
#include "../include/quadruplo.h"
#include "../include/abin.h"
#include "../include/connection.h"

/**
 * @struct Struct used to store information from one commit
 */
struct commit {
   int repoId;
   int authorId;
   int commiterId;
   DATA data;
   unsigned short int lenmessage;
};

/**
 * @brief Function that initializes the array of COMMIT elements
 * @return The array initialized with memory for 30 elements
 */
COMMIT *init_commits(){
   COMMIT *c = malloc(30*sizeof(struct commit));
   return c;
}

/**
 * @brief Function that resizes the block of memory earlier allocated for the array of COMMIT elements
 * @param c Array of COMMIT elements
 * @param n Reallocation buffer
 * @return The array with resized memory on the heap already allocated for it
 */
COMMIT *realloc_commits(COMMIT *c, int *n){
   (*n)++;
   c = realloc (c, (*n) * 30 * sizeof(struct commit));
   return c;
}

/**
 * @brief Function that converts a line from the file "commits-g2.csv" to an element of the array of COMMIT elements
 * @param line line of the file we're evaluating
 * @return COMMIT struct with the information from the line in "commits-g2.csv"
 */
static COMMIT associa_linha_commit (char *line){
   COMMIT c;
   c.repoId = atoi(strsep(&line,";"));
   c.commiterId = atoi(strsep(&line,";"));
   c.authorId = atoi(strsep(&line,";"));
   c.data = string_to_data(strsep(&line, ";"));
   c.lenmessage = strlen(line);
   return c;
}

/**
 * @brief Function that sets the value on the last element of the array of COMMIT elements
 * @param c Array of COMMIT elements
 * @param size Pointer to the real size of the array of COMMIT elements
 * @param line Line with all the information
 * @return Array of COMMIT elements after adding an element to it 
 */
static COMMIT *set_value_commit(COMMIT *c, int *size, char *line){
   c[*size] = associa_linha_commit(line);
   (*size)++;
    return c;
}

/**
 * @brief Function that saves all the information regarding commits into a collection of commits (in our case an array of COMMIT elements)
 * @param s Pointer to save the real size of the array of COMMIT elements
 * @return An array of COMMIT elements with all the information stored on it
 */
COMMIT *start_commits(int *s){
   COMMIT *c = init_commits();
   FILE *ficheiro = fopen("entrada/commits-g2.csv","r");
   char *line = malloc(3000 * sizeof (char));
   line = fgets(line,3000,ficheiro);
   int size = 0, n = 1;
   while(fgets(line,3000,ficheiro)){
      if (size+1 > n *30) c = realloc_commits(c,&n);
         c = set_value_commit(c,&size,line);
   }
   fclose(ficheiro);
   free(line);
   (*s) = size;
   //printf("%d\n",size);
   return c;
}
/**
 * @brief Function that returns a commit's authorId
 * @param c Array of COMMIT elements
 * @param ind Position of the commit
 * @return The authorId of the commit
 */
static int return_author_id (COMMIT *c, int ind){
   return c[ind].authorId;
}

/**
 * @brief Function that returns a commit's authorId
 * @param c Array of COMMIT elements
 * @param ind Position of the commit
 * @return The authorId of the commit
 */
static int return_commiter_id (COMMIT *c, int ind){
   return c[ind].commiterId;
}

/**
 * @brief Function that returns a commit's repoId
 * @param c Array of COMMIT elements
 * @param ind Position of the commit
 * @return The repoId of the commit
 */
static int return_repo_id (COMMIT *c, int ind){
   return c[ind].repoId;
}

/**
 * @brief Funtion that returns the date field of an index a COMMIT array
 * @param c Array of COMMIT elements
 * @param ind Position of the commit
 * @return Void pointer that represents a copy of the date field of the commit
 */
static void *return_data(COMMIT *c, int ind){
   return copy_data(c[ind].data);
}

/**
 * @brief Function that compares the dates of two commits
 * @param c1_aux Void pointer that represents a commit
 * @param c2_aux Void pointer that represents a commit
 * @return the result of comparing the two dates
 */
static int compare_datas_commit(const void *c1_aux,const void *c2_aux)
{
    COMMIT *c1 = (COMMIT *) c1_aux;
    COMMIT *c2 = (COMMIT *) c2_aux;
    int r = cmpfuncdatas(c1->data,c2->data);
    return (r);
}

/**
 * @brief Function that sorts a the array of COMMIT elements based on commit dates
 * @param c Array of COMMIT elements
 * @param size size of the array of COMMIT elements
 * @return 0
 */
int sort_commit(COMMIT *c, int size)
{
    qsort(c,size,sizeof(struct commit),compare_datas_commit);
    return 0;
}

/**
 * @brief Function that returns the position on the array of COMMIT elements where an id exists
 * @param c Array of COMMIT elements
 * @param size Size of the array 
 * @param id Id we are searching for
 * @return The position on the COMMIT array where a given id exists, -1 if doesn't exist
 */
int return_ind_id (COMMIT *c, int size, int id)
{
   int i;
   for(i= 0 ; i < size; i++)
   {
      if(c[i].commiterId == id) return i;
   }
   return -1;
}

/**
 * @brief Function that frees the memory alocated to a COMMIT
 * @param c COMMIT struct
 * @return 0
 */
static int free_elem_commit (COMMIT c)
{
    free_data(c.data);
    return 0;
}

/**
 * @brief Function that frees memory allocated for the Array of COMMIT elements
 * @param c rray of COMMIT elements
 * @param size Size of the commit array
 * @return 0
 */
int free_commit(COMMIT *c, int size)
{
    int i;
    for(i = 0; i < size; i++)
        free_elem_commit(c[i]);
    free(c);
    return 0;
}

/**
 * @brief Function that compares two commits based on the size of their commit message
 * @param c1_aux Void pointer that represents a commit
 * @param c2_aux Void pointer that represents a commit
 * @return The result of comparing the size of the messages of the two commits
 */
static int compare_commit(const void *c1_aux,const void *c2_aux)
{
   COMMIT *c1 = (COMMIT *) c1_aux;
   COMMIT *c2 = (COMMIT *) c2_aux;
   int r = c2->lenmessage - c1->lenmessage;
   return (r);
}

/**
 * @brief Function that sorts an array of commits based on the size of commit messages
 * @param c Array of COMMIT elements
 * @param size Size of the COMMIT array
 * @return 0
 */
int sort_commit2(COMMIT *c, int size)
{
   qsort(c,size,sizeof(struct commit),compare_commit);
   return 0;
}

/**
 * @brief Function that returns the size of the message of an element in a given position of an array of COMMIT elements
 * @param c Array of COMMIT elements
 * @param ind Position of the commit in the array of COMMIT elements
 * @return The size of the message of the element in the given position
 */
static int return_message_size(COMMIT *c,int ind)
{
   return (c[ind].lenmessage);
}

/**
 * @brief Alternate function that creates a QUADRUPLO array
 * @param c Array of COMMIT elements
 * @param size Size of the COMMIT array
 * @param s Pointer that represents the size of the Quadruplo
 * @return Void pointer that represents a QUADRUPLO struct
 */
void *commit_quadruplo(COMMIT *c,int size, int *s)
{
   QUADRUPLO *t = init_quadruplo();
   int i, n = 1;
   BTREE tree = NULL;
   int cm_s = 0;
   for(i = 0; i < size; i++)
   {
      int ri = return_repo_id(c,i);
      if(exist_elem(tree,ri) == 0)
      {
         t = add_elem_quadruplo(t,return_commiter_id(c,i),"",return_message_size(c,i),cm_s,&n,ri); 
         tree = add_elem(tree,ri);
         cm_s++;
      }
   }
   free_btree(tree);
   (*s) = cm_s;
   return t;
}

/**
 * @brief Function that calculates the number of repos with commits made by bots
 * @param c Array of COMMIT elements
 * @param bot_ids integer array containing all the ids belonging to bots
 * @param s Pointer to the real size of the array of COMMIT elements
 * @return j, a variable that stores the amount of repos with commits made by bots
 */
int bot_repos(COMMIT *c, int *bot_ids,int size_commits)
{
   int size = size_array(bot_ids);
   int i, j = 0,ai,ci,ri;
   BTREE tree = NULL;
   for(i = 0; i< size_commits; i++)
   {
      ai = return_author_id(c,i);
      ci = return_commiter_id(c,i);
      ri = return_repo_id(c,i);
      if (exist_elem(tree,ri) == 0)
      {
         if (pesquisaBinaria(bot_ids,ai,size)) {
            tree = add_elem(tree,ri);
            j++;
         }
         else if (pesquisaBinaria(bot_ids,ci,size)) {
            tree = add_elem(tree,ri);
            j++;
         }
      }
   }
   free_btree(tree);
   return j;
}

/**
 * @brief Function that returns the number of colaborators
 * @param c Array of COMMIT elements
 * @param size Size of the COMMIT array
 * @return The number of colaborators
 */
int return_colaborators (COMMIT *c,int size){
   int ci, ai, s = 0;
   BTREE treeci = NULL;
   BTREE treeai = NULL;
   for(int i = 0; i < size ; i++){
      ci = return_commiter_id(c,i);
      ai = return_author_id(c,i);
      if (exist_elem(treeci,ci) == 0)  {
         treeci = add_elem(treeci,ci);
         s++;
      }
      else if (exist_elem(treeai,ai) == 0) {
         treeai = add_elem(treeai,ai);
         s++;
      }
   }
   //printf("COLABORATORS: %d\n",s);
   free_btree(treeai);
   free_btree(treeci);
   return s;
}

/**
 * @brief Function that returns the quantity of commits made by one commiter in a date range
 * @param liminf minimum date
 * @param limsup maximum date
 * @param c Array of COMMIT elements
 * @param size Size of the COMMIT array
 * @param size_triplo Pointer to the real size of the TRIPLO array
 * @return TRIPLO struct array with updated information represented as a void pointer
 */
void *commits_qtty(void *liminf, void* limsup, COMMIT *c, int size,int *size_triplo)
{
   TRIPLO * t = init_triplo();
   int i, n = 1;
   BTREE tree = NULL;
   int s = 0;
   for(i = 0; i < size; i++)
   {
      DATA aux = return_data(c,i);
      if(dif_anos(liminf,aux) && dif_anos(aux,limsup))
      {
         int id = return_commiter_id(c,i);
         if(exist_elem(tree,id) == 0)
         {
            t = add_elem_triplo(t,id,"",1,s,&n);
            tree = add_elem(tree,id);
            s++;
         }
         else
         {
            inc_qtty(t,s,id);
         }
      }
      free_data(aux);
   }
   *size_triplo = s;
   free_btree(tree);
   sort_triplo(t,s);
   return t;
}

/**
 * @brief Function that creates an array of TRIPLO elements with information needed for query 6
 * @param c Array of COMMIT elements
 * @param size Size of the COMMIT array
 * @param repos_ids Integer array with all the repo ids 
 * @param size_triplo Pointer to the real size of the TRIPLO array
 * @return void pointer that represents the TRIPLOS
 */
void *commiter_id_repos(COMMIT *c, int size, int *repos_ids, int *size_triplo)
{
   TRIPLO * t = init_triplo();
   int i;
   int s = size_array(repos_ids);
   int n = 1;
   int st = 0;
   BTREE tree = NULL;
   for(i = 0; i < size; i++)
   {
      if(pesquisaBinaria(repos_ids,return_repo_id(c,i),s))
      {
         int id = return_commiter_id(c,i);
         if(exist_elem(tree,id) == 0)
         {
            t = add_elem_triplo(t,id,"",1,st,&n);
            tree = add_elem(tree,id);
            st++;
         }
         else
         {
            inc_qtty(t,st,id);
         }
      }
   }
   *size_triplo = st;
   sort_triplo(t,st);
   free_btree(tree);
   return t;
}

/**
 * @brief Function that inserts into an array all the repos that are not updated after a certain date
 * @param c Array of COMMIT elements
 * @param size Size of the COMMIT array
 * @param d_aux Date
 * @param s Integer pointer that points to the size of the array
 * @return Array with all the not updated repos
 */
int * not_updated_repos (COMMIT *c, int size, char *d_aux, int *s){
   DATA d = string_to_ano(d_aux);
   BTREE tree = NULL;
   int *not_updated = malloc(sizeof(int)*size);
   int j = 0;
   for(int i = 0; i< size ;i++){
      DATA aux = return_data(c,i);
      int ri = return_repo_id(c,i);
      if (dif_anos(aux,d)&& exist_elem(tree,ri) == 0){
         not_updated[j] = ri;
         tree = add_elem(tree,ri);
         j++;
      }
   }
   *s = j;
   free_btree(tree);
   qsort(not_updated,j,sizeof(int),compareInts);
   return not_updated;
}

/**
 * @brief Function that inserts into an array all the repos that are updated after a certain date
 * @param c Array of COMMIT elements
 * @param size Size of the COMMIT array
 * @param d_aux Date
 * @param s Integer pointer that points to the size of the array
 * @return Array with all the updated repos
 */
int * updated_repos(COMMIT *c, int size, char *d_aux, int *s){
   DATA d = string_to_ano(d_aux);
   BTREE tree = NULL;
   int *updated = malloc(sizeof(int)*size);
   int j = 0;
   for(int i = 0; i< size ;i++){
      DATA aux = return_data(c,i);
      int ri = return_repo_id(c,i);
      if (dif_anos(d,aux) && exist_elem(tree,ri) == 0){
         updated[j] = ri;
         tree = add_elem(tree,ri);
         j++;
      }
   }
   *s = j;
   free_btree(tree);
   qsort(updated,j,sizeof(int),compareInts);
   return updated;
}

/**
 * @brief Function that creates an array of triplo element with the inforation needed for query9
 * @param c Array of COMMIT elements
 * @param size Size of the COMMIT array
 * @param aux_uc Void pointer that represents the array of user connections
 * @param size_triplo Pointer to the real size of the TRIPLO array
 * @return Void pointer that represents the TRIPLO array
 */
void *triplos_parametrizavel(COMMIT *c, int size, void* aux_uc, int *size_triplo, int size_connections){
   CONNECTION *uc = (CONNECTION*) aux_uc;
   TRIPLO *t = init_triplo();
   BTREE tree = NULL;
   int st = 0;
   int N = 1;
   for(int i = 0;i<size;i++){
      int commiterId = return_commiter_id(c,i);
      int ind = find_index_uc(uc,commiterId,size_connections); 
      if (ind != -1) {
         int ai = return_author_id(c,i);
         ind = binary_search_amigos(uc,ai,ind);
         if (ind) {
               if(exist_elem(tree,commiterId)){
                  t = add_elem_triplo(t,commiterId,"",1,st,&N);
                  tree = add_elem(tree,commiterId);
                  st++;
               }
               else
               {  
                  inc_qtty(t,st,commiterId);
               }
            }
         }
   }
   free_btree(tree);
   *size_triplo = st;
   sort_triplo(t,st);
   return t;
}