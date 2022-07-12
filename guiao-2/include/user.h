typedef struct user USER;

USER *init_users();
USER *realloc_users(USER *s, int *n);

char* returnTypes (USER *c, int i);
USER *start_user(int *s, void *u_aux, void *uc_aux, void *ts_aux, int *connection_size);
char* returnLogin (USER *c, int i);
int* getBotIds (USER *u, int size );
void *triplo_create(USER *u, int size);
int free_user(USER *u, int size);
int sort_user(USER *u,int size);
void *complete_triplo (USER *u, int size, void*aux_triplo, int s);
void *complete_quadruplo (USER *u, int size, void*aux_quadruplo, int s);
