#include "../guiao-1/include/guiao1.h"
#include "../include/queries.h"
#include "../include/menu.h"
#include <stdio.h>
#include <ncurses.h>

int main(int argc, char* argv[])
{
    if(argc > 2){
        printf("Wrong number of arguments. %d\n",argc);
    } else if ((argc) == 2){
        printf("Começar a filtrar os ficheiros\n");
        guiao1();
        printf("Ficheiros filtrados\n");
        start_queries(argv[1],0);
    } else {
        printf("Começar a filtrar os ficheiros\n");
        guiao1();
        printf("Ficheiros filtrados\n");
        printMenu();
        interative_program(0);
    }
    printf("Acabou o programa.\n"); 
    return 0;
}