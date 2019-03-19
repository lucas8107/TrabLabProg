#include <stdio.h>
#include "ast.h"
#include <string.h>
#include <stdlib.h>
#include <regex.h>

// bool validVarName(char *name, int count);
// void getInstr(char *str);


int main(int argc, char **argv) {

    FILE *f = fopen(argv[1], "r");

    regex_t regex_expr_var;
    regex_t regex_expr_val;
    regex_t regex_expr;
    regex_t regex_print;
    regex_t regex_read;
    regex_t regex_if;
    regex_t regex_goto;
    regex_t regex_label;
    regex_t regex_quit;

    // int reti;

    regcomp(&regex_expr_var, " *[a-z][a-zA-Z0-9]* *= \\(*[a-z][a-zA-Z0-9]*\\) *;", 0);
    regcomp(&regex_expr_val, " *[a-z][a-zA-Z0-9]* *= \\(*[0-9]+\\) *;", 0);
    regcomp(&regex_expr, " *[a-z][a-zA-Z0-9]* *=.*[+-\\*/].*;", 0);
    regcomp(&regex_print, " *escrever *(\\([a-zA-Z][a-zA-Z0-9]*\\)) *;", 0);
    regcomp(&regex_read, " *ler *(\\([a-zA-Z][a-zA-Z0-9]*\\)) *;", 0);
    regcomp(&regex_if, " *if.*;", 0);
    regcomp(&regex_goto, " *goto.*;", 0);
    regcomp(&regex_label, " *label *\\([A-Z][a-zA-Z0-9]*\\) *;", 0);
    regcomp(&regex_quit, " *quit *;", 0);

    char *buffer;
    __ssize_t read;
    size_t len = 0;
    regmatch_t pmatch[2];

    List *list = mkList();

    while((read = getline(&buffer, &len, f)) != -1) {
    // while(read = getdelim(&buffer, &len, ';', stdin) != -1) {
    // while(read = getline(&buffer, &len, stdin) != -1) {
        printf("%s\n", buffer);
            // if(!regexec(&regex_expr_var, buffer, 0, NULL, 0)) {
            //     // printf("%s is an ATTR Var\n", buffer);
            // }
            // else if(!regexec(&regex_expr_val, buffer, 0, NULL, 0)) {
            //     // printf("%s is an ATTR Val\n", buffer);
            // }
            // else if(!regexec(&regex_expr, buffer, 0, NULL, 0)) {
            //     // printf("%s is an ATTR Op\n", buffer);
            // }
            // else if(!regexec(&regex_print, buffer, 2, pmatch, 0)) {
            //     char *result;
            //     result = (char*)malloc(pmatch[1].rm_eo - pmatch[1].rm_so);
            //     strncpy(result, &buffer[pmatch[1].rm_so], pmatch[1].rm_eo - pmatch[1].rm_so);
            //     // printf("Val: %s\n", result);
            //     // addLast(mkInstrPrint(result), list);
            //     free(result);
            // }
            // else if(!regexec(&regex_read, buffer, 0, NULL, 0)) {
            //     // printf("%s is a read Instr\n", buffer);
            //     char *result;
            //     result = (char*)malloc(pmatch[1].rm_eo - pmatch[1].rm_so);
            //     strncpy(result, &buffer[pmatch[1].rm_so], pmatch[1].rm_eo - pmatch[1].rm_so);
            //     printf("Val: %s\n", result);
            //     // addLast(mkInstrRead(result), list);
            //     free(result);
            // }
            // else if(!regexec(&regex_if, buffer, 0, NULL, 0)) {
            //     // printf("%s is an IF Instr\n", buffer);
            // }
            // else if(!regexec(&regex_goto, buffer, 0, NULL, 0)) {
            //     // printf("%s is a GOTO Instr\n", buffer);
            // }
            // else if(!regexec(&regex_label, buffer, 2, pmatch, 0)) {
            //     // printf("%s is a label Instr\n", buffer);
            //                 char *result;
            //     result = (char*)malloc(pmatch[1].rm_eo - pmatch[1].rm_so);
            //     strncpy(result, &buffer[pmatch[1].rm_so], pmatch[1].rm_eo - pmatch[1].rm_so);
            //     printf("Val: %s\n", result);
            // }
            // else if(!regexec(&regex_quit, buffer, 0, NULL, 0)) {
            //     // printf("%s is a Quit Instr\n", buffer);
            // }
            // else {
            //     // printf("%s no match\n", buffer);
            // }

    }

    fclose(f);

    printList(list);

    return 0;
}