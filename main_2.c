#include <stdio.h>
#include "ast.h"
#include <string.h>
#include <stdlib.h>
#include <regex.h>

int main() {

    regex_t regex_expr_var;
    regex_t regex_expr_val;
    regex_t regex_expr;
    regex_t regex_func;
    regex_t regex_if;
    regex_t regex_goto;
    regex_t regex_label;
    regex_t regex_quit;

    int reti;

    // reti = regcomp(&regex_expr, " *[a-zA-Z][a-zA-Z0-9]* *= *[a-zA-Z0-9]+ *(+|-|*|/) *[a-zA-Z0-9]+ *;", 0);
    regcomp(&regex_expr_var, " *[a-z][a-zA-Z0-9]* *= *[a-z][a-zA-Z0-9]* *", 0);
    regcomp(&regex_expr_val, " *[a-z][a-zA-Z0-9]* *= *[0-9]+ *", 0);
    regcomp(&regex_expr, " *[a-z][a-zA-Z0-9]* *=.*[+-\\*/].*", 0);
    regcomp(&regex_func, " *[a-z][a-zA-Z0-9]* *[(][a-zA-Z][a-zA-Z0-9]*[)] *", 0);
    regcomp(&regex_if, " *if.*", 0);
    regcomp(&regex_goto, " *goto.*", 0);
    regcomp(&regex_label, " *label *[A-Z][a-zA-Z0-9]* *", 0);
    regcomp(&regex_quit, " *quit *", 0);

    char *buffer;
    const char delim[3] = ";\n";
    __ssize_t read;
    size_t len = 0;

    char input[200] = "ler(k);\nler2 (j) ;\np= 6 + k;\nif p goto L1;\np = p/2;\nescrever(p);\ngoto L2;\nlabel L1;\np = 2*p;\nescrever(p);\nlabel L2;\nb=2;\na=b;quit;";

    char *input;

    // fscanf(stdin, "%s", input);

    List *list = mkList();

    buffer = strtok(input, delim);

    // printf("%s\n", buffer);

    while(buffer!=NULL) {
        printf("%s\n", buffer);
        if(!regexec(&regex_expr_var, buffer, 0, NULL, 0)) {
            // printf("%s is an ATTR Var\n", buffer);
        }
        else if(!regexec(&regex_expr_val, buffer, 0, NULL, 0)) {
            // printf("%s is an ATTR Val\n", buffer);
        }
        else if(!regexec(&regex_expr, buffer, 0, NULL, 0)) {
            // printf("%s is an ATTR Op\n", buffer);
        }
        else if(!regexec(&regex_func, buffer, 0, NULL, 0)) {
            printf("%s is a Function Instr\n", buffer);
            addLast(mkInstrPrint(buffer), list);
        }
        else if(!regexec(&regex_if, buffer, 0, NULL, 0)) {
            // printf("%s is an IF Instr\n", buffer);
        }
        else if(!regexec(&regex_goto, buffer, 0, NULL, 0)) {
            // printf("%s is a GOTO Instr\n", buffer);
        }
        else if(!regexec(&regex_label, buffer, 0, NULL, 0)) {
            // printf("%s is a label Instr\n", buffer);
        }
        else if(!regexec(&regex_quit, buffer, 0, NULL, 0)) {
            // printf("%s is a Quit Instr\n", buffer);
        }
        else {
            // printf("%s no match\n", buffer);
        }
        printList(list);
        printf("\n");
        buffer = strtok(NULL, ";\n");
        
    }

    return 0;
}