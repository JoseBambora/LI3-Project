#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "../guiao-2/include/data.h"

/**
* @brief Function that prints the name of the parameters shown on the terminal that vary from each query
* @param query number of the query whose results the user wants to see
*/
static char* format(int query)
{
    char *r = malloc(sizeof(char) * 81);
    switch (query)
    {
        case 1:
            strcpy(r,"| Total de Bots, Total de Organizacoes, Total Users                           |\n");
            break;
        case 2:
            strcpy(r,"| Total de Colaboradores  / Total de Repos                                    |\n");
            break;
        case 3:
            strcpy(r,"| Number of Repos that has bot as colaborator                                 |\n"); 
            break;
        case 4:
            strcpy(r,"| Total de Commits / Total de Users                                           |\n");
            break;
        case 5:
            strcpy(r,"| ID do User      | Login do User                          | Commit Quantity  |\n");
            break;
        case 6:
            strcpy(r,"| ID do User      | Login do User                          | Commit Quantity  |\n");
            break;
        case 7:
            strcpy(r,"| ID do Repo      | Descricao do Repo                                         |\n");
            break;
        case 8:
            strcpy(r,"| Language        | Quantidade de ocorrencias                                 |\n");
            break;
        case 9:
            strcpy(r,"| ID do User      | Login do User                                             |\n");
            break;
        case 10:
            strcpy(r,"| ID do User    | Login do User   | Comprimento da mensagem | ID do Repo      |\n");
            break;
        default:
            break;
    }
    return r;
}

/**
 * @brief Function that returns the number of the lines of a certain file.
 * @return The number of lines.
 */
static int num_lines(FILE *name)
{
    int r = -1;
    char *s = malloc(sizeof(char) * 3000);
    while(fgets(s,3000,name))
        r++;
    free(s);
    return r;
}

/**
 * @brief Returns the number of pages.
 * @param name The File to get the number of pages.
 * @param i Integer that will determine the number of pages.
 * @return The number of pages.
 */
static int num_pages(FILE *name, int i)
{
    int line = num_lines(name);
    return line % i == 0 ? line / i : (line/i) + 1;
}

/**
 * @brief Prints a string in a certain amount of character on the window when using ncurses.
 * @param str String to print.
 * @param lim The size of the print.
 */
static void print_string(char *str,int lim)
{
    printw("| ");
    int k = 1;
    for(int i = 0; i < lim; i++)
    {
        if(k && str[i] != '\0' && str[i] != '\n') addch(str[i]);
        else 
        {
            printw(" ");
            k = 0;
        }
    }
    printw(" ");
}

/**
 * @brief Prints a certain string devided by 2 on the window of ncurses.
 * @param line String to print.
 */
static void print_line(char *line)
{
    char *s = strsep(&line,";");
    print_string(s,15);
    print_string(line,56);
    printw(" |\n");
}

/**
 * @brief Function that prints lines for queries 5 and 6.
 * @param line given string.
 */
static void print_line2(char *line)
{
    char *s1= strsep(&line,";");
    char *s2 = strsep(&line,";");
    print_string(s1,15);
    print_string (s2,38);
    print_string(line,15);
    printw(" |\n");
}

/**
 * @brief Function that prints lines for queries 2,3,4
 * @param line given string.
 */
static void print_line3(char *line)
{
    print_string(line,74);
    printw(" |\n");
}

/**
 * @brief Function that separetes a given string to the format we need to print the results of query 10 on the iterative program
 * @line string to be separated and printed on the format we chose for query 10
 */
static void print_line_q10(char *line)
{
    char *s1= strsep(&line,";");
    char *s2 = strsep(&line,";");
    char *s3 = strsep(&line,";");
    print_string(s1,13);
    print_string (s2,15);
    print_string (s3,23);
    print_string(line,14);
    printw(" |\n");
}

/**
 * @brief Function that prints lines for query 1
 * @param line given string.
 */
static void print_line4(char *line)
{
    char *s = strsep(&line,":");
    print_string(s,56);
    print_string(line,15);
    printw(" |\n");
}

/**
 * @brief Function that prints the char '-' n times on the terminal and leaves an empty line after printing
 * @param n times to print the char
 */
void print_traco(int n)
{
    int i;
    for(i = 0; i < n; i++) putchar('-');
    putchar('\n');
}

/**
 * @brief Function that prints the char '-' n times on the terminal using NCURSES and leaves an empty line after printing
 * @param n times to print the char
 */
void print_traco3(int n)
{
    int i;
    for(i = 0; i < n; i++) printw("-");
    printw("\n");
}

/**
 * @brief Function that prints the char '-' n times on the terminal using NCURSES
 * @param n times to print the char
 */
void print_traco4(int n)
{
    int i;
    for(i = 0; i < n; i++) printw("-");
}

/**
 * @brief Function that prints the char '-' n times on the terminal
 * @param n times to print the char
 */
void print_traco2(int n)
{
    int i;
    for(i = 0; i < n; i++) putchar('-');
}

