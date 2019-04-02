#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include "ast.h"

char *getMatched(regmatch_t rm , char *str) {
    char *result;
    result = (char*)malloc(rm.rm_eo - rm.rm_so + 1);
    strncpy(result, &str[rm.rm_so], rm.rm_eo - rm.rm_so);
    result[rm.rm_eo - rm.rm_so] = '\0';
    return result;        
}

bool isNum(char c) {
    return c >= '0' && c <= '9' ? TRUE : FALSE;
}

int main(int argc, char **argv) {

    if(argc!=2) {
        printf("Usage: ./main input\n");
        return -1;
    }

    regex_t regex_if;
    regex_t regex_quit;
    regex_t regex_goto;
    regex_t regex_label;
    regex_t regex_expr;
    regex_t regex_attrb;
    regex_t regex_print;
    regex_t regex_read;

    regcomp(&regex_if, " *if *\\([a-z][a-zA-Z0-9]*\\) *goto *\\([A-Z][a-zA-Z0-9]*\\) *; *", 0);
    regcomp(&regex_quit, " *quit *; *", 0);
    regcomp(&regex_goto, " *goto *\\([A-Z][a-zA-Z0-9]*\\) *; *", 0);
    regcomp(&regex_label, " *label *\\([A-Z][a-zA-Z0-9]*\\) *; *", 0);
    regcomp(&regex_expr, " *\\([a-z][a-zA-Z0-9]*\\) *= *\\([a-zA-Z0-9]\\+\\) *\\([\\+-\\*\\/]\\) *\\([a-zA-Z0-9]\\+\\) *; *", 0);
    regcomp(&regex_attrb, " *\\([a-z][a-zA-Z0-9]*\\) *= *\\([a-zA-Z0-9]\\+\\) *; *", 0);
    regcomp(&regex_print, " *escrever *(\\([a-zA-Z][a-zA-Z0-9]*\\)) *; *", 0);
    regcomp(&regex_read, " *ler *(\\([a-zA-Z][a-zA-Z0-9]*\\)) *; *", 0);

    FILE *fd = fopen(argv[1], "r");
    IList *list = mkList();

    char *buffer;
    __ssize_t read;
    size_t len = 0;
    regmatch_t pmatch[5];

    while((read = getline(&buffer, &len, fd)) != -1) {
        if(!regexec(&regex_if, buffer, 3, pmatch, 0)) {
            char *result_1 = getMatched(pmatch[1], buffer);
            char *result_2 = getMatched(pmatch[2], buffer);
            addLast(mkInstr(IF_I, mkVar(result_1), mkVar(result_2), NULL), list);
            free(result_1);
            free(result_2);
        }
        else if(!regexec(&regex_quit, buffer, 0, NULL, 0)) {
            addLast(mkInstr(QUIT, NULL, NULL, NULL), list);
        }
        else if(!regexec(&regex_goto, buffer, 2, pmatch, 0)) {
            char *result = getMatched(pmatch[1], buffer);
            addLast(mkInstr(GOTO_I, mkVar(result), NULL, NULL), list);
            free(result);
        }
        else if(!regexec(&regex_label, buffer, 2, pmatch, 0)) {
            char *result = getMatched(pmatch[1], buffer);
            addLast(mkInstr(LABEL, mkVar(result), NULL, NULL), list);
            free(result);
        }
        else if(!regexec(&regex_expr, buffer, 5, pmatch, 0)) {
            char *result_1 = getMatched(pmatch[1], buffer);
            char *result_2 = getMatched(pmatch[2], buffer);
            char *result_3 = getMatched(pmatch[3], buffer);
            char *result_4 = getMatched(pmatch[4], buffer);
            Elem *e1 = mkVar(result_1);
            Elem *e2;
            Elem *e3;
            if(isNum(result_2[0]))
                e2 = mkInt(atoi(result_2));
            else
                e2 = mkVar(result_2);
            if(isNum(result_4[0]))
                e3 = mkInt(atoi(result_4));
            else
                e3 = mkVar(result_4);
            switch (result_3[0]) {
                case '+':
                    addLast(mkInstr(ADD, e1, e2, e3), list);
                    break;
                case '-':
                    addLast(mkInstr(SUB, e1, e2, e3), list);
                    break;
                case '*':
                    addLast(mkInstr(MUL, e1, e2, e3), list);
                    break;
                case '/':
                    addLast(mkInstr(DIV, e1, e2, e3), list);
                    break;
            }

            free(result_1);
            free(result_2);
            free(result_3);
            free(result_4);
        }
        else if(!regexec(&regex_attrb, buffer, 3, pmatch, 0)) {
            char *result_1 = getMatched(pmatch[1], buffer);
            char *result_2 = getMatched(pmatch[2], buffer);
            Elem *e1;
            if(isNum(result_2[0]))
                e1 = mkInt(atoi(result_2));
            else
                e1 = mkVar(result_2);

            addLast(mkInstr(ATRIB, mkVar(result_1), e1, NULL), list);
            
            free(result_1);
            free(result_2);
        }
        else if(!regexec(&regex_read, buffer, 2, pmatch, 0)) {
            char *result = getMatched(pmatch[1], buffer);
            addLast(mkInstr(READ, mkVar(result), NULL, NULL), list);
            free(result);
        }
        else if(!regexec(&regex_print, buffer, 2, pmatch, 0)) {
            char *result = getMatched(pmatch[1], buffer);
            addLast(mkInstr(PRINT, mkVar(result), NULL, NULL), list);
            free(result);
        }
    }

    regfree(&regex_if);
    regfree(&regex_quit);
    regfree(&regex_goto);
    regfree(&regex_label);
    regfree(&regex_expr);
    regfree(&regex_attrb);
    regfree(&regex_print);
    regfree(&regex_read);

    run(list);

    return 0;

}