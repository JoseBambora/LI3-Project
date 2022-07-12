typedef struct triplo TRIPLO;
TRIPLO* init_triplo();
TRIPLO* realloc_triplo(TRIPLO *tr, int *n);
void* add_elem_triplo(TRIPLO *atr, int id, char *login, int qtty, int size,int *N);
int sort_triplo(TRIPLO *atr, int size);
int return_id_triplo(TRIPLO *t, int indice);
int set_str_triplo(TRIPLO *a, int indice, char *str);
int free_triplo(TRIPLO *a, int size);
int add_content_triplo (TRIPLO *t, int size, int num, void* File);
int add_content_triplo2 (TRIPLO *t, int size, int num, void* File);
int inc_qtty(TRIPLO *t, int size, int id);
