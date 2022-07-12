typedef struct user USER;


char* returnTypes_line (char *line);
int start_user();
char* returnLogin (USER *c, int i);
int* getBotIds (USER *u, int size );
void *triplo_create(USER *u, int size);
void *complete_triplo (void*aux_triplo, int s);
void *complete_quadruplo (void*aux_quadruplo, int s);
int returnID_line (char *line);