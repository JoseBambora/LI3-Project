typedef struct tuplo TUPLO;

TUPLO* init_tuplo();
TUPLO* add_elem_tuplo(TUPLO *a, char *s,int v,int *N,int size);
TUPLO* add_tuplo(TUPLO *a, char *str, int *N,int size,int num, int *inc);
int sort_tuplo(TUPLO *a,int size);
int free_tuplo(TUPLO *a, int size);
int add_content_tuplo (TUPLO *t, int size, int num, void* File);
int add_content_tuplo2 (TUPLO *t, int size, int num, void* File);
