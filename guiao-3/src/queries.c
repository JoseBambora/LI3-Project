#include "../guiao-2/include/user.h"
#include "../guiao-2/include/repo.h"
#include "../guiao-2/include/commit.h"
#include "../guiao-2/include/totalstats.h"
#include "../guiao-2/include/typesstats.h"
#include "../guiao-2/include/tuplo.h"
#include "../guiao-2/include/aux.h"
#include "../guiao-2/include/connection.h"
#include "../guiao-2/include/triplo.h"
#include "../guiao-2/include/data.h"
#include "../guiao-2/include/commessage.h"
#include "../include/queries.h"
#include "../include/menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>

#define s_line 1000
int teste;
int interativo;

/**
 * @brief Function to transfer information from one file to another.
 * @param f1 File 1.
 * @param f2 File 2.
 * @param num Number of lines to pass.
 * @param param If the query has parameters.
 */
static void transfer_info(FILE *f1, FILE *f2, int num, int param)
{
    int i;
    char *line = malloc(sizeof(char) * 3000);
    if(param) line = fgets(line,3000,f2);
    for(i = 0; i < num && fgets(line,3000,f2); i++)
        fprintf(f1,"%s",line);
    fclose(f1);
    fclose(f2);
    free(line);
}

/**
 * @brief Print the time used.
 * @param time_used the time to print.
 */
static void print_time(double time_used)
{
    if(interativo) 
        print_time_ncur(time_used);
    else 
        printf("Tempo: %.2f\n",time_used);
}

/**
 * @brief Print some string on the terminal.
 * @param r String to print.
 */
static void resolver_query(char *r)
{
    if (interativo) 
        print_str(r);
    else {
        print_traco(79);
        printf("%s",r); 
    }
}

/**
 * @brief Print some string on the terminal.
 * @param r String to print.
 */
static void resolvida_query(char *r)
{
    if (interativo) 
        print_str(r);
    else
        printf("%s",r); 
}

/**
 * @brief Function to see if the result is right.
 * @param param String with the parameters.
 * @param name Name of the file to compare.
 * @param lineNum Number of query.
 */
static void verify_files(char *param,char *name , int lineNum)
{
    int pa = 0;
    char *aux2 = malloc(sizeof(char) * 60);
    char *aux3 = malloc(sizeof(char) * 60);
    strcpy(aux2,"expected_files/query");
    strcpy(aux3,"saida/query");
    char *s = malloc(sizeof(char) *5);
    sprintf(s,"%d/",lineNum);
    strcat(aux2,s);
    strcat(aux3,s);
    if(*param) 
    {
        pa = 1;
        aux2 = where(aux2,param);
        aux3 = where(aux3,param);
    }
    else 
    {
        strcat(aux2,"output.txt");
        strcat(aux3,"output.txt");
    }
    validate_files(name,aux2,aux3,interativo,pa,param,lineNum);
    free(aux2);
    free(aux3);
    free(s);
}

/**
 * @brief Function that will answer query1.
 * @param newFile File that we will put the answer.
 * @return 0
 */
 static int query1 (FILE* newFile) {
    clock_t start, end;
    double time_used = 0;
    start = clock();
    resolver_query("Resolver Query 1.\n");
    FILE *fileQ = fopen("saida/query1/output.txt", "r");
    if (!fileQ) {
         UTYPESTATS u = start_typesstats();
         fileQ = fopen("saida/query1/output.txt","w");
         fprintf(newFile,"Bot: %d\n",returnBots(u));    
         fprintf(newFile,"Organization: %d\n",returnOrganization(u));
         fprintf(newFile,"User: %d\n",returnUser(u));
         fprintf(fileQ,"Bot: %d\n",returnBots(u));    
         fprintf(fileQ,"Organization: %d\n",returnOrganization(u));
         fprintf(fileQ,"User: %d\n",returnUser(u));
         free_Utypes(u);
        fclose(newFile);
        fclose (fileQ);
    }
    else 
        transfer_info(newFile,fileQ,1000,0);
    if(teste)
    {
        end = clock();
        time_used = ((double) end - start)/ CLOCKS_PER_SEC;
    }
    char *filename= "saida/query1/output.txt";
    if (interativo) read_file_estatisticasqueries(filename,1);
    if(teste)
       print_time(time_used); 
    resolvida_query("Query 1 resolvida.\n");
    return 0;
}
  
