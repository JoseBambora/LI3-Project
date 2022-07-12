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
#include "../include/hashint.h"

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
 * @brief Function that converts a line from the file cointaing the commit collection to an element of the array of COMMIT elements
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
 * @brief Funtion that adds content to the file storing the information of the commits 
 * @param c Commit to store
 * @param ficheiro File to be written
 */
static void add_content_commit(COMMIT c, FILE *ficheiro){
   fseek(ficheiro,0,SEEK_END);
   fprintf(ficheiro,"%d;%d;%d;%d-%d-%d %d:%d:%d;%d\n",c.repoId,c.authorId,c.commiterId,return_field(c.data,'A'),return_field(c.data,'M'),return_field(c.data,'D'),return_field(c.data,'h'),return_field(c.data,'m'),return_field(c.data,'s'),c.lenmessage);
   free_data(c.data);
   //remove space if needed
}


/**
 * @brief Function that saves all the information regarding commits into a collection of commits (in our case an array of COMMIT elements)
 * @return the real size of the array of COMMIT elements
 */
int start_commits(){
   int size = 0;
   COMMIT aux;
   FILE *commit = fopen("catalogo/commit.csv","w");
   FILE *ficheiro = fopen("entrada/commits-g3-filter.csv","r");
   char *line = malloc(3000 * sizeof (char));
   line = fgets(line,3000,ficheiro);
   while(fgets(line,3000,ficheiro)){
      aux = associa_linha_commit(line);
      add_content_commit(aux,commit);
      size++;
   }
   fclose(ficheiro);
   fclose(commit);
   free(line);
   return size;
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
 * @brief Alternate function that creates a QUADRUPLO array
 * @param s Pointer that represents the size of the Quadruplo
 * @return Void pointer that represents a QUADRUPLO struct
 */
void *commit_quadruplo(int *s)
{
   COMMIT co;
   FILE *commit = fopen("catalogo/commit.csv","r");
   char *line = malloc(sizeof(char)*3000);
   QUADRUPLO *t = init_quadruplo();
   int n = 1;
   THash h = init_hash();
   int cm_s = 0;
   while(fgets(line,3000,commit))
   {
      co = associa_linha_commit(line);
      int ri = co.repoId;
      if(exist_elem_hash(h,ri) == 0)
      {
         t = add_elem_quadruplo(t,co.commiterId,"",co.lenmessage,cm_s,&n,ri); 
         insert_hash(h,ri);
         cm_s++;
      }
      free_elem_commit(co);
   }
   free(line);
   fclose(commit);
   free_hash(h);
   (*s) = cm_s;
   return t;
}

/**
 * @brief Function that calculates the number of repos with commits made by bots
 * @param bot_ids integer array containing all the ids belonging to bots
 * @return j, a variable that stores the amount of repos with commits made by bots
 */
int bot_repos(int *bot_ids)
{
   COMMIT co;
   FILE *commit = fopen("catalogo/commit.csv","r");
   char *line = malloc(sizeof(char)*3000);
   int size = size_array(bot_ids);
   int j = 0,ai,ci,ri;
   BTREE tree = NULL;
   while(fgets(line,3000,commit))
   {
      co = associa_linha_commit(line);
      ri = co.repoId;
      if (exist_elem(tree,ri) == 0)
      {
         ai = co.authorId;
         ci = co.commiterId;
         if (pesquisaBinaria(bot_ids,ai,size)) {
            tree = add_elem(tree,ri);
            j++;
         }
         else if (pesquisaBinaria(bot_ids,ci,size)) {
            tree = add_elem(tree,ri);
            j++;
         }
      }
      free_elem_commit(co);
   }
   free(line);
   fclose(commit);
   free_btree(tree);
   return j;
}

/**
 * @brief Function that returns the number of colaborators
 * @return The number of colaborators
 */
int return_colaborators(){
   COMMIT co;
   FILE *commit = fopen("catalogo/commit.csv","r");
   char *line = malloc(sizeof(char)*3000);
   int ci, ai, s = 0;
   BTREE treeci = NULL;
   BTREE treeai = NULL;
   while(fgets(line,3000,commit))
   {
      co = associa_linha_commit(line);
      ci = co.commiterId;
      ai = co.authorId;
      if (exist_elem(treeci,ci) == 0)  {
         treeci = add_elem(treeci,ci);
         s++;
      }
      else if (exist_elem(treeai,ai) == 0) {
         treeai = add_elem(treeai,ai);
         s++;
      }
      free_elem_commit(co);
   }
   free_btree(treeai);
   free_btree(treeci);
   free(line);
   fclose(commit);
   return s;
}

/**
 * @brief Function that returns the quantity of commits made by one commiter in a date range
 * @param liminf minimum date
 * @param limsup maximum date
 * @param size_triplo Pointer to the real size of the TRIPLO array
 * @return TRIPLO struct array with updated information represented as a void pointer
 */
void *commits_qtty(void *liminf, void* limsup, int *size_triplo)
{
   COMMIT co;
   FILE *commit = fopen("catalogo/commit.csv","r");
   char *line = malloc(sizeof(char)*3000);
   TRIPLO * t = init_triplo();
   int n = 1;
   THash h = init_hash();
   int s = 0;
   while(fgets(line,3000,commit))
   {
      co = associa_linha_commit(line);
      DATA aux = co.data;
      if(dif_anos(liminf,aux) && dif_anos(aux,limsup))
      {
         int id = co.commiterId;
         if(exist_elem_hash(h,id) == 0)
         {
            t = add_elem_triplo(t,id,"",1,s,&n);
            insert_hash(h,id);
            s++;
         }
         else
         {
            inc_qtty(t,s,id);
         }
      }
      free_elem_commit(co);
   }
   free(line);
   *size_triplo = s;
   free_hash(h);
   sort_triplo(t,s);
   fclose(commit);
   return t;
}

/**
 * @brief Function that creates an array of TRIPLO elements with information needed for query 6
 * @param repos_ids Integer array with all the repo ids 
 * @param size_triplo Pointer to the real size of the TRIPLO array
 * @return void pointer that represents the TRIPLOS
 */
void *commiter_id_repos(int *repos_ids, int *size_triplo)
{
   COMMIT co;
   FILE *commit = fopen("catalogo/commit.csv","r");
   char *line = malloc(sizeof(char)*3000);
   TRIPLO * t = init_triplo();
   int s = size_array(repos_ids);
   int n = 1;
   int st = 0;
   THash h = init_hash();
   while(fgets(line,3000,commit))
   {
      co = associa_linha_commit(line);
      if(pesquisaBinaria(repos_ids,co.repoId,s))
      {
         int id = co.commiterId;
         if(exist_elem_hash(h,id) == 0)
         {
            t = add_elem_triplo(t,id,"",1,st,&n);
            insert_hash(h,id);
            st++;
         }
         else
         {
            inc_qtty(t,st,id);
         }
      }
      free_elem_commit(co);
   }
   free(line);
   *size_triplo = st;
   sort_triplo(t,st);
   free_hash(h);
   fclose(commit);
   return t;
}

/**
 * @brief Function that inserts into an array all the repos that are not updated after a certain date
 * @param size Size of the COMMIT array
 * @param d_aux Date
 * @param s Integer pointer that points to the size of the array
 * @return Array with all the not updated repos
 */
int *not_updated_repos (int size, char *d_aux, int *s){
   COMMIT co;
   FILE *commit = fopen("catalogo/commit.csv","r");
   char *line = malloc(sizeof(char)*3000000);
   DATA d = string_to_ano(d_aux);
   BTREE tree = NULL;
   int *not_updated = malloc(sizeof(int)*size);
   int j = 0;
   while(fgets(line,3000,commit))
   {
      co = associa_linha_commit(line);
      DATA aux = co.data;
      int ri = co.repoId;
      if (dif_anos(aux,d)&& exist_elem(tree,ri) == 0){
         not_updated[j] = ri;
         tree = add_elem(tree,ri);
         j++;
      }
      free_elem_commit(co);
   }
   *s = j;
   free_btree(tree);
   free(line);
   qsort(not_updated,j,sizeof(int),compareInts);
   fclose(commit);
   return not_updated;
}

/**
 * @brief Function that inserts into an array all the repos that are updated after a certain date
 * @param size Size of the COMMIT array
 * @param d_aux Date
 * @param s Integer pointer that points to the size of the array
 * @return Array with all the updated repos
 */
int *updated_repos(int size, char *d_aux, int *s){
   COMMIT co;
   FILE *commit = fopen("catalogo/commit.csv","r");
   char *line = malloc(sizeof(char)*3000000);
   DATA d = string_to_ano(d_aux);
   BTREE tree = NULL;
   int *updated = malloc(sizeof(int)*size);
   int j = 0;
   while(fgets(line,3000,commit))
   {
      co = associa_linha_commit(line);
      DATA aux = co.data;
      int ri = co.repoId;
      if (dif_anos(d,aux) && exist_elem(tree,ri) == 0){
         updated[j] = ri;
         tree = add_elem(tree,ri);
         j++;
      }
      free_elem_commit(co);
   }
   *s = j;
   free_btree(tree);
   free(line);
   qsort(updated,j,sizeof(int),compareInts);
   fclose(commit);
   return updated;
}

/**
 * @brief Function that creates an array of triplo element with the inforation needed for query9
 * @param aux_uc Void pointer that represents the array of user connections
 * @param size_triplo Pointer to the real size of the TRIPLO array
 * @param size_connections Size of user connections
 * @return Void pointer that represents the TRIPLO array
 */
void *triplos_parametrizavel(void* aux_uc, int *size_triplo, int size_connections){
   COMMIT co;
   FILE *commit = fopen("catalogo/commit.csv","r");
   char *line = malloc(sizeof(char)*3000);
   CONNECTION *uc = (CONNECTION*) aux_uc;
   TRIPLO *t = init_triplo();
   BTREE tree = NULL;
   int st = 0;
   int N = 1;
   while(fgets(line,3000,commit))
   {
      co = associa_linha_commit(line);
      int commiterId = co.commiterId;
      int ind = find_index_uc(uc,commiterId,size_connections); 
      if (ind != -1) {
         int ai = co.authorId;
         ind = binary_search_amigos(uc,ai,ind);
         if (ind) 
         {
            if(!exist_elem(tree,commiterId)){
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
      free_elem_commit(co);
   }
   free(line);
   free_btree(tree);
   *size_triplo = st;
   sort_triplo(t,st);
   fclose(commit);
   return t;
}