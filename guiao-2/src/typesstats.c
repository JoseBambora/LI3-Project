#include "../include/typesstats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * \brief Struct that handles the information related to the different types that an user can have - used in statistic queries
 */
struct u_types_stats {
    int bot;
    int organization;
    int user;
};

/**
 * @brief  Function that initializes the UTYPESTATS struct
 * @return u -> the struct UTYPESTATS already initiliazed
 */
UTYPESTATS  init_types_users() {
   UTYPESTATS u = malloc (sizeof(struct u_types_stats));
   u->bot = 0;
   u->organization=0;
   u->user = 0;
   return u;
}

/**
 * @brief  Auxiliar function used in order to find the exact number of users of type: bot; organization; user
 * @param u Struct we're working on
 * @param n integer that identifies the type we're incrementing - whether it is a bot, organization or user
 * @return 0
 */
int incrementaTypes (UTYPESTATS u, int n) {
    if (n==0) u->bot++;
    else if (n==1) u->organization++;
    else if (n==2) u->user++;
    return 0;
}

/**
 * @brief  Function that returns the number of BOT users
 * @param stats Struct we're working on
 * @return n -> total of bot users
 */
int returnBots (UTYPESTATS stats) {
    int n = stats-> bot;
    return n;
}

/**
 * @brief  Function that returns the number of ORGANIZATION users
 * @param stats Struct we're working on
 * @return n -> total of organization users
 */
int returnOrganization (UTYPESTATS stats) {
    int n = stats-> organization;
    return n;
}

/**
 * @brief  Function that returns the number of USER users
 * @param stats Struct we're working on
 * @return n -> total of USER users
 */
int returnUser (UTYPESTATS stats) {
    int n = stats-> user;
    return n;
}

/**
 * @brief Function that frees the memory blocks previously allocated for stats related elements.
 * @param s UTYPESTATS data that we want to deallocate.
 * @return 0
 */
int free_Utypes(UTYPESTATS s)
{
        free(s);
        return 0;

}