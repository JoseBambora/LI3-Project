typedef struct u_types_stats *UTYPESTATS;

void setBots (UTYPESTATS stats, int n);
void setOrganization (UTYPESTATS stats, int n);
void setUser (UTYPESTATS stats, int n);
int returnBots (UTYPESTATS stats);
int returnOrganization (UTYPESTATS stats);
int returnUser (UTYPESTATS stats);
UTYPESTATS start_typesstats();

int free_Utypes(UTYPESTATS s);

