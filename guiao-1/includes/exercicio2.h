typedef struct
{
    int *id_users;
    int userSize;
    int *id_repos;
    int repoSize;
    int *id_commits;
    int commitSize;
}Array_IDS;

int add_elem(char *line, int *users_ID,int n);
int count_lines(FILE *fp);
Array_IDS getUsersId();
char *getNElement(char *line, int n);
int searchArray(int *usersID, int id, int n);
int verifyCommitIDLine(char *line,Array_IDS usersID);
int verifyCommitIDLine(char *line,Array_IDS usersID);
int ex2();
