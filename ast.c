#include "ast.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash.h"

List *mkList() {
    initTable();
    List *list = (List *) malloc(sizeof(List));
    list->size = 0;
    return list;
}


void addLast(Instr *instr, List *list) {
    struct Node *node = (struct Node *) malloc(sizeof(struct Node));
    node->instr = instr;
    node->next = list->head;
    list->head = node;

    list->size++;

}

// void addLast(Instr *instr, List *list) {
//     struct Node *node = (struct Node *) malloc(sizeof(struct Node));
//     node->instr = instr;
//     if(isEmpty(list)) {
//         list->head = node;
//     }
//     else {
//         struct Node *aux = list->head;
//         while(aux->next!=NULL) aux = aux->next;
//         aux->next = node;
//     }

//     list->size++;
// }

bool isEmpty(List *list) {
    return list->size == 0 ? TRUE : FALSE;
}

void printList(List *list) {
    printf("LIST_SIZE = %d\n", list->size);
    struct Node *node = list->head;
    for(int i = 0; i < list->size; i++, node=node->next) {
        execInstr(node->instr);
    }
    // while(node!=NULL) {
    //     execInstr(node->instr);
    //     node = node->next;
    // }
}

Instr *mkInstrPrint(char* varName) {
    Instr *instr = (Instr *) malloc(sizeof(Instr));
    instr->attr.varName = strdup(varName);
    instr->kind = PRINT;
    return instr;
}

Instr *mkInstrRead(char* varName) {
    Instr *instr = (Instr *) malloc(sizeof(Instr));
    instr->attr.varName = strdup(varName);
    instr->kind = READ;
    return instr;
}

void execInstr(Instr *instr) {
    int temp = 0;
    switch (instr->kind) {
        case PRINT:
            printf("%d\n", lookUp(instr->attr.varName)->val);
            break;
        case READ:
            printf("Var to read: %s\n", instr->attr.varName);
            // scanf("%d", &temp);
            insert(instr->attr.varName, temp);
            break;
        default:
            printf("DEF\n");
            break;
    }
}

Expr *mkExprOp(enum ExprKind kind, Expr *left, Expr *right) {
    Expr *expr = (Expr *) malloc(sizeof(Expr));
    expr->kind = kind;
    expr->attrb.expr.left = left;
    expr->attrb.expr.right = right;
    return expr;
}

Expr *mkExprVar(enum ExprKind kind, char *var) {
    Expr *expr = (Expr *) malloc(sizeof(Expr));
    expr->kind = kind;
    expr->attrb.var = strdup(var);
    return expr;
}

Expr *mkExprInt(enum ExprKind kind, int val) {
    Expr *expr = (Expr *) malloc(sizeof(Expr));
    expr->kind = kind;
    expr->attrb.val = val;
    return expr;
}