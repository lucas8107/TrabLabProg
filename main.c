#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

int main() {

    IList *list = mkList();


    addLast(mkInstr(READ, mkVar("x"), NULL, NULL), list);
    addLast(mkInstr(QUIT, NULL, NULL, NULL), list);

    addLast(mkInstr(LABEL, mkVar("Init"), NULL, NULL), list);
    addLast(mkInstr(IF_I, mkVar("x"), mkVar("Exit"), NULL), list);
    // addLast(mkInstr(IF_I, mkInt(0), mkVar("Exit"), NULL), list);
    addLast(mkInstr(ADD, mkVar("x"), mkVar("x"), mkInt(1)), list);
    addLast(mkInstr(GOTO_I, mkVar("Init"), NULL, NULL), list);
    
    addLast(mkInstr(LABEL, mkVar("Exit"), NULL, NULL), list);
    addLast(mkInstr(PRINT, mkVar("x"), NULL, NULL), list);
    

    // // addLast(mkInstr(ADD, mkVar("x"), mkInt(3), mkInt(5)), list);
    // // addLast(mkInstr(SUB, mkVar("y"), mkInt(3), mkInt(5)), list);
    // addLast(mkInstr(READ, mkVar("z"), NULL, NULL), list);
    
    // addLast(mkInstr(ADD, mkVar("var1"), mkInt(10), mkVar("z")), list);

    // // addLast(mkInstr(PRINT, mkVar("x"), NULL, NULL), list);
    // // addLast(mkInstr(PRINT, mkVar("y"), NULL, NULL), list);
    // addLast(mkInstr(PRINT, mkVar("var1"), NULL, NULL), list);



    run(list);

    return 0;

}