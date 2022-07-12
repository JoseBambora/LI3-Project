#include "../include/aux.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
    strcpy(newFile,"saida/command");
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
    int *a = malloc((n+1) * sizeof (int));
    int i;
    str++; 
    if(*str == ']') 
    {
        *a = -1;
        return a;
    }
    char *aux;
    for(i = 0; i < n - 1; i++)
    {
        aux = strsep(&str,", "); 
        a[i] = atoi(aux); 
    }
    aux = strsep(&str,"]"); 
    a[i] = atoi(aux);
    a[i+1] = -1; 
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
  int csize= asize+bsize;
  int ia = 0, ib =0, ka = 1, kb = 1;
  int* c = malloc (sizeof(int)*csize);
  for (int i=0; i<csize; i++ ) {
        if(ia >= asize) ka = 0;
        if(ib >= bsize) kb = 0; 
        if (ka && kb && a[ia]< b[ib]) {c[i] = a[ia]; ia++; }
        else if (ka && kb) {c[i] = b[ia]; ib++;} 
        else if (ka) {c[i] = a[ia]; ia++; }
        else if (kb) {c[i] = b[ia]; ib++;} 
  }
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


