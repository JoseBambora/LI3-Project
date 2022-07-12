typedef struct nodo **THash;

int exist_elem_hash(THash t, int re);
void free_hash(THash t);
void insert_hash (THash t, int re);
THash init_hash();