/**
 * @brief Function that will answer query2.
 * @param size_repo repo size
 * @param newFile File that we will put the answer.
 * @return 0
 */
static int query2 (int size_repo,FILE* newFile) {
    clock_t start, end;
    double time_used = 0;
    start = clock();
    resolver_query("Resolver Query 2.\n");
    FILE *fileQ = fopen("saida/query2/output.txt", "r");
    if (!fileQ) {
        TOTALSTATS t = start_totalstats();
        set_total_stats(t,return_colaborators(),0,size_repo,0,0);
        fileQ = fopen("saida/query2/output.txt","w");
        float colaboradores=0, repos=0;
        colaboradores = (float) returnColaboradores(t);
        repos = (float) returnRepos(t);
        float media = colaboradores/repos;
        fprintf(newFile,"%.2f\n",media);
        fprintf(fileQ,"%.2f\n",media);
        free_TotalStats(t);
        fclose(newFile);
        fclose (fileQ);
    }
    else 
        transfer_info(newFile,fileQ,1000,0);
    if(teste)
    {
        end = clock();
        time_used = ((double) end - start)/ CLOCKS_PER_SEC;
    }
    char*filename = "saida/query2/output.txt";
    if (interativo) read_file_estatisticasqueries(filename,2);
    if(teste)
       print_time(time_used); 
    resolvida_query("Query 2 resolvida.\n");
    return 0;
}

/**
 * @brief Function that will answer query3.
 * @param newFile File that we will put the answer.
 * @return 0
 */
static int query3(FILE* newFile){
    clock_t start, end;
    double time_used = 0;
    start = clock();
    resolver_query("Resolver Query 3.\n");
    FILE *fileQ = fopen("saida/query3/output.txt", "r");
    if (!fileQ) {
        TOTALSTATS t = start_totalstats();
        set_total_stats(t,0,0,0,0,get_bot_ids(t));
        fileQ = fopen("saida/query3/output.txt","w");
        int r = returnBotIds(t);
        fprintf(newFile,"%d\n",r);
        fprintf(fileQ,"%d\n",r);
        free_TotalStats(t);
        fclose(newFile);
        fclose (fileQ);
    }
    else 
        transfer_info(newFile,fileQ,1000,0);
    if(teste)
    {
        end = clock();
        time_used = ((double) end - start)/ CLOCKS_PER_SEC;
    }
    char *filename = "saida/query3/output.txt";
    if (interativo) read_file_estatisticasqueries(filename,3);
    if(teste)
       print_time(time_used); 
    resolvida_query("Query 3 resolvida.\n");
    return 0;
}

/**
 * @brief Function that will answer query4.
 * @param size_user user size
 * @param size_commit commit size
 * @param newFile File that we will put the answer.
 * @return 0
 */
static int query4 (int size_user, int size_commit, FILE* newFile) {
    clock_t start, end;
    double time_used = 0;
    start = clock();
    resolver_query("Resolver Query 4.\n");
    FILE *fileQ = fopen("saida/query4/output.txt", "r");
    if (!fileQ) {
        TOTALSTATS t = start_totalstats();
        set_total_stats(t,0,size_commit,0,size_user,0);
        fileQ = fopen("saida/query4/output.txt","w");
        float com=0, use=0;
        com = (float) returnCommits(t);
        use =  (float) returnUsers(t);
        float media = com/use;
        fprintf(newFile,"%.2f\n",media);
        fprintf(fileQ,"%.2f\n",media);
        free_TotalStats(t);
        fclose(newFile);
        fclose (fileQ);
    }
    else 
        transfer_info(newFile,fileQ,1000,0);
    if(teste)
    {
        end = clock();
        time_used = ((double) end - start)/ CLOCKS_PER_SEC;
    }
    char *filename = "saida/query4/output.txt";
    if (interativo) read_file_estatisticasqueries(filename,4);
    if(teste)
       print_time(time_used); 
    resolvida_query("Query 4 resolvida.\n");
    return 0;
}

