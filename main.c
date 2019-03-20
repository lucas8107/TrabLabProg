#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include "ast.h"

char *getMatched(int first, int last, char *str) {
    char *result;
    result = (char*)malloc(last - first);
    strncpy(result, &str[first], last - first);
    return result;        
}

int main(int argc, char **argv) {

    // regex_t regex_expr_var;
    // regex_t regex_expr_val;
    // regex_t regex_if;
    // regex_t regex_goto;
    // regex_t regex_label;
    // regex_t regex_quit;

    // int reti;

    // regcomp(&regex_expr_var, " *[a-z][a-zA-Z0-9]* *= \\(*[a-z][a-zA-Z0-9]*\\) *;", 0);
    // regcomp(&regex_expr_val, " *[a-z][a-zA-Z0-9]* *= \\(*[0-9]+\\) *;", 0);
    // regcomp(&regex_if, " *if.*;", 0);
    // regcomp(&regex_goto, " *goto.*;", 0);
    // regcomp(&regex_label, " *label *\\([A-Z][a-zA-Z0-9]*\\) *;", 0);
    // regcomp(&regex_quit, " *quit *;", 0);

    regex_t regex_expr;
    regex_t regex_var;
    regex_t regex_int;
    regex_t regex_print;
    regex_t regex_read;

    regcomp(&regex_expr, " *\\([a-z][a-zA-Z0-9]*\\) *= *\\([a-zA-Z0-9]\\+\\) *[+\\-\\*\\/] *\\([a-zA-Z0-9]\\+\\) *;", 0);
    regcomp(&regex_var, " *\\([a-z][a-zA-Z0-9]*\\) *", 0);
    regcomp(&regex_int, " *\\([0-9]+\\) *", 0);
    regcomp(&regex_print, " *escrever *(\\([a-zA-Z][a-zA-Z0-9]*\\)) *;", 0);
    regcomp(&regex_read, " *ler *(\\([a-zA-Z][a-zA-Z0-9]*\\)) *;", 0);

    FILE *fd = fopen(argv[1], "r");
    IList *list = mkList();

    char *buffer;
    __ssize_t read;
    size_t len = 0;
    regmatch_t pmatch[4];

    while((read = getline(&buffer, &len, fd)) != -1) {
        if(!regexec(&regex_expr, buffer, 4, pmatch, 0)) {
            printf("\n\n%s", buffer);
            char *result_1 = getMatched(pmatch[1].rm_so, pmatch[1].rm_eo, buffer);
            char *result_2 = getMatched(pmatch[2].rm_so, pmatch[2].rm_eo, buffer);
            char *result_3 = getMatched(pmatch[3].rm_so, pmatch[3].rm_eo, buffer);
            printf("(%s) (%s) (%s)\n", result_1, result_2, result_3);
        }        
        if(!regexec(&regex_read, buffer, 2, pmatch, 0)) {
            char *result = getMatched(pmatch[1].rm_so, pmatch[1].rm_eo, buffer);
            addLast(mkInstr(READ, mkVar(result), NULL, NULL), list);
            free(result);
        }
        if(!regexec(&regex_print, buffer, 2, pmatch, 0)) {
            char *result = getMatched(pmatch[1].rm_so, pmatch[1].rm_eo, buffer);
            addLast(mkInstr(PRINT, mkVar(result), NULL, NULL), list);
            free(result);
        }
    }

    // run(list);

    // addLast(mkInstr(READ, mkVar("x"), NULL, NULL), list);
    // addLast(mkInstr(QUIT, NULL, NULL, NULL), list);
    // addLast(mkInstr(LABEL, mkVar("Init"), NULL, NULL), list);
    // addLast(mkInstr(IF_I, mkVar("x"), mkVar("Exit"), NULL), list);
    // addLast(mkInstr(IF_I, mkInt(0), mkVar("Exit"), NULL), list);
    // addLast(mkInstr(ADD, mkVar("x"), mkVar("x"), mkInt(1)), list);
    // addLast(mkInstr(GOTO_I, mkVar("Init"), NULL, NULL), list);
    // addLast(mkInstr(LABEL, mkVar("Exit"), NULL, NULL), list);
    // addLast(mkInstr(PRINT, mkVar("x"), NULL, NULL), list);
    // addLast(mkInstr(ADD, mkVar("x"), mkInt(3), mkInt(5)), list);
    // addLast(mkInstr(SUB, mkVar("y"), mkInt(3), mkInt(5)), list);
    // addLast(mkInstr(READ, mkVar("z"), NULL, NULL), list);
    // addLast(mkInstr(ADD, mkVar("var1"), mkInt(10), mkVar("z")), list);
    // addLast(mkInstr(PRINT, mkVar("x"), NULL, NULL), list);
    // addLast(mkInstr(PRINT, mkVar("y"), NULL, NULL), list);
    // addLast(mkInstr(PRINT, mkVar("var1"), NULL, NULL), list);

    // run(list);

    return 0;

}