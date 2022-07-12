#include "../include/commessage.h"
#include "../include/quadruplo.h"
#include "../include/user.h"
#include "../include/commit.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @struct struct of COMMITMESSAGE.
 */
struct commitmessage{
   QUADRUPLO *tr;
};

/**
 * @brief Function that inicialize a COMMITMESSAGE.
 * @param size_triplo Pointer to save the size of quadruplo.
 * @return The final COMMITMESSAGE.
 */
COMMITMESSAGE startcommitmessage(int *size_triplo)
{
   QUADRUPLO *t = (QUADRUPLO *) commit_quadruplo(size_triplo);
   t = complete_quadruplo(t,*size_triplo);
   COMMITMESSAGE cm = malloc(sizeof(struct commitmessage));
   sort_quadruplo(t,*size_triplo);
   sort_aux(t,*size_triplo);
   cm->tr = t;
   return cm;
}

/**
 * @brief Function that free a COMMITMESSAGE.
 * @return 0.
 */
int free_cm(COMMITMESSAGE cm, int size_cm)
{
   free_quadruplo(cm->tr,size_cm);
   free(cm);
   return 0;
}

/**
 * @brief Function that adds a content of COMMITMESSAGE to the file.
 * @param cm COMMITMESSAGE with the information we want to print.
 * @param size size of the array Quadruplo associated on COMMITMESSAGE.
 * @param num Top N.
 * @param newfile File to add information.
 * @return 0.
 */
int add_content_cm (COMMITMESSAGE cm ,int size, int num, void *newfile, void *query_file)
{
   add_content_quadruplo(cm->tr,size,num , newfile,query_file);
   return 0;
}