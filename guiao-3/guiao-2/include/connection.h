typedef struct userConnections CONNECTION;

CONNECTION *init_userConnections();
CONNECTION *realloc_usersConnections(CONNECTION *s, int *n);
CONNECTION *start_connections( int*s);

void *add_elem_Connection(CONNECTION *uc, int id, int *idA,int amigosSize, int size, int *n);

int sort_connection(CONNECTION * u, int size);
int binary_search_amigos (CONNECTION *uc, int authorID, int ind);
int find_index_uc(CONNECTION *uc, int commiterID ,int size);
int free_Connection (CONNECTION *c, int size);
