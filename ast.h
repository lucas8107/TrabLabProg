#define TRUE 1
#define FALSE 0

typedef int bool;

enum InstrKind {
    PRINT,
    READ,
    ATTRB,
};

enum ExprKind {
    OP,
    VAR,
    INT
};

typedef enum {
    ADD,
    SUB,
    DIV,
    MUL
} ExprOp;

typedef struct Expr Expr;
typedef struct Instr Instr;
typedef struct List List;

struct Expr {
    enum ExprKind kind;
    union {
        int val;
        char *var;
        struct {
            ExprOp op;
            struct Expr *left;
            struct Expr *right;
        } expr;
    } attrb;
};

struct Instr {
    enum InstrKind kind;
    union {
        char *varName;
        struct {
            char *varName;
            struct Expr *expr;
        } attrb;
    } attr;
};

struct List {
    struct Node *head;
    int size;
};

struct Node {
    struct Node *next;
    struct Instr *instr;
};

Instr *mkInstrPrint(char* varName);
Instr *mkInstrRead(char* varName);
void execInstr(Instr *instr);

List *mkList();
void addLast(Instr *instr, List *list);
bool isEmpty(List *list);
void printList(List *list);

Expr *mkExprOp(enum ExprKind kind, Expr *left, Expr *right);
Expr *mkExprVar(enum ExprKind kind, char *var);
Expr *mkExprInt(enum ExprKind kind, int val);