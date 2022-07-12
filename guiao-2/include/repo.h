typedef struct repo REPO;

REPO* init_repo();
REPO *start_repo (int *s);
int free_repo(REPO *r, int size);
int sort_repo(REPO *r, int size);
int *repo_language (REPO *r,int size, char * lan);
void *repo_no_updates(REPO *r, int size,int *not_updated, int size_no_updated, int *size_tuplo);
void *repo_language_qtty(REPO *r,int size, int *updated, int s,int *size_tuplos);
