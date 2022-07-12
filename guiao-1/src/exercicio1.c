/**
 * @file exercicio1.c
 * @brief This file contains the functions related to exercice 1
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "../includes/exercicio1.h"


/**
 * @brief  Function that verifies if the string contains a number
 * @param s string
 * @return 1 if the string has in fact a number else returns 0
 */
int isNumber(char s[])
{
    if (s == NULL) return 0;
    for (int i = 0; s[i]!= '\0'; i++)
    {
        if (isdigit(s[i]) == 0) return 0;
    }
    return 1;
}

/**
 * @brief  Function that when given a string compares it to the first 3 letters of the months of the calendar returning the number of the month from 1 to 12
 * @param str string
 * @return the number of the month from 1 to 12, 0 if the string is not equal to the first three leters of a numer.
 */
int monthNumber(char*str){
    if (strcmp(str,"Jan")==0) return 1;
    if (strcmp(str,"Feb")==0) return 2;
    if (strcmp(str,"Mar")==0) return 3;
    if (strcmp(str,"Apr")==0) return 4;
    if (strcmp(str,"May")==0) return 5;
    if (strcmp(str,"Jun")==0) return 6;
    if (strcmp(str,"Jul")==0) return 7;
    if (strcmp(str,"Aug")==0) return 8;
    if (strcmp(str,"Sep")==0) return 9;
    if (strcmp(str,"Oct")==0) return 10;
    if (strcmp(str,"Nov")==0) return 11;
    if (strcmp(str,"Dec")==0) return 12;
    return 0;
}

/**
 * @brief  Function separates the parts of a string that represents a date and stores them on a d Data struct
 * @param str string
 * @return d
 */
Data separateTime (char *str){
    Data d;
    str = str+4;
    char *mes = strsep(&str," ");
    str++;
    d.mes = monthNumber(mes);
    d.dia = atoi(strsep(&str," "));
    char *horas = strsep(&str," ");
    sscanf(horas,"%d:%d:%d", &d.hora,&d.minuto,&d.segundo);
    d.ano = atoi(str);
    return d;
}

/**
 * @brief  Function gets the current time 
 * @return 1 if the string has in fact a number else returns 0
 */
Data getTime(){
    time_t tempo;
    time (&tempo);
    char *str = ctime(&tempo);
    return separateTime(str);
}

/**
 * @brief  Function that calculates the diffenrence in seconds between two dates
 * @param liminf Data 
 * @param limsup Data
 * @return the diffence between the date on the second argument and the date on the first argument
 */
int calcDifDatas (Data liminf, Data limsup){
    if (limsup.ano < liminf.ano) return 0;
    if (limsup.ano == liminf.ano && limsup.mes < liminf.mes) return 0;
    if (limsup.ano == liminf.ano && limsup.mes == liminf.mes && limsup.dia < liminf.dia) return 0;
    if (limsup.ano == liminf.ano && limsup.mes == liminf.mes && limsup.dia == liminf.dia)
    {
        if (limsup.hora < liminf.hora) return 0;
        if (limsup.hora == liminf.hora && limsup.minuto < liminf.minuto) return 0;
        if (limsup.hora == liminf.hora && limsup.minuto == liminf.minuto && limsup.segundo < liminf.segundo) return 0;
    }
    return 1;
}

/**
 * @brief  Function that turns a inexisting date into a real date
 * @param d Data
 * @return d Data, converted into a new valid format
 */
Data validateData(Data d){
    if (d.hora > 24) {
        d.dia++;
        d.hora-=24;
    }
    if (d.hora < 0){
        d.dia --;
        d.hora += 24;
    }
    if (d.dia > 31 || (d.dia > 30 && (d.mes % 2 ==0) && d.mes < 8) || (d.dia > 30 && (d.mes % 2 !=0) && d.mes >= 8) || (d.dia > 29 && d.mes == 2) || (d.ano % 4 != 0 && d.dia > 28 && d.mes == 2)){
        d.mes++;
        d.dia = 1;
    }
    if (d.dia == 0){
        d.mes--;
        if      (d.mes == 2 && d.ano % 4 == 0) d.dia = 29;
        else if (d.mes == 2 && d.ano % 4 != 0) d.dia = 28;
        else if (d.mes % 2 == 0 && d.mes < 8)  d.dia = 30;
        else if (d.mes % 2 != 0 && d.mes < 8)  d.dia = 31;
        else if (d.mes % 2 == 0 && d.mes >= 8) d.dia = 31;
        else if (d.mes % 2 != 0 && d.mes >= 8) d.dia = 30;
    }
    if (d.mes == 0) 
    {
        d.ano--; 
        d.mes = 12; 
        d.dia = 31;
    }
    if (d.mes == 13) 
    {
        d.ano++; 
        d.mes = 1; 
        d.dia = 1;}
    return d;
}

