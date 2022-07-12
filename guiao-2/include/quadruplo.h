typedef struct quadruplo  QUADRUPLO;
QUADRUPLO* init_quadruplo();
QUADRUPLO* add_elem_quadruplo(QUADRUPLO *atr, int id, char *login, int qtty, int size,int *N ,int repo_id);
int free_quadruplo(QUADRUPLO *t, int size);
int add_content_quadruplo (QUADRUPLO *t, int size, int num, void* File);
int return_id_quadruplo(QUADRUPLO *t, int indice);
int set_str_quadruplo(QUADRUPLO *t, int indice, char *str);
