typedef struct quadruplo  QUADRUPLO;
QUADRUPLO* init_quadruplo();
QUADRUPLO* add_elem_quadruplo(QUADRUPLO *atr, int id, char *login, int qtty, int size,int *N ,int repo_id);
int free_quadruplo(QUADRUPLO *t, int size);
int add_content_quadruplo (QUADRUPLO *t, int size, int num, void* File,void *);
int sort_quadruplo(QUADRUPLO *atr, int size);
QUADRUPLO *sort_aux(QUADRUPLO *t, int size);
QUADRUPLO *complete_quadruplo_tuplo(QUADRUPLO *tr, int s_tr, void *tu, int s_tu);