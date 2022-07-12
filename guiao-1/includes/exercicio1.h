/**
 * \brief Struct that handles the data variables
 */
typedef struct 
{
    int dia; int mes; int ano;
    int hora; int minuto; int segundo;
} Data;

/**
 * \brief Struct that handles the array variables
 */
typedef struct 
{
    int *array_f;
    int size;
} Array_f;


int isNumber (char *s);
int monthNumber(char*str);
Data separateTime (char *str);
Data getTime();
int calcDifDatas (Data liminf, Data limsup);
Data validateData(Data d);
Data addFuso (char c, Data d, int horaFuso, int minutoFuso);
Array_f stringToArray(char *str);
int checkT (char *type);
Data invalidData();
Data stringToData (char *hora);
int checkData (char *data);
int checkPos (int num);
int checkString (char *login);
int checkList (char *list, int size);
int isBool (char *str);
int parserUsers (char *line);
int parserCommits (char *line);
int parserRepos (char *line);
int users();
int commits();
int repos();
int ex1();
