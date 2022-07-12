typedef struct total_stats *TOTALSTATS;

int returnColaboradores (TOTALSTATS stats);
int returnRepos (TOTALSTATS stats);
int returnCommits (TOTALSTATS stats) ;
int returnUsers (TOTALSTATS stats);
int returnBotIds (TOTALSTATS stats);
TOTALSTATS init_total_stats();
int set_colaboradores (TOTALSTATS t, int n);
int set_commits (TOTALSTATS t, int n);
int set_repos (TOTALSTATS t, int n);
void* add_elem_to_array (TOTALSTATS ts,int n,int id);
int set_user (TOTALSTATS t, int n);
int get_bot_ids(void *aux_c, void *ts_aux, int size);
int set_bot_ids (TOTALSTATS t, int n);
int set_total_stats(TOTALSTATS t, int col, int com, int rep, int use,int bi);
int free_TotalStats( TOTALSTATS t);