/**
 * @brief Function that will answer query5
 * @param n Top n users with most commits between two dates
 * @param liminf lower bound of the dates
 * @param limsup upper bound of the dates
 * @param newFile file where the answer will be put
 * @return 0
 */
static int query5(char *n, char *liminf, char *limsup, FILE *newFile)
{
    clock_t start, end;
    double time_used = 0;
    start = clock();
    resolver_query("Resolver Query 5.\n");
    char* name;
    char *d = strdup(liminf);
    strcat(d," ");
    strcat(d,limsup);
    strcat(d,"\n");
    name= where("saida/query5/",d);
    int num = atoi(n);
    FILE *aux = fopen (name , "r");
    if (!aux) {
        aux = fopen (name, "w");
        fprintf(aux,"%s",d);
        DATA di = string_to_ano(liminf);
        DATA ds = string_to_ano(limsup);
        int size_triplo = 0;
        TRIPLO *t = commits_qtty(di,ds,&size_triplo);
        t = complete_triplo(t,size_triplo); 
        add_content_triplo(t,size_triplo,num,newFile,aux);
        free_data(di);
        free_data(ds);
    }    
    else 
        transfer_info(newFile,aux,num,1);
    free(d);
    if(teste)
    {
        end = clock();
        time_used = ((double) end - start)/ CLOCKS_PER_SEC;
    }
    if (interativo) read_file_queries(name,5);
    free (name);
    if(teste)
       print_time(time_used); 
    resolvida_query("Query 5 resolvida.\n");
    return 0;
}

/**
 * @brief Function that will answer query6
 * @param n Top n users with most commits on repos of a certain language
 * @param lan Language 
 * @param newFile file where the asnwer will be put
 * @return 0
 */
static int query6(char* n, char*lan,FILE *newFile)
{
    clock_t start, end;
    double time_used = 0;
    start = clock();
    resolver_query("Resolver Query 6.\n");
    char *name;
    char *l = strdup(lan);
    strcat(l,"\n");
    name = where("saida/query6/",l);
    int num = atoi(n);
    FILE *aux = fopen(name,"r");
    if (!aux)
    {
        aux = fopen (name, "w");
        fprintf(aux,"%s",l);
        int *rID = repo_language(lan);
        int size_triplo = 0;
        TRIPLO *t = commiter_id_repos(rID,&size_triplo);
        free(rID);
        t = complete_triplo(t,size_triplo);
        add_content_triplo(t,size_triplo,num,newFile,aux);
    }
    else
        transfer_info(newFile,aux,num,1);
    free(l);
    if(teste)
    {
        end = clock();
        time_used = ((double) end - start)/ CLOCKS_PER_SEC;
    }
    if (interativo) read_file_queries(name,6);
    free (name);
    if(teste)
       print_time(time_used); 
    resolvida_query("Query 6 resolvida.\n");
    return 0;
}

