typedef struct commitmessage *COMMITMESSAGE;
COMMITMESSAGE startcommitmessage(void *us, void*co, int size, int usize, int *size_quadruplo);
int free_cm(COMMITMESSAGE cm, int size_cm);
int add_content_cm (COMMITMESSAGE cm ,int size, int num, void *newfile);
