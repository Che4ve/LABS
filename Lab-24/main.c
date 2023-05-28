#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "globals.h"
#include "mathparser.h"

int main(int argc, char** argv)
{
    char inputS[MAX_LEN];
    printf("Enter expression: ");
    fgets(inputS, MAX_LEN, stdin);
    rpnQueue* output = parseExpr(inputS);
    syntaxTree* ast = buildSyntaxTree(output);
    simplifyTree(ast, ast->root);
    char* infixExpr = toInfix(ast->root, true);
    printf("%s\n", infixExpr);
    free(infixExpr);
    return 0;
}