/**
 * @brief Function that will answer query7.
 * @param size_commits Size of the COMMIT struct array.
 * @param data Data to filter.
 * @param newFile File that we will put the answer.
 * @return 0.
*/
static int query7(int size_commits, char*data, FILE *newFile){
    clock_t start, end;
    double time_used = 0;
    start = clock();
    resolver_query("Resolver Query 7.\n");
    char *name;
    char *d = strdup(data);
    strcat(d,"\n");
    name = where("saida/query7/",d);
    FILE *aux = fopen(name,"r");
    if(!aux)
    {
        int s = 0, size_tuplo = 0;
        aux = fopen(name,"w");
        fprintf(aux,"%s",d);
        int *not_updated = not_updated_repos(size_commits,data,&s);
        TUPLO *t = (TUPLO *) repo_no_updates(not_updated,s,&size_tuplo);
        add_content_tuplo2(t,size_tuplo,newFile,aux);
        free(not_updated);
    }
    else
        transfer_info(newFile,aux,100000000,1);
    free(d);
    if(teste)
    {
        end = clock();
        time_used = ((double) end - start)/ CLOCKS_PER_SEC;
    }
    if(interativo)read_file_queries(name,7);
    free(name);
    if(teste)
       print_time(time_used); 
    resolvida_query("Query 7 resolvida.\n");
    return 0;
}
/**
 * @brief Function that will answer query8.
 * @param size_commits Size of the COMMIT struct array 
 * @param size_repos Size of the REPO struct array 
 * @param n Top n repos of certain language.
 * @param data Data that will determine the result.
 * @param newFile File that we will put the answer.
 * @return 0.
*/
static int query8(int size_commits,char* n,char *data, FILE *newFile){
    clock_t start, end;
    double time_used = 0;
    start = clock();
    resolver_query("Resolver Query 8.\n");
    char *name;
    char *d = strdup(data);
    strcat(d,"\n");
    name = where("saida/query8/",d);
    FILE *aux = fopen(name,"r");
    int num = atoi(n);
    if(!aux)
    {
        int s = 0,size_tuplo = 0;
        aux = fopen(name,"w");
        fprintf(aux,"%s",d);
        int *updated = updated_repos(size_commits,data,&s);
        TUPLO* t = (TUPLO *) repo_language_qtty(updated,s,&size_tuplo);
        add_content_tuplo(t,size_tuplo,num,newFile,aux);
        free(updated);
    }
    else
    {
        int i;
        char *line = malloc(sizeof(char) * 3000);
        line = fgets(line,3000,aux);
        for(i = 0; i < num && fgets(line,3000,aux); i++)
        {
            char *li = line;
            char *l = strsep(&li,";");
            fprintf(newFile,"%s\n",l);
        }
        fclose(newFile);
        fclose(aux);
        free(line);
    }
    free(d);
    if(teste)
    {
        end = clock();
        time_used = ((double) end - start)/ CLOCKS_PER_SEC;
    }
    if(interativo)read_file_queries(name,8);
    free(name);
    if(teste)
       print_time(time_used); 
    resolvida_query("Query 8 resolvida.\n");
    return 0;
}

/**
 * @brief Function that will answer query9
 * @param n Top N users with most commits in repos owned by their friends
 * @param newfile File where the answer will be put
 * @return 0
 */
static int query9 ( char *n, FILE *newfile){
    clock_t start, end;
    double time_used = 0;
    start = clock();
    resolver_query("Resolver Query 9.\n");
    int num = atoi(n);
    FILE *fileQ = fopen("saida/query9/output.txt", "r");
    if(!fileQ)
    {
        fileQ = fopen("saida/query9/output.txt", "w");  
        int size_triplo = 0;
        int size_connections = 0;
        CONNECTION *uc = start_connections(&size_connections);
        TRIPLO *t = triplos_parametrizavel(uc,&size_triplo, size_connections);
        t = complete_triplo(t,size_triplo); 
        add_content_triplo2(t,size_triplo,num,newfile,fileQ);
    }
    else
        transfer_info(newfile,fileQ,num,1);
    if(teste)
    {
        end = clock();
        time_used = ((double) end - start)/ CLOCKS_PER_SEC;
    }
    if(interativo)read_file_queries("saida/query9/output.txt",9);
    if(teste)
       print_time(time_used); 
    resolvida_query("Query 9 resolvida.\n");
    return 0;
}

