#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "mathparser.h"
 // Function to print the menu options
void printMenu(void) 
{ 
    printf("    1. Print back expression.\n");
    printf("    2. Show abstract syntax tree.\n");
    printf("    3. Evaluate the expression (initial expression will be overwritten).\n");
    printf("    4. Enter new expression.\n");
    printf("    0. Exit.\n");
}
 int main(int argc, char** argv)
{
    char inputS[MAX_LEN + 1];
    inputS[MAX_LEN] = '\0';
    rpnQueue* output;
    syntaxTree* ast;
    char* infixExpr = NULL;
     int choice;
    // Enumeration for menu options
    enum {
        EXPR_PRINT = 1,
        AST_PRINT  = 2,
        EVALUATE   = 3,
        NEW_EXPR   = 4,
        QUIT       = 0
    };
     // Main loop for user input and processing
    do {
        printf("Enter expression: ");
        fgets(inputS, MAX_LEN, stdin);
        inputS[strcspn(inputS, "\n")] = '\0';
        output = parseExpr(inputS);
        ast = buildSyntaxTree(output);
         // Loop for menu and user choices
        do {
            printMenu();
            scanf("%d", &choice);
            getchar();
             // Process user choice
            switch (choice) {
                case EXPR_PRINT: {
                    if (infixExpr != NULL) {
                        free(infixExpr);
                    }
                    infixExpr = toInfix(ast->root, 0);
                    printf("======\n");
                    printf("%s\n", infixExpr);
                    printf("======\n");
                    break;
                }
                case AST_PRINT: {
                    printf("Abstract syntax tree:\n");
                    printf("======\n");
                    printTree(ast->root, 0);
                    printf("======\n");
                    break;
                }
                case EVALUATE: {
                    if (infixExpr != NULL) {
                        free(infixExpr);
                    }
                    simplifyTree(ast, ast->root);
                    infixExpr = toInfix(ast->root, 0);
                    printf("Simplified expression:\n");
                    printf("======\n");
                    printf("%s\n", infixExpr);
                    printf("======\n");
                    break;
                }
                case NEW_EXPR: {
                    break;
                }
                case QUIT: {
                    break;
                }
                default: {
                    printf("Incorrect input. Try again.\n");
                    break;
                }
            }
        } while (choice != NEW_EXPR && choice != QUIT);
         // Free memory and reset pointers
        free(infixExpr);
        infixExpr = NULL;
        freeTree(ast->root);
        free(ast);
        freeRpnQueue(output);
     } while (choice != QUIT);
     return 0;
}