typedef struct stringarray STRARRAY; 

STRARRAY* init_strarray();
STRARRAY* add_elem_strarray (STRARRAY *sa, char *str, int *N, int size);
int free_str_array(STRARRAY *sa, int size);
void *strarray_language_qtty(STRARRAY *sa, int size, int *s_tuplo);
