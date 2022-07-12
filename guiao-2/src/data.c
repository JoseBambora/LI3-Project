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
