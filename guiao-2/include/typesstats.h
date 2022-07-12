typedef struct u_types_stats *UTYPESTATS;

void setBots (UTYPESTATS stats, int n);
void setOrganization (UTYPESTATS stats, int n);
void setUser (UTYPESTATS stats, int n);
int returnBots (UTYPESTATS stats);
int returnOrganization (UTYPESTATS stats);
int returnUser (UTYPESTATS stats);
UTYPESTATS  init_types_users();
int incrementaTypes (UTYPESTATS u, int n);
int free_Utypes(UTYPESTATS s);

