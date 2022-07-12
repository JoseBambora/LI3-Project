#include "../include/user.h"
#include "../include/repo.h"
#include "../include/commit.h"
#include "../include/totalstats.h"
#include "../include/typesstats.h"
#include "../include/queries.h"
#include "../include/tuplo.h"
#include "../include/aux.h"
#include "../include/connection.h"
#include "../include/triplo.h"
#include "../include/data.h"
#include "../include/commessage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Function that will answer query1.
 * @param u definition of struct that contains all the information needed for this query
 * @param newFile File that we will put the answer.
 * @return 0
 */
static int query1 (UTYPESTATS u, FILE* newFile) {
    printf("Resolver Query 1\n");
    fprintf(newFile,"Bot: %d\n",returnBots(u));   
    fprintf(newFile,"Organization: %d\n",returnOrganization(u));
    fprintf(newFile,"User: %d\n",returnUser(u));
    printf("Query 1 resolvida\n");
    return 0;
}
/**
 * @brief Function that will answer query2.
 * @param u definition of struct that contains all the information needed for this query
 * @param newFile File that we will put the answer.
 * @return 0
 */
static int query2 (TOTALSTATS u, FILE* newFile) {
    printf("Resolver Query 2\n");
    float colaboradores=0, repos=0;
    colaboradores = (float) returnColaboradores(u);
    repos = (float) returnRepos(u);
    float media = colaboradores/repos;
    fprintf(newFile,"%.2f\n",media);
    printf("Query 2 resolvida\n");
    return 0;
}

/**
 * @brief Function that will answer query3.
 * @param u definition of struct that contains all the information needed for this query
 * @param newFile File that we will put the answer.
 * @return 0
 */
static int query3(TOTALSTATS u, FILE* newFile){
    printf("Resolver Query 3\n");
    int r = returnBotIds(u);
    fprintf(newFile,"%d\n",r);
    printf("Query 3 resolvida\n");
    return 0;
}

/**
 * @brief Function that will answer query4.
 * @param u definition of struct that contains all the information needed for this query
 * @param newFile File that we will put the answer.
 * @return 0
 */
static int query4 (TOTALSTATS u, FILE* newFile) {
    printf("Resolver Query 4\n");
    float com=0, use=0;
    com = (float) returnCommits(u);
    use = (float) returnUsers(u);
    float media = com/use;
    fprintf(newFile,"%.2f\n",media);
    printf("Query 4 resolvida\n");
    return 0;
}

/**
 * @brief Function that will answer query5
 * @param u USER struct array needed to answer this querry
 * @param size_users
 * @param c COMMIT struct array needed to answer this querry
 * @param size_commit
 * @param n Top n users with most commits between two dates
 * @param liminf lower bound of the dates
 * @param limsup upper bound of the dates
 * @param newFile file where the answer will be put
 * @return 0
 */
static int query5(USER* u,int size_users, COMMIT *c, int size_commits, char *n, char *liminf, char *limsup, FILE *newFile)
{
    printf("Resolver Query 5\n");
    DATA di = string_to_ano(liminf);
    DATA ds = string_to_ano(limsup);
    int size_triplo = 0;
    TRIPLO *t = commits_qtty(di,ds,c,size_commits,&size_triplo);
    t = complete_triplo(u,size_users,t,size_triplo); 
    int num = atoi(n);
    add_content_triplo(t,size_triplo,num,newFile);
    free_triplo(t,size_triplo);
    free_data(di);
    free_data(ds);
    printf("Query 5 resolvida\n");
    return 0;
}

/**
 * @brief Function that will answer query6
 * @param u USERS struct needed to answer this querry
 * @param size_users Size of the COMMIT struct array 
 * @param c COMMIT struct array needed to answer this querry
 * @param size_commits Size of the COMMIT struct array 
 * @param r REPOS struct needed to answer this querry
 * @param n Top n users with most commits on repos of a certain language
 * @param lan Language 
 * @param newFile file where the asnwer will be put
 * @return 0
 */
static int query6(USER *u, int size_users , COMMIT *c, int size_commits, REPO* r, int size_repos,char* n, char*lan,FILE *newFile)
{
    printf("Resolver Query 6\n");
    int num = atoi(n);
    int *rID = repo_language(r,size_repos,lan);
    int size_triplo = 0;
    TRIPLO *t = commiter_id_repos(c,size_commits,rID,&size_triplo);
    t = complete_triplo(u,size_users,t,size_triplo); 
    add_content_triplo(t,size_triplo,num,newFile);
    free(rID);
    free_triplo(t,size_triplo);
    printf("Query 6 resolvida\n");
    return 0;
}

/**
 * @brief Function that will answer query7.
 * @param c COMMT struct array needed to answer this query
 * @param size_commits Size of the COMMIT struct array 
 * @param r Repos that will allow us to answer.
 * @param size_repos Size of the REPO struct array 
 * @param data Data to filter.
 * @param newFile File that we will put the answer.
 * @return 0.
*/
static int query7(COMMIT *c, int size_commits, REPO *r,int size_repos, char*data, FILE *newFile){
    printf("Resolver Query 7\n");
    int s = 0, size_tuplo = 0;
    int *not_updated = not_updated_repos(c,size_commits,data,&s);
    TUPLO *t = (TUPLO *) repo_no_updates(r,size_repos,not_updated,s,&size_tuplo);
    add_content_tuplo2(t,size_tuplo,size_tuplo,newFile);
    printf("Query 7 resolvida\n");
    free(not_updated);
    return 0;
}
/**
 * @brief Function that will answer query8.
 * @param c COMMT struct array needed to answer this query
 * @param size_commits Size of the COMMIT struct array 
 * @param r REPO struct array needed to answer this query
 * @param size_repos Size of the REPO struct array 
 * @param n Top n repos of certain language.
 * @param lan Language to filter repos.
 * @param newFile File that we will put the answer.
 * @return 0.
*/
static int query8(COMMIT *c, int size_commits, REPO * r, int size_repos,char* n,char *data, FILE *newFile){
    printf("Resolver Query 8\n");
    int s = 0,size_tuplo = 0;
    int *updated = updated_repos(c,size_commits,data,&s);
    TUPLO* t = (TUPLO *) repo_language_qtty(r,size_repos,updated,s,&size_tuplo);
    int num = atoi(n);
    add_content_tuplo(t,size_tuplo,num,newFile);
    printf("Query 8 resolvida\n");
    free(updated);
    return 0;
}

