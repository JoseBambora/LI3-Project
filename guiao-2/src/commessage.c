#include "../include/commessage.h"
#include "../include/quadruplo.h"
#include "../include/user.h"
#include "../include/commit.h"
#include <stdlib.h>

/**
 * @struct struct of COMMITMESSAGE.
 */
struct commitmessage{
   QUADRUPLO *tr;
};

/**
 * @brief Function that inicialize a COMMITMESSAGE.
 * @param us Users to help us on adding information on COMMITMESSAGE.
 * @param co Commits to help us on adding information on COMMITMESSAGE.
 * @return The final COMMITMESSAGE.
 */
COMMITMESSAGE startcommitmessage(void *us, void*co, int size, int usize, int *size_triplo)
{
   USER *u = (USER*) us;
   COMMIT *c = (COMMIT *) co;
   sort_commit2(c,size);
   QUADRUPLO *t = (QUADRUPLO *) commit_quadruplo(c,size,size_triplo);
   t = complete_quadruplo(u,usize,t,*size_triplo);
   COMMITMESSAGE cm = malloc(sizeof(struct commitmessage));
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
int add_content_cm (COMMITMESSAGE cm ,int size, int num, void *newfile)
{
   add_content_quadruplo(cm->tr,size,num , newfile);
   return 0;
}