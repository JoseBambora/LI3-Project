typedef struct btree *BTREE;
BTREE init_nodo(int n);
BTREE add_elem(BTREE n, int num);
int exist_elem (BTREE n, int num);
int free_btree (BTREE bt);