/**
 * @brief Function that will answer query9
 * @param u USER struct array  needed to answer this querry
 * @param size_users Size of the USER struct array 
 * @param uc CONNECTION struct array  needed to answer this querry
 * @param c COMMIT struct array needed to answer this querry
 * @param size_commits Size of the COMMIT struct array 
 * @param n Top N users with most commits in repos owned by their friends
 * @param newfile File where the answer will be put
 * @return 0
 */
static int query9 (USER *u, int size_users,CONNECTION *uc, COMMIT *c, int size_commits, int size_connections, char *n, FILE *newfile){
    printf("Resolver Query 9\n");
    int size_triplo = 0;
    TRIPLO *t = triplos_parametrizavel(c,size_commits,uc,&size_triplo, size_connections);
    t = complete_triplo(u,size_users,t,size_triplo); 
    int num = atoi(n);
    add_content_triplo2(t,size_triplo,num,newfile);
    free_triplo(t,size_triplo);
    printf("Query 9 resolvida\n");
    return 0;
}

/**
 * @brief Function that will answer query10
 * @param cm COMMITMESSAGE struct needed to answer this querry
 * @param n top N users with the biggest commit messages
 * @param newFile file where the answer will be put
 * @return 0
 */
static int query10(COMMITMESSAGE cm, char *n, FILE *newFile, int size_cm)
{
    printf("Resolver Query 10\n");
    int num = atoi(n);
    add_content_cm(cm,size_cm,num,newFile);
    printf("Query 10 resolvida\n");
    return 0;
}

/**
 * @brief Function that will answer the queries.
 * @param aux_u Void pointer that represents the collection of users
 * @param aux_r Void pointer that represents the collection of repos
 * @param aux_c Void pointer that represents the collection of commits
 * @param aux_utypes Void pointer that represents
 * @param aux_totalstats Void pointer that represents the stats of our files
 * @param aux_cm Void pointer that represents commit messages
 * @param aux_uc Void pointer that represents connections between users
 * @param commands Commands used to invoke the queries
 * @param size_repos Number of repos
 * @param size_commits Number of commits
 * @param size_users Number of users
 * @param size_cm Size of the commit messages
 * @return 0.
 */
int answer_queries(void *aux_u, void* aux_r, void *aux_c, void*aux_utypes, void *aux_totalstats, void *aux_cm, void *aux_uc,char *commands, int size_repos,int size_commits, int size_users, int size_cm, int size_connections)
{
    USER *u = (USER*) aux_u;
    REPO * r = (REPO *) aux_r;
    COMMIT * c = (COMMIT *) aux_c;
    UTYPESTATS utt = (UTYPESTATS) aux_utypes;
    TOTALSTATS ts = (TOTALSTATS) aux_totalstats;
    COMMITMESSAGE cm = (COMMITMESSAGE) aux_cm;
    CONNECTION *uc = (CONNECTION*) aux_uc;
    FILE *answer = NULL;
    FILE *queries = fopen(commands,"r");
    int i;
    char *num = NULL,*d = NULL,*liminf = NULL,*limsup = NULL;
    char *line = malloc(40 * sizeof(char));
    for(i = 1; fgets(line,40,queries);i++)
    {
        char *name = name_newfile(i);
        char *aux = NULL;
        answer = fopen(name,"w");
        int lineNum = strtol(line,&aux,10);
        switch (lineNum)
        {
            case 1:
                query1(utt,answer);
                break;
            case 2:
                query2(ts,answer);
                break;
            case 3:
                query3(ts,answer);
                break;
            case 4:
                query4(ts,answer);
                break;
            case 5:
                aux = line + 2;
                num = strsep(&aux," ");
                liminf = strsep(&aux," ");
                limsup = strsep(&aux,"\n");
                query5(u,size_users,c,size_commits,num,liminf,limsup,answer);
                break;
            case 6:
                aux = line + 2;
                num = strsep(&aux," ");
                d = strsep(&aux,"\n");
                query6(u,size_users,c,size_commits,r,size_repos,num,d,answer);
                break;
            case 7:
                aux = line + 2;
                d = strsep(&aux,"\n");
                query7(c,size_commits,r,size_repos,d,answer);
                break;
            case 8:
                aux = line + 2;
                num = strsep(&aux," ");
                d = strsep(&aux, "\n");
                query8(c,size_commits,r,size_repos,num,d,answer);
                break;
            case 9:
                aux = line + 2;
                num = strsep(&aux,"\n");
                query9(u,size_users,uc,c,size_commits,size_connections,num,answer);
                break;
            case 10:
                aux = line + 3;
                num = strsep(&aux,"\n");
                query10(cm,num,answer,size_cm);
                break;
        }
        free(name);
        fclose(answer);
    }
    free(line);
    return 0;
}