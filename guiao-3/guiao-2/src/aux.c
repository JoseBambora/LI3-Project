#include "../include/aux.h"
#include "../../include/menu.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>


/**
 * @brief  Function that compares two integers 
 * @param a 
 * @param b 
 * @return the result of the comparison
 */
int compareInts (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}
/**
 * @brief Function that calculates the size of an integer array
 * @param array integer array
 * @return i, a variable that contains the size of the array
 */
int size_array(int *array)
{
  int i = 0;
  while(array[i] != -1) i++;
  return i;
}

/**
 * @brief Binary search funtion
 * @param array integer array where the search will occur
 * @param elem integer element to find on the array
 * @param size integer variable with the value of the size of the array
 * @return 0
 */
int pesquisaBinaria (int *array, int elem, int size)
{
    int inf = 0;
    int sup = size-1;
    int mid;
    while (inf <= sup)
    {
        mid = (inf + sup)/2;
        if (elem == array[mid]) return 1;
        if (elem < array[mid]) sup = mid-1;
        else inf = mid+1;
    }
    return 0;
}

/**
 * @brief Function that returns the name of the new file.
 * @param n Number that the of the new file will depend.
 * @return The file name.
 */
char *name_newfile(int n)
{
    char *num = malloc(30 * sizeof (char));
    sprintf(num, "%d", n);
    int size = 14 + strlen(num) + 12;
    char *newFile = malloc(size * sizeof(char));
    strcpy(newFile,"saida/outputs/command");
    strcat(newFile,num);
    strcat(newFile,"_output.txt");
    free(num);
    return newFile;
}

/**
 * @brief  Function that turns a string into an array
 * @param str string given
 * @param n size of the string
 * @return the array 
 */
int *str_array(char *str, int n) 
{
    int *a = malloc((n) * sizeof (int));
    int i;
    str++; 
    if(*str == ']') 
    {
        free (a);
        return NULL;
    }
    char *aux;
    for(i = 0; i < n - 1; i++)
    {
        aux = strsep(&str,", "); 
        a[i] = atoi(aux); 
    }
    aux = strsep(&str,"]"); 
    a[i] = atoi(aux);
    return a;
}

/**
 * @brief  Function that concatenates 2 given arrays
 * @param a one of the array that we want to concatenate
 * @param asize it's size
 * @param b one of the array that we want to concatenate
 * @param bsize it's size
 * @return the array 
 */
int* concatena_arrays (int a[],int asize, int b[], int bsize){
    int csize = asize+bsize;
    int* c = malloc (sizeof(int)*csize);
    for (int i=0; i<asize; i++ )
        c[i] = a[i];
    for (int j = 0; j < bsize; j++)
        c[j + asize] = b[j];
    qsort(c,sizeof(int),csize,compareInts);
    return c;       
}

/**
 * @brief  Function that copies the info in an array to another
 * @param a  array that we want to copy
 * @param asize it's size
 * @return the array with the info that was copied
 */
int* copyArray (int a[], int size) {
    int *r = malloc (sizeof(int)*size);
    for (int i=0; i<size;i++) r[i] = a[i];
    return r;
}

/**
 * @brief Function that generates a name to a certain format.
 * @param n The number that will determine the final string.
 * @param r String that has already memory allocated
 * @return The final string.
 */
static char *generate_name(int n, char *r)
{
    char *num = malloc(30 * sizeof (char));
    sprintf(num, "%d", n);
    strcat(r,"output");
    strcat(r,num);
    strcat(r,".txt");
    free(num);
    return r;
}

/**
 * @brief Function that will get the name of the file that we want to create or to see its own information, depending if the first line is equal to data.
 * @param pasta Folder to search information.
 * @param data String with the parameters.
 * @return The name of the file that we want to create or see its own information.
 */
char *where(char *pasta,char *data)
{
    int n = 1;
    char *str_aux = malloc(30 * sizeof (char));
    char *r = malloc(60 * sizeof (char));
    strcpy(r,pasta);
    r = generate_name(n,r);
    FILE *file = fopen(r,"r");
    while(file && fgets(str_aux,30,file))
    {
        if(strcmp(str_aux,data) == 0)
            break;
        n++;
        strcpy(r,pasta);
        r = generate_name(n,r);
        file = fopen(r,"r");
    }
    free(str_aux);
    return r;
}

/**
 * @brief Function to create a comparasion file.
 * @param file1 File name of one file.
 * @param file2 File name of one file.
 * @param iterativo 0 if we are not in the iterative program 1 otherwise
 * @param data Parameters
 */
static void copy_info_files(char *file1, char*file2, int iterativo,char *data)
{
    if (iterativo){
        print_traco3(79);
        printw("Ficheiros de comparação (expected files) inexistente.\n");
        printw("A criar ficheiro de comparação para futuros testes.\n");
    }
    else {
        printf("Ficheiros de comparação (expected files) inexistente.\n");
        printf("A criar ficheiro de comparação para futuros testes.\n");
    }
    char *str1 = malloc(sizeof(char) * 1000);
    FILE *f1 = fopen(file1,"r");   
    FILE *f2 = fopen(file2,"w");
    while(fgets(str1,1000,f1))
        fprintf(f2,"%s",str1);
    fclose(f1);
    fclose(f2);
    free(str1);
    if (iterativo) printw("Ficheiro %s criado.\n", file2);
    else printf("Ficheiro %s criado.\n", file2);
}

/**
 * @brief Function that validates the result of queries.
 * @param file1 File name of one file.
 * @param file2 File name of one file.
 * @param iterativo 0 if we are not in the iterative program 1 otherwise
 * @param param If the query has parameters
 * @param data Parameters
 * @param query Number of query
 */
void validate_files(char *file1, char*file2,char *file3, int iterativo, int param, char*data, int query)
{
    char *str1 = malloc(sizeof(char) * 1000);
    char *str2 = malloc(sizeof(char) * 1000);
    int n = 1;
    FILE *f1 = fopen(file1,"r");
    FILE *f2 = fopen(file2,"r");
    if(!f2)
        copy_info_files(file3,file2,iterativo,data);
    else
    {
        if(param) str2 = fgets(str2,500,f2);
        while(fgets(str1,500,f1))
        {
            if(!fgets(str2,500,f2)) 
            {
                n = 0;
                break;
            }
            else 
            {
                char *aux = str2;
                if(query == 8) 
                {
                    aux = strsep(&aux,";");
                    strcat(aux,"\n");
                }
                if(strcmp(aux,str1) != 0)
                {
                    n = 0;
                    break;
                }
            }
        }
        if(n){
            if(iterativo) {
                print_traco3(79);
                printw("Resultado certo\n");
            }
            else printf("Resultado certo\n");
        }else{
            if(iterativo) {
                print_traco3(79);
                printw("Resultado errado\n"); 
            }
            else printf("Resultado errado\n");
            }   
        fclose(f1);
        fclose(f2);
    }
    free(str1); 
    free(str2);
}

/**
 * @brief Function that validates a language
 * @param lan language to be validated
 * @return 0 if invalid 1 if valid
 */
int validate_language(char *lan)
{
  int r = 1;
  if(!lan || *lan == '\n' || *lan == '\0') r = 0;
  return r;
}