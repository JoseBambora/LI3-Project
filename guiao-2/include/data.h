typedef struct data *DATA;

char *strsep(char **stringp, const char *delim);

DATA init_data();
DATA string_to_data(char *hora);
DATA string_to_ano (char *dia);
int dif_datas(DATA inf, DATA sup);
int dif_anos(DATA inf, DATA sup);
DATA copy_data(DATA d);
int free_data(DATA d);
int cmpfuncdatas(const void* d1_aux, const void* d2_aux);
