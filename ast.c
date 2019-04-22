#include "ast.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash.h"

IList *mkList() {
    initTable();
    IList *list = (IList *) malloc(sizeof(IList));
    size = 0;
}

struct Node* addLast(Instr *instr, IList *list) {
    struct Node *node = (struct Node *) malloc(sizeof(struct Node));
    node->instr = instr;
    if(isEmpty(list)) {
        list->head = node;
        list->last = node;
    }
    else {
        list->last->next = node;
        list->last = list->last->next;
    }
    size++;
    return node;
}

bool isEmpty(IList *list) {
    return size == 0 ? TRUE : FALSE;
}

Elem *mkInt(int val) {
    Elem *el = (Elem *) malloc(sizeof(Elem));
    el->kind = INT_CONST;
    el->contents.val = val;
    return el;
}

Elem *mkVar(char *varName) {
    Elem *el = (Elem *) malloc(sizeof(Elem));
    el->kind = STRING;
    el->contents.name = strdup(varName);
    return el;
}

Instr *mkInstr(OpKind op, Elem *first, Elem *second, Elem *third) {
    Instr *instr = (Instr *) malloc(sizeof(Instr));

    
    instr->op = op;
    instr->first = first;
    instr->second = second;
    instr->third = third;

    if(op == LABEL) {
        insert(first->contents.name, labelCount);
    }
    return instr;
}

int getElemVal(Elem *e) {
    if(e->kind == STRING) {
        return lookUp(e->contents.name)->val;
    }
    else {
        return e->contents.val;
    }
}

void run(IList *list) {
    struct Node *node = list->head;
    int aux;
    int aux_2;
    bool quit = FALSE;
    while(!quit) {
        switch (node->instr->op) {
            case QUIT:
                quit = TRUE;
                break;
            case GOTO_I:
                node = labelArray[(lookUp(node->instr->first->contents.name)->val)];
                break;
            case IF_I:
                aux = getElemVal(node->instr->first);
                aux_2 = lookUp(node->instr->second->contents.name)->val;
                if(aux) {
                    node = labelArray[aux_2];
                }
                break;
            case ATRIB:
                aux = getElemVal(node->instr->second);
                insert(node->instr->first->contents.name, aux);
                break;
            case ADD:
                aux = getElemVal(node->instr->second);
                aux_2 = getElemVal(node->instr->third);
                insert(node->instr->first->contents.name, aux + aux_2);
                break;
            case SUB:
                aux = getElemVal(node->instr->second);
                aux_2 = getElemVal(node->instr->third);
                insert(node->instr->first->contents.name, aux - aux_2);
                break;
            case MUL:
                aux = getElemVal(node->instr->second);
                aux_2 = getElemVal(node->instr->third);
                insert(node->instr->first->contents.name, aux * aux_2);
                break;
            case DIV:
                aux = getElemVal(node->instr->second);
                aux_2 = getElemVal(node->instr->third);
                insert(node->instr->first->contents.name, aux / aux_2);
                break;
            case PRINT:
                printf("%s: %d\n", node->instr->first->contents.name, lookUp(node->instr->first->contents.name)->val);
                break;
            case READ:
                scanf("%d", &aux);
                insert(node->instr->first->contents.name, aux);
                break;
            case LABEL:
                break;
            default:
                printf("Unknow %d\n", node->instr->op);
                break;
        }

        node = node->next;
    }
}