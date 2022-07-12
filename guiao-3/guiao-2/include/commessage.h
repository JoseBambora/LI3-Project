typedef struct commitmessage *COMMITMESSAGE;
COMMITMESSAGE startcommitmessage(int *size_quadruplo);
int free_cm(COMMITMESSAGE cm, int size_cm);
int add_content_cm (COMMITMESSAGE cm ,int size, int num, void *newfile,void *);
