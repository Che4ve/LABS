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
    printf("Abstract syntax tree:\n");
    printTree(ast->root, 0);
    printf("======\n");
    simplifyTree(ast, ast->root);
    
    char* infixExpr = toInfix(ast->root, 0);
    printf("Simplified expression:\n\n");
    printf("%s\n", infixExpr);

    free(infixExpr);
    freeTree(ast->root);
    free(ast);
    freeRpnQueue(output);
    return 0;
}