/**
 * @brief Function that prints the number of pages of content that answers a query
 * @param i Number of the line to print
 * @param n Number of entries in each page
 * @param paginas Amount of pages calculated previously
 */
void print_number_page(int i, int n, int paginas)
{
    print_traco3(79);
    char auxs1[60] = "Pagina: ";
    char auxs2[20];
    sprintf(auxs2,"%d",i/n);
    strcat(auxs1,auxs2);
    strcat(auxs1," de ");
    sprintf(auxs2,"%d",paginas);
    strcat(auxs1,auxs2);
    print_string(auxs1,75);
    printw("|\n");
}

/**
 * @brief Function that handles the printing of the results of our queries on the terminal
 * @param aux File where we will get the information related to our answers from
 * @param i Number of the line to print
 * @param j Auxiliar of i
 * @param n Number of entries in each page
 * @param str_aux Auxiliary string where we well keep storing the information on the given file that we want to display on the terminal
 * @param paginas Number of pages of outputs
 * @param query Number of the query whose output we want to see
 */
static int print_some_lines(FILE *aux, int i, int j, int n, char *str_aux, int paginas, int query)
{
    clear();
    print_traco3(79);
    char *r = format(query);
    printw(r);
    free(r);
    print_traco3(79);
    for(; i < j + n; i++)
        if(fgets(str_aux,3000,aux)) {
          if (query == 1) print_line4 (str_aux);
          else if (query == 2 || query == 3 || query == 4) print_line3 (str_aux);
          else if (query == 5 || query == 6)  print_line2 (str_aux);
          else if (query == 7 || query == 8 || query == 9) print_line(str_aux);
          else if (query == 10) print_line_q10(str_aux);
          }
    print_number_page(i,n,paginas);
    return i;
}

/**
 * @brief Function that goes to anterior page of a file.
 * @param aux File that we are moving the pages.
 * @param i_a Pointer to save the final Line of the final page
 * @param j_a Pointer to save the final Line of the final page.
 * @param n The number of line for each page.
 * @param str_aux Auxiliary string that has already memory allocated.
 * @return The final 0.
 */
static int anterior_page(FILE *aux, int *i_a, int *j_a, int n, char *str_aux)
{
    int i = *i_a;
    i -= (n * 2);
    if(i < 0)
    {
        i+=n;
        return 1;
    }
    clear();
    fseek(aux,0,SEEK_SET);
    int j = 0;
    str_aux = fgets(str_aux,300,aux);
    while(j < i) 
    {
        str_aux = fgets(str_aux,300,aux);
        j++;
    }
    *j_a = j;
    *i_a = i;
    return 0;
}

/**
 * @brief Function that jumps certain page of a file.
 * @param aux File that we are moving the pages.
 * @param i_a Pointer to save the final Line of the final page.
 * @param j_a Pointer to save the final Line of the final page.
 * @param n The number of line for each page.
 * @param str_aux Auxiliary string that has already memory allocated.
 * @param pagina Our current  page.
 * @param r Page that we want to jump into.
 * @return The final 0.
 */
static int jump_pages(FILE *aux, int *i_a, int *j_a, int n, char *str_aux, int pagina, char *r)
{
    r += 2;
    int i = *i_a;
    int j = *j_a;
    int pag;
    pag = atoi(r);
    if(pag > pagina || pag < 1) 
        return 1;
    clear();
    if(pag > i/n) 
    {
        j = (pag - 1) * n;
        while(i < j) 
        {
            str_aux = fgets(str_aux,300,aux);
            i++;
        }
    }
    else
    {
        i = (pag-1) * n;
        fseek(aux,0,SEEK_SET);
        j = 0;
        str_aux = fgets(str_aux,300,aux);
        while(j < i) 
        {
            str_aux = fgets(str_aux,300,aux);
            j++;
        }
    } 
    *j_a = j;
    *i_a = i;
    return 0;
}

/**
* @brief Function that prints helpful information on the terminal
*/
void get_event()
{
    print_traco3(79);
    printw("Insira uma opção:\nEscreva 'Q' se quiser acabar o programa, ou 'M' para um menu geral\n");
}

/**
* @brief Function that prints the options that the user can choose on the iterative program
*/
char *print_pag()
{
    print_traco3(79);
    printw("P     : Próxima\n");
    printw("A     : Anterior\n");
    printw("S <N> : Saltar para página\n");
    printw("Q     : Para sair da query atual\n");
    char *r = malloc(sizeof(char));
    getstr(r);
    return r;
}

/**
 * @brief Function that will answer query2.
 * @param name name of the path
 * @param query number of the query we're analysing
 */
void read_file_estatisticasqueries (char *name, int query)
{
    clear();
    char *str_aux = malloc(sizeof(char) * 3000);
    FILE *file = fopen(name,"r");
    int n = num_lines(file)+1;
    fseek(file,0,SEEK_SET);
    print_some_lines(file,0,0,n,str_aux,1,query);
    print_traco3(79);
    printw("Prima uma tecla aleatória do teclado para sair\n");
    free(str_aux);
    getch();
    clear();
}

