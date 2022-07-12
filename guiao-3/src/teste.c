#include <stdio.h>
#include <stdlib.h>
#include "../guiao-1/include/guiao1.h"
#include "../include/queries.h"
#include "../include/menu.h"

/**
 * @brief Function that add content to the file for pre-define tests
 */
static void add_content_tests(FILE * aux, char *s1,char*s2,char*s3)
{
    fprintf(aux,"%s\n",s1);
    fprintf(aux,"%s\n",s2);
    fprintf(aux,"%s\n",s3);
}
/**
 * @brief Function that does pre-define tests
 */
static void testes()
{
    char *t1 = "1";
    char *t2 = "2";
    char *t3 = "3";
    char *t4 = "4";
    char *t51 = "5 10 2010-01-01 2015-06-15";
    char *t52 = "5 20 2015-06-15 2019-12-31";
    char *t53 = "5 30 2010-01-01 2019-12-31";
    char *t61 = "6 10 Python";
    char *t62 = "6 20 Java";
    char *t63 = "6 30 C#";
    char *t71 = "7 2010-01-01";
    char *t72 = "7 2015-06-15";
    char *t73 = "7 2019-12-31";
    char *t81 = "8 10 2010-01-01";
    char *t82 = "8 20 2015-06-15";
    char *t83 = "8 30 2019-12-31";
    char *t9  = "9 15";
    char *t10 = "10 30";
    char *commands = "entrada/testes_queries.txt";
    FILE *aux = fopen(commands,"w");
    fprintf(aux,"%s\n",t1);
    fprintf(aux,"%s\n",t2);
    fprintf(aux,"%s\n",t3);
    fprintf(aux,"%s\n",t4);
    add_content_tests(aux,t51,t52,t53);
    add_content_tests(aux,t61,t62,t63);
    add_content_tests(aux,t71,t72,t73);
    add_content_tests(aux,t81,t82,t83);
    fprintf(aux,"%s\n",t9);
    fprintf(aux,"%s\n",t10);
    fclose(aux);
    start_queries(commands,1);

}

/**
 * @brief Function to see if the user wants to test our progtam by the interative program or by our pre-defined tests
 */
static void teste_no_args()
{
    char a[2];
    printf("Programa interativo (Escrever I) ou testes pré definidos (Escrever D)?\n");
    while(!fgets(a,2,stdin))
        putchar('\n');
    if(*a == 'I' || *a == 'i') interative_program(1);
    else if (*a == 'D' || *a == 'd') testes();
}

int main(int argc, char* argv[])
{
    printf("Começar testes\n");
    if(argc > 2){
        printf("Wrong number of arguments. %d\n",argc);
    } else if ((argc) == 2){
        printf("Começar a filtrar os ficheiros\n");
        guiao1();
        printf("Ficheiros filtrados\n");
        start_queries(argv[1],1);
    } else {
        printf("Começar a filtrar os ficheiros\n");
        guiao1();
        printf("Ficheiros filtrados\n");
        printMenu();
        teste_no_args();
    }
    printf("Acabou testes\n");
    return 0;
}