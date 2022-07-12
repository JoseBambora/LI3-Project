typedef struct tuplo TUPLO;

TUPLO* init_tuplo();
TUPLO* add_elem_tuplo(TUPLO *a, char *s,int v,int *N,int size);
TUPLO* add_tuplo(TUPLO *a, char *str, int *N,int size,int num, int *inc);
int sort_tuplo(TUPLO *a,int size);
int free_tuplo(TUPLO *a, int size);
char *return_tuplo_str(TUPLO *a, int ind);
int add_content_tuplo (TUPLO *t, int size, int num, void* File, void *query8file);
int add_content_tuplo2 (TUPLO *t, int size, void* File, void *quer7file);
int pesquisa_bin_tuplo(TUPLO *t,int inf, int sup, int id);