/**
 * @brief Main function that will print the information of a certain file that contains the answer for a certain query.
 * @param name The name of the file.
 * @param query The number of the query.
 */
void read_file_queries(char *name, int query)
{
    char *str_aux = malloc(sizeof(char) * 3000);
    printw("Insira número de utilizadores entre 1 e 10:\n");
    int n;
    getstr(str_aux);
    n = atoi(str_aux);
    for(; n < 1 || n > 10; getstr(str_aux), n = atoi(str_aux))
        printw("Número inválido\n");
    FILE *aux = fopen(name,"r");
    int paginas = num_pages(aux,n);
    fseek(aux,0,SEEK_SET);
    char *r = malloc(sizeof(char));
    str_aux = fgets(str_aux,300,aux);
    int i = 0;
    int a = 0;
    do
    {
        free(r);
        int j = i;
        if(!a) i = print_some_lines(aux,i,j,n,str_aux,paginas,query);
        else 
        {
            clear();
            print_traco3(79);
            print_string("Pagina invalida ou Comando invalido", 75);
            printw("|\n");
            print_number_page(i,n,paginas);
            a = 0;
        }
        r = print_pag();
        if(r == NULL);
        else if(*r == 'A' || *r == 'a') 
            a = anterior_page(aux,&i,&j,n,str_aux);
        else if(*r == 'S' || *r == 's')
            a = jump_pages(aux,&i,&j,n,str_aux,paginas,r);
        else if((*r == 'P' || *r == 'p') && i/n >= paginas) 
            a = 1;
        else  if(*r != 'A' && *r != 'S' && *r != 'P' && *r != 'a' && *r != 's' && *r != 'p') a = 1;
    } while (r != NULL && *r != 'Q' && *r != 'q' && strcmp(r,"") != 0 && *r != '\n');
    free(str_aux);
    clear();
}

/**
 * @brief Function to print when it is received an invalid data.
 */
int print_invalid_lan()
{
    clear();
    print_traco3(79);
    printw("Linguagem Inválida\n");
    return 0;
}

/**
 * @brief Function to print when it is received an invalid data.
 */
int print_invalid_data()
{
    clear();
    print_traco3(79);
    printw("Data inválida\n");
    return 0;
}

/**
 * @brief Function that prints the iterative program's menu on the terminal using NCURSES
 */
void printMenu_iterativo(){
    clear();
    putchar('\n');
    print_traco4(30);printw("< LI3 - GRUPO 30 >");print_traco3(31);
    printw("|  1 "); print_string("Quantidade de bots, organizacoes e utilizadores",70);printw("|\n");
    printw("|  2 "); print_string("Numero medio de colaboradores por repositorio",70);printw("|\n");
    printw("|  3 "); print_string("Quantidade de repositorios com bots",70);printw("|\n");
    printw("|  4 "); print_string("Quantidade media de commits por utilizador",70);printw("|\n");
    printw("|  5 "); print_string("N utilizadores mais ativos num intervalo de datas",70);printw("|\n");
    printw("|  6 "); print_string("N utilizadores mais ativos em repositorios de uma linguagem",70);printw("|\n");
    printw("|  7 "); print_string("Repositorios inativos a partir de uma determinada data",70);printw("|\n");
    printw("|  8 "); print_string("N linguagens mais utilizadas a partir de uma determinada data",70);printw("|\n");
    printw("|  9 "); print_string("N utilizadores com mais commits em repositorios de amigos",70);printw("|\n");
    printw("| 10 "); print_string("N utilizadores com as maiores mensagens de commit por repositorio",70);printw("|\n");
    print_traco3(79);
    putchar('\n');
}

/**
 * @brief Function that prints the menu of our interactive program
 * 
 */
void printMenu(){
    putchar('\n');
    print_traco2(30);printf("< LI3 - GRUPO 30 >");print_traco(31);
    printf("|  1 | Quantidade de bots, organizações e utilizadores                        |\n");
    printf("|  2 | Número médio de colaboradores por repositório                          |\n");
    printf("|  3 | Quantidade de repositórios com bots                                    |\n");
    printf("|  4 | Quantidade média de commits por utilizador                             |\n");
    printf("|  5 | N utilizadores mais ativos num intervalo de datas                      |\n");
    printf("|  6 | N utilizadores mais ativos em repositórios de uma linguagem            |\n");
    printf("|  7 | Repositórios inativos a partir de uma determinada data                 |\n");
    printf("|  8 | N linguagens mais utilizadas a partir de uma determinada data          |\n");
    printf("|  9 | N utilizadores com mais commits em repositórios de amigos              |\n");
    printf("| 10 | N utilizadores com as maiores mensagens de commit por repositório      |\n");
    print_traco(79);
    putchar('\n');
}

/**
 * @brief Print some string.
 * @param str String to print.
 */
void print_str(char *str)
{
    print_traco3(79);
    printw("%s",str);
}
/**
 * @brief Print the time used.
 * @param time_used the time to print.
 */
void print_time_ncur(double time_used)
{
    print_traco3(79);
    printw("Tempo: %.2f\n",time_used);
}