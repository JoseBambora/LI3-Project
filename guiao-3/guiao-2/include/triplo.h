typedef struct triplo TRIPLO;
TRIPLO* init_triplo();
void* add_elem_triplo(TRIPLO *atr, int id, char *login, int qtty, int size,int *N);
int sort_triplo(TRIPLO *atr, int size);
int free_triplo(TRIPLO *a, int size);
int add_content_triplo (TRIPLO *t, int size, int num, void* File, void* queryFile);
int add_content_triplo2 (TRIPLO *t, int size, int num, void* File,void* queryFile);
int inc_qtty(TRIPLO *t, int size, int id);
TRIPLO *complete_triplo_tuplo(TRIPLO *tr, int s_tr, void *tu, int s_tu);