/**
 * @brief  Function that converts a string into an array
 * @param str string
 * @return an array that contains the information located inside the given string
 */
Array_f stringToArray(char *str)
{
    int size = 0;
    int buffer = 1;
    Array_f Array_followers;
    Array_followers.array_f = malloc (30*sizeof(int));
    if(strcmp(str,"[]") == 0)
    { 
        Array_followers.size = 0; 
        return Array_followers;
    }
    str++; // avança uma posição para pular o '['
    str[strlen(str) - 1] = ',';
    for(int i = 0; (*str)!= '\0'; i++)
    {
        char *num = strsep(&str,",");
        num++;
        if (isNumber(num) == 0) {Array_followers.size = -1; return Array_followers;}
        if (size == 30*buffer) {buffer++; Array_followers.array_f = realloc (Array_followers.array_f,buffer*30*sizeof(int));}
        Array_followers.array_f[size] = atoi(num);
        size++;
    }
    Array_followers.size = size;
    return Array_followers;
}

/**
 * @brief  Function that verifies if the string within the "Type" variable is indeed one of the possible types 
 * @param type string
 * @return 1 if the information is one of the possible types, else 0
 */
int checkT (char *type){
    if (type == NULL) return 0;
    if (strcmp (type, "User") == 0 || strcmp (type, "Organization") == 0 || strcmp(type, "Bot") == 0) return 1;
    return 0;
}

/**
 * @brief  Function checks if a Date is valid
 * @return d Data
 */
Data invalidData()
{
    Data d;
    d.dia = -1;
    return d;
}

/**
 * @brief  Function that converts the variable data in string format into the format Data
 * @param hora string
 * @return the variable data in the expected format
 */
Data stringToData (char *hora){
    if(strlen(hora) > 19) return invalidData();
    Data d;
    char *dia;
    dia = strsep(&hora," ");
    int r;
    r = sscanf(dia,"%d-%d-%d", &d.ano,&d.mes,&d.dia);
    if(r != 3) return invalidData();
    r = sscanf(hora,"%d:%d:%d", &d.hora,&d.minuto,&d.segundo);
    if(r != 3) return invalidData();
    return d;
}

/**
 * @brief  Function that verifies if the information within the data variable is accurate according to the given format
 * @param data string
 * @return 1 if it is accurate, else 0
 */
int checkData (char *data){
    if (data == NULL) return 0;
    Data d = stringToData(data);
    Data d_atual = getTime();
    if (d.dia == -1) return 0;
    if (d.mes < 1 || d.mes > 12) return 0;
    if (d.ano < 2005  || (d.ano == 2005 && d.mes < 4) || (d.ano == 2005 && d.mes == 4 && d.dia < 7)) return 0;
    int bissexto = d.ano % 4;
    int mesPar = d.mes % 2;
    if ((bissexto == 0 && d.mes == 2 && d.dia > 29) || (bissexto != 0 && d.mes == 2 && d.dia > 28)) return 0;
    if (mesPar == 0 && d.dia > 30 && d.mes < 8) return 0;
    if (mesPar == 1 && d.dia > 31 && d.mes < 8) return 0;
    if (mesPar == 0 && d.dia > 31 && d.mes >= 8) return 0;
    if (mesPar == 1 && d.dia > 30 && d.mes >= 8) return 0;
    if (d.hora < 0 || d.hora > 23 || d.minuto < 0 || d.minuto > 59 || d.segundo < 0 || d.segundo >  59) return 0;
    if (d_atual.ano < d.ano || (d_atual.ano == d.ano && d_atual.mes < d.mes) || (d_atual.ano == d.ano && d_atual.mes == d.mes && d_atual.dia < d.dia)) return 0;
    if (d_atual.ano == d.ano && d_atual.mes == d.mes && d_atual.dia == d.dia)
    {
        if (d_atual.hora < d.hora || (d_atual.hora == d.hora && d_atual.minuto < d.minuto) || (d_atual.hora == d.hora && d_atual.minuto == d.minuto && d_atual.segundo < d.segundo))
        return 0;    
    } 
    return 1;
}

