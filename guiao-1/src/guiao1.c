#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "../includes/exercicio1.h"
#include "../includes/exercicio2.h"

/**
 * @brief Main function of guiao1.c
 * @param argc integer
 * @param argv string
 * @return 0
 */
int main (int argc, char* argv[]){
    if (argc != 2) printf ("Wrong number of arguments");
    else if (strcmp (argv[1], "exercicio-1") == 0) ex1();
    else if (strcmp (argv[1], "exercicio-2") == 0) ex2();
    return 0;
}
