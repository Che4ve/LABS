#ifndef __MATHPARSER_H__
#define __MATHPARSER_H__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 300
#define MAX_STACK_SIZE 250

typedef enum {
    ADDITION          = 1,         
    SUBTRACTION       = 2,     
    MULTIPLICATION    = 3,   
    DIVISION          = 4,         
    EXPONENTIATION    = 5,    
    LEFT_PARENTHESIS  = 6, 
    RIGHT_PARENTHESIS = 7,
    UNKNOWN_OPERATOR  = -1
} operatorType;

operatorType getOperator(char op);

char operatorToChar(operatorType op);

typedef struct {
    enum { VALUE, VARIABLE, OPERATOR } type;
    union {
        double value;
        char variable;
        operatorType oper;
    } data;
    double varCoeff;
} exprElement;

void printExprElement(exprElement element);

int unloadOperatorStack(operatorType* stack, int top);

typedef struct {
    exprElement* queue;
    int size;
} rpnQueue;

rpnQueue* parseExpr(char* inputStr);

void freeRpnQueue(rpnQueue* rpn);

typedef struct _treeNode {
    struct _treeNode* parent;
    struct _treeNode* leftChild;
    struct _treeNode* rightChild;
    exprElement content;
} treeNode;

typedef struct {
    treeNode* root;
} syntaxTree;

treeNode* initTreeNode(exprElement data, treeNode* parent);

void freeTree(treeNode* root);

void freeChildren(treeNode* node);

bool isOperatorNode(treeNode* node);

bool isValueNode(treeNode* node);

bool isVariableNode(treeNode* node);

syntaxTree* buildSyntaxTree(rpnQueue* rpn);

bool isLeaf(treeNode* node);

bool isRightOperand(treeNode* node);

bool isZeroNode(treeNode* node);

exprElement evaluate(treeNode* node);

int reduceSimilarTerms(treeNode* node);

void simplifyTree(syntaxTree* tree, treeNode* root);

void printTree(treeNode* root, int indent);

char* toInfix(treeNode* root, operatorType prevOper);

#endif /* __STRMATH_H__ */