/**
 * @brief Function that evaluates if an integer is positive
 * @param num integer 
 * @return 1 if it is indeed an positive integer , else 0
 */
int checkPos (int num){
    if (num < 0) return 0;
    return 1;
}

/**
 * @brief Function that evaluates if a string on our files is valid
 * @param login string
 * @return 1 if the string is valid
 */
int checkString (char *login) 
{
    if ((login == NULL) || (*login == '\0') || (*login == '\n')) return 0;
    return 1;
}    

/**
 * @brief Function that evaluates if the parts of the .csv files that are represented as a list are valid
 * @param list string
 * @param size integer
 * @return 1 if it is the list is valid , 0 otherwise
 */
int checkList (char *list, int size)
{
    int i;
   if(list == NULL || *list != '[' || list[strlen(list)-1] != ']') return 0;
    Array_f array_list = stringToArray(list);
    if(array_list.size != size) return 0;
    for(i = 0; i < size; i++) if (array_list.array_f[i] < 0) return 0;
    return 1;
}

/**
 * @brief Function that checks if a string is equal to the words "True" and "False" that represent Boolean values
 * @param str string
 * @return 1 if the string is equal to the words "True" or "False", 0 otherwsise
 */
int isBool (char *str){
    if (strcmp(str,"True") == 0 || strcmp(str,"False") == 0) return 1;
    return 0;
}

/**
 * @brief Function that does the parsing of the lines on users.csv
 * @param line string upon which the parsing is done
 * @return k a variable that is equal to 1 if the line is validated on the parsing process or 0 if not
 */
int parserUsers (char *line){ 
    //char *sobra;
    int i = 0, k = 1, followers = 0, following = 0;
    for (; i < 10 && k == 1; i++)
    {
        char *token;
        if (line == NULL || *line == ';') return 0;
        token = strsep(&line,";");
        if (token == NULL) return 0; 
        switch (i){
         case 0://id
                if (isNumber(token)) k = checkPos(atoi(token));
                else k = 0;
                break;
            case 1://login
                k = checkString(token);
                break;
            case 2://type
                 k = checkT(token);
                break;
            case 3://data
                k = checkData(token);
                //printf("%d\n",k);
                break;
            case 4://followers
                if (isNumber(token)) k = checkPos(atoi(token));
                else k = 0;
                followers = atoi(token);
                break;
            case 5://follower_list
                k = checkList(token,followers);
                break;
             case 6://following
                if (isNumber(token)) k = checkPos(atoi(token));
                else k = 0;
                following = atoi(token);
                break;
            case 7://following_list
                k = checkList(token, following);
                break;
            case 8://check_pg
                if (isNumber(token)) k = checkPos(atoi(token));
                else k = 0;
                break;
            case 9://check_Prep
                token[strlen(token)-2] = '\0';
                if (isNumber(token)) k = checkPos(atoi(token));
                else k = 0;
                break;
        }
    }
    return k;
}

/**
 * @brief Function that does the parsing of the lines on commits.csv
 * @param line string upon which the parsing is done
 * @return k a variable that is equal to 1 if the line is validated on the parsing process or 0 if not
 */
int parserCommits (char *line) {
    //char *sobra;
    int i = 0, k = 1;    
    for (; i < 4 && k == 1; i++)
    {
        char *token;
       if ((line == NULL || *line == ';') && i != 4) return 0;
        token = strsep(&line,";");
        if (token == NULL) return 0;
        switch (i){
            case 0://repo_id
                if (isNumber(token)) k = checkPos(atoi(token));
                else k = 0;
                break;
            case 1://commiter_id
                if (isNumber(token)) k = checkPos(atoi(token));
                else k = 0;
                break;
            case 2://author_id
                if (isNumber(token)) k = checkPos(atoi(token));
                else k = 0;
                break;
            case 3://data
                k = checkData(token);
                break;
        }
    }
    return k;
}

/**
 * @brief Function that does the parsing of the lines on repos.csv
 * @param line string upon which the parsing is done
 * @return k a variable that is equal to 1 if the line is validated on the parsing process or 0 if not
 */
