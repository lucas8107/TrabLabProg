#define HASH_SIZE 19
#define MULTIPLIER 31

typedef struct List_hash {
    char *key;
    int val;
    struct List_hash *next;
} List_hash;

List_hash *table[HASH_SIZE];

void initTable();
unsigned int _hash(char *key);
List_hash *lookUp(char* key);
void insert(char* key, int val);
void printTable();
void printCell();