/**
 * @brief Function that will answer query10
 * @param n top N users with the biggest commit messages
 * @param newFile file where the answer will be put
 * @return 0
 */
static int query10(char *n, FILE *newFile)
{
    clock_t start, end;
    double time_used = 0;
    start = clock();
    resolver_query("Resolver Query 10.\n");
    int num = atoi(n);
    FILE *fileQ = fopen("saida/query10/output.txt", "r");
    if(!fileQ)
    {
        fileQ = fopen("saida/query10/output.txt", "w");
        int size_cm = 0;
        COMMITMESSAGE cm = startcommitmessage(&size_cm);
        add_content_cm(cm,size_cm,num,newFile,fileQ);
        free_cm(cm,size_cm);
    }
    else
        transfer_info(newFile,fileQ,num,1);
    if(teste)
    {
        end = clock();
        time_used = ((double) end - start)/ CLOCKS_PER_SEC;
    }
    if(interativo)read_file_queries("saida/query10/output.txt",10);
    if(teste)
       print_time(time_used); 
    resolvida_query("Query 10 resolvida.\n");
    return 0;
}

/**
 * @brief Function that will answer the queries.
 * @param uc Pointer that represents connections between users
 * @param size_repos Number of repos
 * @param size_commits Number of commits
 * @param size_users Number of users
 * @param size_connection Size of connections.
 * @param commands Commands used to invoke the queries
 * @return 0.
 */
static int answer_queries( int size_repos,int size_commits, int size_users,char *commands)
{
    FILE *answer = NULL;
    FILE *queries = fopen(commands,"r");
    int i;
    char *num = NULL,*d = NULL,*liminf = NULL,*limsup = NULL;
    char *line = malloc(40 * sizeof(char));
    char *param = malloc(40 * sizeof(char));
    for(i = 1; fgets(line,40,queries);i++)
    {
        char *name = name_newfile(i);
        char *aux = NULL;
        answer = fopen(name,"w");
        int lineNum = strtol(line,&aux,10);
        *param = 0;
        switch (lineNum)
        {
            case 1:
                query1(answer);
                break;
            case 2:
                query2(size_repos,answer);
                break;
            case 3:
                query3(answer);
                break;
            case 4:
                query4(size_users,size_commits,answer);
                break;
            case 5:
                aux = line + 2;
                num = strsep(&aux," ");
                strcpy(param,aux);
                liminf = strsep(&aux," ");
                limsup = strsep(&aux,"\n");
                query5(num,liminf,limsup,answer);
                break;
            case 6:
                aux = line + 2;
                num = strsep(&aux," ");
                strcpy(param,aux);
                d = strsep(&aux,"\n");
                query6(num,d,answer);
                break;
            case 7:
                aux = line + 2;
                strcpy(param,aux);
                d = strsep(&aux,"\n");
                query7(size_commits,d,answer);
                break;
            case 8:
                aux = line + 2;
                num = strsep(&aux," ");
                strcpy(param,aux);
                d = strsep(&aux, "\n");
                query8(size_commits,num,d,answer);
                break;
            case 9:
                aux = line + 2;
                num = strsep(&aux,"\n");
                query9(num,answer);
                break;
            case 10:
                aux = line + 3;
                num = strsep(&aux,"\n");
                query10(num,answer);
                break;
        }
        if(teste) 
            verify_files(param,name,lineNum);
        free(name);
    }
    free(param);
    print_traco(79);
    free(line);
    return 0;
}

/**
 * @brief Function that will make the first step for solving queries on the file .txt given.
 * @param commands Name of the file .txt with queries to answer.
 * @param te Integer to see if the executable invocated is ./teste or ./guiao-3.
 * @return 0.
 */
