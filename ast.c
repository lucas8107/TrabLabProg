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

void addLast(Instr *instr, IList *list) {
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
}

bool isEmpty(IList *list) {
    return size == 0 ? TRUE : FALSE;
}

struct Node *getAt(int index, IList *list) {
    struct Node *node = list->head;
    int i = 0;
    while(i!=index) {
        node = node->next;
        i++;
    }
    return node;
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
    if(op == ATRIB) {
        instr->op = op;
        instr->first = first;
        instr->second = second;
        return instr;
    }
    if(op == ADD || op == SUB || op == MUL || op == DIV) {
        instr->op = op;
        instr->first = first;
        instr->second = second;
        instr->third = third;
        return instr;
    }
    if(op == PRINT || op == READ) {
        instr->op = op;
        instr->first = first;
        return instr;
    }
    if(op == GOTO_I || op == LABEL) {
        if(op == LABEL)
            insert(first->contents.name, size);
        instr->op = op;
        instr->first = first;
        return instr;
    }
    if(op == IF_I) {
        instr->op = op;
        instr->first = first;
        instr->second = second;
        return instr;
    }
    if(op == QUIT) {
        instr->op = QUIT;
        return instr;
    }
}

void run(IList *list) {
    struct Node *node = list->head;
    int aux;
    int aux_2;
    bool quit = FALSE;
    while(node!=NULL && !quit) {
        switch (node->instr->op) {
            case QUIT:
                quit = TRUE;
                break;
            case GOTO_I:
                node = getAt(lookUp(node->instr->first->contents.name)->val, list);
                break;
            case IF_I:
                if(node->instr->first->kind == STRING)
                    aux = lookUp(node->instr->first->contents.name)->val;
                else
                    aux = node->instr->first->contents.val;
                if(aux) {
                    node = getAt(lookUp(node->instr->second->contents.name)->val, list);                    
                }
                break;
            // case LABEL:

            //     break;
            case ATRIB:
                insert(node->instr->first->contents.name, node->instr->second->contents.val);
                break;
            case ADD:
                if(node->instr->second->kind == STRING)
                    aux = lookUp(node->instr->second->contents.name)->val;
                else
                    aux = node->instr->second->contents.val;    
                if(node->instr->third->kind == STRING)
                    aux_2 = lookUp(node->instr->third->contents.name)->val;
                else
                    aux_2 = node->instr->third->contents.val;
                insert(node->instr->first->contents.name, aux + aux_2);
                break;
            case SUB:
                if(node->instr->second->kind == STRING)
                    aux = lookUp(node->instr->second->contents.name)->val;
                else
                    aux = node->instr->second->contents.val;    
                if(node->instr->third->kind == STRING)
                    aux_2 = lookUp(node->instr->third->contents.name)->val;
                else
                    aux_2 = node->instr->third->contents.val;
                insert(node->instr->first->contents.name, aux - aux_2);
                break;
            case MUL:
                if(node->instr->second->kind == STRING)
                    aux = lookUp(node->instr->second->contents.name)->val;
                else
                    aux = node->instr->second->contents.val;    
                if(node->instr->third->kind == STRING)
                    aux_2 = lookUp(node->instr->third->contents.name)->val;
                else
                    aux_2 = node->instr->third->contents.val;
                insert(node->instr->first->contents.name, aux * aux_2);
                break;
            case DIV:
                if(node->instr->second->kind == STRING)
                    aux = lookUp(node->instr->second->contents.name)->val;
                else
                    aux = node->instr->second->contents.val;    
                if(node->instr->third->kind == STRING)
                    aux_2 = lookUp(node->instr->third->contents.name)->val;
                else
                    aux_2 = node->instr->third->contents.val;
                insert(node->instr->first->contents.name, aux / aux_2);
                break;
            case PRINT:
                printf("%d\n", lookUp(node->instr->first->contents.name)->val);
                break;
            case READ:
                scanf("%d", &aux);
                insert(node->instr->first->contents.name, aux);
                break;
            default:
                break;
        }

        node = node->next;
    }
}