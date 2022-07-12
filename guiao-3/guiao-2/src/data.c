#include "../include/data.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Struct of data
 */
struct data{
    unsigned short int ano;
    unsigned short int mes;
    unsigned short int dia;
    unsigned short int hora;
    unsigned short int min;
    unsigned short int seg;
};

/**
 * @brief Allocate memory to data.
 * @return An Data allocated.
 */
DATA init_data()
{
    DATA d = malloc(sizeof(struct data));
    return d;
}

/**
 * @brief Converts a string to typedef DATA.
 * @param hora String to convert.
 * @return The data converted.
 */
DATA string_to_data(char *hora)
{
    char *aux;
    DATA d = init_data();
    char *dia = malloc(9 * sizeof (char));
    dia = strsep(&hora," ");
    d->ano = (unsigned short int) strtol(strsep(&dia,"-"),&aux,10);
    d->mes = (unsigned short int) strtol(strsep(&dia,"-"),&aux,10);
    d->dia = (unsigned short int) strtol(dia,&aux,10);
    d->hora= (unsigned short int) strtol(strsep(&hora,":"),&aux,10);
    d->min = (unsigned short int) strtol(strsep(&hora,":"),&aux,10);
    d->seg = (unsigned short int) strtol(hora,&aux,10);
    return d;
}

/**
  * @brief Converts a string to typedef DATA, only considering the year, month and the day.
  * @param hora String to convert.
  * @return The data converted.
  */
DATA string_to_ano (char *dia)
{
    char *aux;
    DATA d = init_data();
    d->ano = (unsigned short int) strtol(strsep(&dia,"-"),&aux,10);
    d->mes = (unsigned short int) strtol(strsep(&dia,"-"),&aux,10);
    d->dia = (unsigned short int) strtol(dia,&aux,10);
    d->hora = 0; d->min = 0; d->seg = 0;
    return d;
}

/**
 * @brief Check if one data is inferior than the other one.
 * @param inf Inferior Data.
 * @param sup Superior Data.
 * @return 1 if the Data inf is inferior to sup, 0 if not.
 */
int dif_datas(DATA inf, DATA sup)
{
    if(inf->ano < sup->ano) return 1;
    if(inf->ano == sup->ano && inf->mes < sup->mes) return 1;
    if(inf->ano == sup->ano && inf->mes == sup->mes && inf->dia < sup->dia) return 1;
    if(inf->ano == sup->ano && inf->mes == sup->mes && inf->dia == sup->dia && inf->hora < sup->hora) return 1;
    if(inf->ano == sup->ano && inf->mes == sup->mes && inf->dia == sup->dia && inf->hora == sup->hora && inf->min < sup->min) return 1;
    if(inf->ano == sup->ano && inf->mes == sup->mes && inf->dia == sup->dia && inf->hora == sup->hora && inf->min == sup->min && inf->seg < sup->seg) return 1;
    return 0;
}

/**
 * @brief See if one year is inferior than the other one. 
 * @param inf Inferior year.
 * @param sup superior year.
 * @return 1 if the year inf is inferior to sup, 0 if not.
 */
int dif_anos(DATA inf, DATA sup)
{
    if(inf->ano < sup->ano) return 1;
    if(inf->ano == sup->ano && inf->mes < sup->mes) return 1;
    if(inf->ano == sup->ano && inf->mes == sup->mes && inf->dia < sup->dia) return 1;
    return 0;
}

/**
 * @brief Copy the information of one DATA to another one
 * @param d Source
 * @return Data copied.
 */
DATA copy_data(DATA d)
{
    DATA result = init_data();
    result->ano = d->ano;
    result->mes = d->mes;
    result->dia = d->dia;
    result->hora = d->hora;
    result->min = d->min;
    result->seg = d->seg;
    return result;
}

/**
 * @brief Function that free one Data.
 * @param d Data that we want to free.
 * @return 0.
 */
int free_data(DATA d)
{
    free(d);
    return 0;
}

/**
 * @brief Function that will return the difference bettween 2 datas.
 * @param d1_aux Data 1.
 * @param d2_aux Data 2.
 * @return The difference.
 */
int cmpfuncdatas(const void* d1_aux, const void* d2_aux)
{
    DATA d1 = (DATA) d1_aux;
    DATA d2 = (DATA) d2_aux;
    if(d1->ano != d2->ano) return d1->ano - d2->ano;
    else if (d1->mes != d2->mes) return d1->mes - d2->mes;
    else if (d1->dia != d2->dia) return d1->dia - d2->dia;
    else if (d1->hora != d2->hora) return d1->hora - d2->hora;
    else if (d1->min != d2->min) return d1->min- d2->min;
    else return d1->seg - d2->seg;
}

/**
 * @brief Function that returns a field of a DATA struct when given a DATA and an identifier
 * @param d DATA struct
 * @param f Field identifier, it's a char that can be 'A' (year), 'M' (month), 'D' (day), 'h' (hour), 'm'(minutes), 's'(seconds)
 * @return The value of the field 
 */
int return_field (DATA d, char f){
    int field;
    switch (f)
    {
        case 'A':
           field = d->ano;
        break;
        case 'M':
            field = d->mes;
        break;
        case 'D':
            field = d->dia;
        break;
        case 'h':
            field = d->hora;
        break;
        case 'm':
            field = d->mes;
        break;
        case 's':
            field = d->seg;
        break;
        default:
            field = 0;
    }
    return field;
}

/**
 * @brief Count the number of trace in a string
 * @param s String to count
 * @return The number of traces
 */
static int count_traco(char *s)
{
    int count = 0;
    for(int i = 0; s[i] != '\0'; i++)
    {
        if(s[i] == '-')
            count++;
        else if(s[i] < 48 || s[i] > 57)
            return -1;
    }
    return count;
}

/**
 * @brief Function to validate a data
 * @param s String that has the data
 * @return 1 if it is valid, 0 if not.
 */
int validate_data(char *s)
{
    if (s == NULL || count_traco(s) != 2) return 0;
    int r = 1;
    DATA d = string_to_ano(s);
    int bissexto = d->ano % 4;
    int mesPar = d->mes % 2;
    if      (d->mes < 1 || d->mes > 12) r = 0;
    else if (d->dia < 0 || d->dia > 31) r = 0;
    else if ((bissexto == 0 && d->mes == 2 && d->dia > 29) || (bissexto != 0 && d->mes == 2 && d->dia > 28)) r = 0;
    else if (mesPar == 0 && d->dia > 30 && d->mes < 8) r = 0;
    else if (mesPar == 1 && d->dia > 30 && d->mes >= 8) r = 0;
    free_data(d);
    return r;
}