int start_queries(char *commands, int te)
{
    teste = te;
    printf("Catalogo User\n");
    int size_user = start_user();
    printf("Catalogo Repo\n");
    int size_repo = start_repo();
    printf("Catalogo Commit\n");
    int size_commit = start_commits();
    answer_queries(size_repo,size_commit,size_user,commands);
    return 0;   
} 

/**
 * @brief Main function of the interative program.
 */
void interative_program(int t)
{
    teste = t;
    interativo = 1;
    int i = 1;
    printf("Catalogo User\n");
    int size_user = start_user();
    printf("Catalogo Repo\n");
    int size_repos = start_repo();
    printf("Catalogo Commit\n");
    int size_commits = start_commits();
    char *str = malloc(sizeof(char) * 2);
    char *di,*df;
    FILE* answer;
    clear();
    initscr();
    raw();
    get_event();
    di = malloc(sizeof(char) * 30);
    df = malloc(sizeof(char) * 30);
    char *param = malloc(40 * sizeof(char));
    int result_files = 1;
    for(getstr(str); str && *str != 'Q' && *str != 'q'; getstr(str))
    {
        char *aux;
        int n = strtol(str,&aux,10);
        if (n > 0 && n < 11 && (!aux || strcmp(aux,"") == 0)){
            *param = 0;
            char *name = name_newfile(i);
            answer = fopen(name,"w");
            switch (n)
            {
                case 1:
                    query1 (answer);
                    break;
                case 2:
                    query2 (size_repos,answer);
                    break;
                case 3:
                    query3 (answer);
                    break;
                case 4:
                    query4 (size_user,size_commits,answer);
                    break;
                case 5:
                    printw("Insira uma data de inicio:\n");
                    getstr(di);
                    printw("Insira uma data de fim:\n");
                    getstr(df);
                    char *s1_aux = strdup(di);
                    char *s2_aux = strdup(df);
                    if(validate_data(s1_aux) && validate_data(s2_aux)) 
                    {
                        strcpy(param,di);
                        strcat(param," ");
                        strcat(param,df);
                        strcat(param,"\n");
                        query5("100000000",di,df,answer);
                    }
                    else 
                    {
                        result_files = print_invalid_data();
                        i--;
                    }
                    free(s1_aux);
                    free(s2_aux);
                    break;
                case 6:
                    printw("Insira uma linguagem: \n");
                    getstr(di);
                    int r = validate_language(di);
                    if(r) 
                    {
                        strcpy(param,di);
                        strcat(param,"\n");
                        query6("100000000",di,answer);
                    }
                    else 
                    {
                        result_files = print_invalid_lan();
                        i--;
                    }
                    break;
                case 7:
                    printw("Insira uma data:\n");
                    getstr(di);
                    strcpy(df,di);
                    if(validate_data(df)) 
                    {    
                        strcpy(param,di);
                        strcat(param,"\n");
                        query7(size_commits,di,answer);
                    }
                    else 
                    {
                        result_files = print_invalid_data();
                        i--;
                    }
                    break;
                case 8:
                    printw("Insira uma data:\n");
                    getstr(di);
                    strcpy(df,di);
                    if(validate_data(df)) 
                    {
                        strcpy(param,di);
                        strcat(param,"\n");
                        query8(size_commits,"100000000",di,answer);
                    }
                    else 
                    {
                        result_files = print_invalid_data();
                        i--;
                    }
                    break;
                case 9:
                    query9("100000000",answer);
                    break;
                case 10:
                    query10("100000000",answer);
                    break;
                default:
                    break;
            }
            i++;
            if (result_files && teste)
                verify_files(param,name,n);
            else if (teste) result_files = 1;
            free(name);
        }
        else if(*str == 'M' || *str == 'm') printMenu_iterativo();
        else 
        {
            clear();
            print_traco3(79);
            printw("Comando Invalido\n");
        }
        get_event();
    }
    free(param);
    free(di);
    free(df);
    endwin();
}