int parserRepos (char *line){
    //char *sobra;
    int i = 0, k = 1;
    for (; i < 14 && k == 1; i++)
    {
        char *token, token2[20];
        if ((line == NULL || *line == ';') && i != 5) return 0;
        token = strsep(&line,";");
        if (token == NULL) return 0;
        switch (i){
            case 0://id
                if (isNumber(token)) k = checkPos(atoi(token));
                else k = 0;
                break;
            case 1://owner_id
                if (isNumber(token)) k = checkPos(atoi(token));
                else k = 0;
                break;
            case 2://full_name
                k = checkString(token);
                break;
            case 3://license
                k = checkString(token);
                break;
            case 4://has_wiki
                k = isBool(token);
                break;
            case 5://description
                //k = checkString(token);
                break;
             case 6://language
                k = checkString(token);
                break;
            case 7://default_branch
                k = checkString(token);
                break;
            case 8://created_at
                strcpy(token2,token);
                k = checkData(token);
                //Data created = stringToData(token2);
                break;
            case 9://updated_at
                strcpy(token2,token);
                k = checkData(token);
                //Data updated = stringToData(token2);
                //if (k!=0) k = calcDifDatas(created,updated);
                break;
            case 10://forks_count
                if (isNumber(token)) k = checkPos(atoi(token));
                else k = 0;
                break;
            case 11://open_issues
                if (isNumber(token)) k = checkPos(atoi(token));
                else k = 0;
                break;
            case 12://stargazers_count
                if (isNumber(token)) k = checkPos(atoi(token));
                else k = 0;
                break;
            case 13://size
                token[strlen(token)-2] = '\0';
                if (isNumber(token)) k = checkPos(atoi(token));
                else k = 0;
                break;
        }
    }
    return k;
}
/**
 * @brief Function that sends the lines of users.csv to the respective parser and writes the valid lines into the file users-ok.csv
 * @param line string upon which the parsing is done
 * @return 0
 */
int users()
{
    FILE *ficheiro, *newFile; 
    ficheiro = fopen("entrada/users.csv","r");
    newFile = fopen ("saida/users-ok.csv","w");
    char *line = malloc(200000* sizeof (char));
    char *line2 = malloc(200000 * sizeof (char));
    char *s = malloc(200000 * sizeof (char));
    s = fgets (line, 200000, ficheiro);
    fputs(line,newFile);
    int val = 1;
    while (s != NULL)
    {
        s = fgets(line,200000,ficheiro);
        strcpy(line2,line);
        val = parserUsers(line);
        if (val==1) fputs(line2,newFile);
    }
    fclose(ficheiro);
    fclose(newFile);
    return 0;
}

/**
 * @brief Function that sends the lines of commits.csv to the respective parser and writes the valid lines into the file commits-ok.csv
 * @param line string upon which the parsing is done
 * @return 0
 */
int commits()
{
    FILE *ficheiro, *newFile; 
    ficheiro = fopen("entrada/commits.csv","r");
    newFile = fopen ("saida/commits-ok.csv","w");
    char *line = malloc(2000 * sizeof (char));
    char *line2 = malloc(2000 * sizeof (char));
    char *s = malloc(2000 * sizeof (char));
    s = fgets (line, 2000, ficheiro);
    fputs(line,newFile);
    int val = 1;
    while (s != NULL)
    {
        s = fgets(line,2000,ficheiro);
        strcpy(line2,line);
        val = parserCommits(line);
        if (val==1) fputs(line2,newFile);
    }
    fclose(ficheiro);
    fclose(newFile);
    return 0;
}
/**
 * @brief Function that sends the lines of repos.csv to the respective parser and writes the valid lines into the file repos-ok.csv
 * @param line string upon which the parsing is done
 * @return 0
 */

int repos()
{
    FILE *ficheiro, *newFile; 
    ficheiro = fopen("entrada/repos.csv","r");
    newFile = fopen ("saida/repos-ok.csv","w");
    char *line = malloc(2000 * sizeof (char));
    char *line2 = malloc(2000 * sizeof (char));
    char *s = malloc(2000 * sizeof (char));
    s = fgets (line, 2000, ficheiro);
    fputs(line,newFile);
    int val = 1;
    while (s != NULL)
    {
        s = fgets(line,2000,ficheiro);
        strcpy(line2,line);
        val = parserRepos(line);
        if (val==1) fputs(line2,newFile);
    }
    fclose(ficheiro);
    fclose(newFile);
    return 0;
}

/**
 * @brief Function that activates the other functions of the first exercise
 * @return 0
 */
int ex1()
{
    users();
    commits();
    repos();
    return 0;
}

