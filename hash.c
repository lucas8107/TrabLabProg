#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"

void initTable() {
    for(int i = 0; i < HASH_SIZE; i++)
        table[i] = NULL;
}

unsigned int _hash(char *key) {
    unsigned int h;
    unsigned char *p;
    h = 0;
    for(p = (unsigned char *)key; *p!='\0'; p++)
        h = MULTIPLIER * h + *p;
    return h%HASH_SIZE;
}

List_hash *lookUp(char* key) {
    unsigned int hash = _hash(key);
    List_hash *list_hash = table[hash];
    while(list_hash!=NULL && strcmp(list_hash->key, key) != 0) list_hash = list_hash->next;
    return list_hash;
}

void insert(char* key, int val) {

    List_hash *l;

    if((l = lookUp(key)) != NULL) {
        l->val = val;
        return;
    }

    unsigned int hash = _hash(key);
    
    l = (List_hash *) malloc(sizeof(List_hash));
    l->key = strdup(key);
    l->val = val;

    l->next = table[hash];
    table[hash] = l;

}

void printTable() {
    printf("{\n");
    for(unsigned int i = 0; i < HASH_SIZE; i++) {
        if(table[i]!=NULL) {
            List_hash *l = table[i];
            while(l!=NULL) {
                printf("\t");
                printCell(l);
                printf(",\n");
                l = l->next;
            }
        }
    }
    printf("}\n");
}

void printCell(List_hash *l) {
    printf("\"%s\": %d", l->key, l->val);
}