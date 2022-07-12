typedef struct total_stats *TOTALSTATS;

int returnColaboradores (TOTALSTATS stats);
int returnRepos (TOTALSTATS stats);
int returnCommits (TOTALSTATS stats) ;
int returnUsers (TOTALSTATS stats);
int returnBotIds (TOTALSTATS stats);
TOTALSTATS start_totalstats();
TOTALSTATS add_elem_to_array (TOTALSTATS ts,int n,int id);
int get_bot_ids(void *ts_aux);

int set_total_stats(TOTALSTATS t, int col, int com, int rep, int use,int bi);
int free_TotalStats( TOTALSTATS t);
