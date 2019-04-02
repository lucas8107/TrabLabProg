#define TRUE 1
#define FALSE 0

typedef int bool;

typedef enum {ATRIB, ADD, SUB, MUL, DIV, IF_I, PRINT, READ, GOTO_I, LABEL, QUIT} OpKind;

typedef enum {EMPTY, INT_CONST, STRING} ElemKind;

typedef struct {
    ElemKind kind;
    union { 
        int val;
        char *name;
    } contents;
} Elem;

typedef struct {
    OpKind op;
    Elem *first, *second, *third;
} Instr;

int size;

typedef struct {
    struct Node *head;
    struct Node *last;
    // int size;
} IList;

struct Node {
    Instr *instr;
    struct Node *next;
};

IList *mkList();
bool isEmpty(IList *list);
void addLast(Instr *instr, IList *list);
struct Node *getAt(int index, IList *list);

Elem *mkVar(char *varName);
Elem *mkInt(int val);

int getElemVal(Elem *e);

Instr *mkInstr(OpKind op, Elem *e1, Elem *e2, Elem *e3);

void run(IList *list);