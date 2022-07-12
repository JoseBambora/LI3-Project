#include "../include/repo.h"
#include "../include/user.h"
#include "../include/commit.h"
#include "../include/totalstats.h"
#include "../include/typesstats.h"
#include "../include/queries.h"
#include "../include/connection.h"
#include "../include/commessage.h"
#include <stdio.h>
int main(int argc, char* argv[])
{
    UTYPESTATS ut = init_types_users();
    TOTALSTATS t = init_total_stats();
    CONNECTION *uc = init_userConnections();
    int size_user = 0;
    int size_repo = 0;
    int size_commit = 0;
    int size_connection=0;
    REPO* r = start_repo(&size_repo);
    COMMIT *c = start_commits(&size_commit);
    USER *u = start_user(&size_user,ut, uc,t,&size_connection);
    sort_repo(r,size_repo);
    sort_user(u, size_user);
    set_total_stats(t,return_colaborators(c,size_commit),size_commit,size_repo,size_user,get_bot_ids(c,t,size_commit));
    int size_cm = 0;
    COMMITMESSAGE cm = startcommitmessage(u,c,size_commit,size_user,&size_cm);
    sort_commit(c,size_commit);
    sort_connection(uc,size_connection);
    answer_queries(u,r,c,ut,t,cm,uc,argv[1],size_repo,size_commit,size_user,size_cm, size_connection);
    free_repo(r,size_repo);
    free_commit(c,size_commit);
    free_user(u, size_user);
    free_Utypes(ut);
    free_TotalStats(t);
    free_Connection (uc, size_connection);
    free_cm(cm,size_cm);
    return 0;
} 