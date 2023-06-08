#include "mathparser.h"
 // Function to get the operator type based on the input character
operatorType getOperator(char op)
{
    switch (op) {
        case '+': return ADDITION;
        case '-': return SUBTRACTION;
        case '*': return MULTIPLICATION;
        case '/': return DIVISION;
        case '^': return EXPONENTIATION;
        case '(': return LEFT_PARENTHESIS;
        case ')': return RIGHT_PARENTHESIS;
    }
    return UNKNOWN_OPERATOR;
}
 // Function to convert an operator type to its corresponding character
char operatorToChar(operatorType op)
{
    switch (op) {
    case ADDITION:          return '+';
    case SUBTRACTION:      return '-';
    case MULTIPLICATION:    return '*';
    case DIVISION:          return '/';
    case EXPONENTIATION:    return '^';
    case LEFT_PARENTHESIS:  return '(';
    case RIGHT_PARENTHESIS: return ')';
    default: return '$';
    }
}
 // Function to print the expression element
void printExprElement(exprElement element)
{
    switch (element.type) {
        case VALUE: 
            if (element.data.value == 0.0) {
                printf("0");
            }
            else {
                printf("%.1lf", element.data.value);
            }
            break;
        case VARIABLE: 
            if (element.varCoeff == 1.0) {
                printf("%c", element.data.variable);
            }
            else if (element.varCoeff == 0.0) {
                printf("0");
            }
            else {
                printf("%.1lf*%c", element.varCoeff, element.data.variable);
            }
            break;
        case OPERATOR: 
            printf("%c", operatorToChar(element.data.oper));
            break;
        default:
            break;
    }
}
 // Function to unload the operator stack
int unloadOperatorStack(operatorType* stack, int top)
{
    if (top <= 0) {
        return top;
    }
     operatorType topOperator = stack[top];
    operatorType prevOperator = stack[top - 1];

    // IF IS OPERATOR
    if (ADDITION <= topOperator && topOperator <= EXPONENTIATION) { 
        if (topOperator != EXPONENTIATION) {
            while (topOperator < prevOperator && top > 0) {
                if (prevOperator == LEFT_PARENTHESIS) {
                    break;
                }
                prevOperator = stack[--top];
                if (topOperator >= prevOperator) {
                    top++;
                    break;
                }
            }
        }
        else {
            while (topOperator <= prevOperator && top > 0) {
                if (prevOperator == LEFT_PARENTHESIS) {
                    break;
                }
                prevOperator = stack[--top];
                if (topOperator > prevOperator) {
                    top++;
                    break;
                }
            }
        }
    }
    // IF IS PARENTHESIS
    else {
        if (topOperator == RIGHT_PARENTHESIS) {
            while (prevOperator != LEFT_PARENTHESIS && top > 0) {
                prevOperator = stack[--top];
                if (prevOperator == LEFT_PARENTHESIS) {
                    break;
                }
            }
        }
    }
    return top;
}
 // Function to parse the input expression string
rpnQueue* parseExpr(char* inputStr)
{
    int len = 0;
    for(len; inputStr[len] != '\0'; ++len);
     operatorType operatorStack[MAX_STACK_SIZE];
    int stackTop = -1;
    rpnQueue* outputQueue = (rpnQueue*)malloc(sizeof(rpnQueue));
    outputQueue->queue = (exprElement*)calloc(MAX_LEN, sizeof(exprElement));
    outputQueue->size = 0;
    int queueTop = -1;
     for (int i = 0; i <= len; i++)  {
        // === MANAGING OUTPUT ===
        int newStackTop = unloadOperatorStack(operatorStack, stackTop);
        if (stackTop != -1 && stackTop != newStackTop) {
            operatorType tmpOperator = operatorStack[stackTop--];
            while ( stackTop + 1 != newStackTop && stackTop >= 0) {
                operatorType curOperator = operatorStack[stackTop--];
                if (curOperator == LEFT_PARENTHESIS) {
                    continue;
                }
                outputQueue->queue[++queueTop] = (exprElement)\
                                                 { OPERATOR, \
                                                   .data.oper = curOperator };
            }
            if (tmpOperator != RIGHT_PARENTHESIS) {
                operatorStack[++stackTop] = tmpOperator;
            }
        }
        // === PARSING ===
        char* currentPtr = inputStr + i;
        operatorType operator = getOperator(*currentPtr);
        if ( operator != UNKNOWN_OPERATOR ) { // OPERATOR
            operatorStack[++stackTop] = operator;
            continue;
        }
        if ( isalpha(*currentPtr) ) { // VARIABLE
            outputQueue->queue[++queueTop]= (exprElement)\
                                            { VARIABLE, \
                                              .data.variable = *currentPtr,
                                              .varCoeff = 1.0 };
            continue;
        }
        char* valueEndPtr;
        double value = strtod(currentPtr, &valueEndPtr); // Make own strtod
        if ( currentPtr != valueEndPtr ) { // VALUE
            i = (valueEndPtr - inputStr) - 1;
            currentPtr = valueEndPtr;
            outputQueue->queue[++queueTop] = (exprElement)\
                                             { VALUE, \
                                               .data.value = value };
        }
    }
    while (stackTop != -1) {
        operatorType curOperator = operatorStack[stackTop--]; 
        outputQueue->queue[++queueTop] = (exprElement)\
                                         { OPERATOR, \
                                           .data.oper = curOperator };
    }
    outputQueue->size = queueTop + 1;
    return outputQueue;
}
 // Function to free the memory allocated for the RPN queue
void freeRpnQueue(rpnQueue* rpn)
{
    if (rpn == NULL) return;
    free(rpn->queue);
    free(rpn);
}
 // Function to initialize a tree node
treeNode* initTreeNode(exprElement data, treeNode* parent)
{
    treeNode* node = (treeNode*)malloc(sizeof(treeNode));
    if (node == NULL) return NULL;
    node->parent = parent;
    node->leftChild = NULL;
    node->rightChild = NULL;
    node->content = data;
    return node;
}
 // Freeing Syntax Tree from memory
void freeTree(treeNode* root)
{
    if (root == NULL) return;
    freeTree(root->leftChild);
    freeTree(root->rightChild);
    root->leftChild = NULL;
    root->rightChild = NULL;
    free(root);
    return;
}
 // Freeing children of the node
void freeChildren(treeNode* node)
{
    if (node == NULL) return;
    if (node->leftChild != NULL) {
        freeTree(node->leftChild);
        node->leftChild = NULL;
    }
    if (node->rightChild != NULL) {
        freeTree(node->rightChild);
        node->rightChild = NULL;
    }
    return;
}

bool isOperatorNode(treeNode* node)
{
    if (node == NULL) return false;
    return node->content.type == OPERATOR;
}

bool isValueNode(treeNode* node)
{
    if (node == NULL) return false;
    return node->content.type == VALUE;
}

bool isVariableNode(treeNode* node)
{
    if (node == NULL) return false;
    return node->content.type == VARIABLE;
}
 // Building AST with iterative method
syntaxTree* buildSyntaxTree(rpnQueue* rpn)
{
    exprElement* queue = rpn->queue;
    int top = rpn->size - 1;

    // Initializing tree itself
    syntaxTree* tree = (syntaxTree*)malloc(sizeof(syntaxTree));
    tree->root = initTreeNode(queue[top--], NULL);
    treeNode* currentNode = tree->root;

    while (top >= 0) {
        if ( isValueNode(currentNode) == 1 || isVariableNode(currentNode) == 1 ) {
            currentNode = currentNode->parent;
        }
        if (currentNode->rightChild == NULL) {
            currentNode->rightChild = initTreeNode(queue[top--], currentNode);
            currentNode = currentNode->rightChild;
            continue;
        }
        else if (currentNode->leftChild == NULL) {
            currentNode->leftChild = initTreeNode(queue[top--], currentNode);
            currentNode = currentNode->leftChild;
            continue;
        }
        else {
            currentNode = currentNode->parent;
        }
    }
    return tree;
}

bool isLeaf(treeNode* node)
{
    if (node == NULL) return false;
    treeNode* lNode = node->leftChild;
    treeNode* rNode = node->rightChild;
    return (lNode == NULL && rNode == NULL);
}

bool isRightOperand(treeNode* node)
{
    if (node == NULL || node->parent == NULL) {
        return false;
    }
    treeNode* parent = node->parent;
    return parent->rightChild == node;
}
 // Function to check if the value of the element is zero
bool isZeroNode(treeNode* node)
{
    if (node == NULL) return false;
    exprElement expr = node->content;
    if (expr.type == VALUE && expr.data.value == 0.0) {
        return true;
    }
    if (expr.type == VARIABLE && expr.varCoeff == 0.0) {
        return true;
    }
    return false;
}
 // Evaluates numbers and variables of the same parent
exprElement evaluate(treeNode* node)
{
    if (isValueNode(node)) {
        return node->content; 
    }
    if (isVariableNode(node)) {
        return node->content;
    }   

    treeNode* lNode = node->leftChild;
    treeNode* rNode = node->rightChild;
    
    exprElement evaluatedExpr;
    exprElement lhs = evaluate(lNode);
    exprElement rhs = evaluate(rNode);
    operatorType op = node->content.data.oper;

    //
    bool bothValues    =  lhs.type == VALUE    && rhs.type == VALUE;
    //
    bool varAndValue   = (lhs.type == VARIABLE && rhs.type == VALUE) ||
                         (lhs.type == VALUE    && rhs.type == VARIABLE);
    //                    
    bool bothVariables = (lhs.type == VARIABLE && rhs.type == VARIABLE) &&
                         (lhs.data.variable == rhs.data.variable);
    // VALUE & VALUE
    if (bothValues) {
        double lValue = lhs.data.value;
        double rValue = rhs.data.value;
        evaluatedExpr.type = VALUE;
        switch (op) {
            case ADDITION:
                evaluatedExpr.data.value = lValue + rValue;
                break;
            case SUBTRACTION:
                evaluatedExpr.data.value = lValue - rValue;
                break;
            case MULTIPLICATION:
                evaluatedExpr.data.value = lValue * rValue;
                break;
            case DIVISION:
                evaluatedExpr.data.value = lValue / rValue;
                break;
            default:
                break;
        }
        node->content = evaluatedExpr;
        freeChildren(node);
    }
    // VARIABLE & VALUE
    if (varAndValue) {
        double value;
        char var;
        exprElement varExpr;
        if (lhs.type == VALUE) {
            value = lhs.data.value;
            var = rhs.data.variable;
            varExpr = rhs;
        }
        else {
            value = rhs.data.value;
            var = lhs.data.variable;
            varExpr = lhs;
        }
        evaluatedExpr.type = VARIABLE;
        evaluatedExpr.data.variable = var;
        switch (op) {
            case ADDITION:
                // a + 0 or 0 + a
                if (value == 0.0 || varExpr.varCoeff == 0.0) {
                    double result = value + varExpr.varCoeff;
                    evaluatedExpr.type = VALUE;
                    evaluatedExpr.data.value = result;
                    node->content = evaluatedExpr;
                    freeChildren(node);
                }
                break;
            case SUBTRACTION:
                // 0 - a or a - 0
                if (value == 0.0 || varExpr.varCoeff == 0.0) {
                    double result;
                    if (lhs.type == VALUE) {
                        result = value - varExpr.varCoeff;
                    }
                    else {
                        result = varExpr.varCoeff - value;
                    }
                    evaluatedExpr.type = VALUE;
                    evaluatedExpr.data.value = result;
                    node->content = evaluatedExpr;
                    freeChildren(node);
                }
                break;
            case MULTIPLICATION:
                evaluatedExpr.varCoeff = varExpr.varCoeff * value;
                node->content = evaluatedExpr;
                freeChildren(node);
                break;
            case DIVISION:
                if (rhs.type == VALUE) {
                    evaluatedExpr.varCoeff = 1.0 / value;
                    node->content = evaluatedExpr;
                    freeChildren(node);
                }
                break;
            default:
                break;
        }
    }
    // VARIABLE & VARIABLE
    if (bothVariables) {
        char var = lhs.data.variable;
        double lCoeff = lhs.varCoeff;
        double rCoeff = rhs.varCoeff;
        double result;
        evaluatedExpr.type = VARIABLE;
        evaluatedExpr.data.variable = var;
        switch (op) {
            // a + a
            case ADDITION:
                result = lCoeff + rCoeff;
                evaluatedExpr.varCoeff = result;
                if (result == 0.0) {
                    evaluatedExpr.type = VALUE;
                    evaluatedExpr.data.value = 0.0;
                }
                node->content = evaluatedExpr;
                freeChildren(node);
                break;
            // a - a
            case SUBTRACTION:
                result = lCoeff - rCoeff;
                evaluatedExpr.varCoeff = result;
                if (result == 0.0) {
                    evaluatedExpr.type = VALUE;
                    evaluatedExpr.data.value = 0.0;
                }
                node->content = evaluatedExpr;
                freeChildren(node);
                break;
            default:
                break;
        }
    }
    return node->content;
}
 // Function to reduce similar variables
int reduceSimilarTerms(treeNode* root)
{
    treeNode* stack[MAX_STACK_SIZE];
    int top = -1;

    operatorType curOper = UNKNOWN_OPERATOR;
    bool isAppropriate = false;
    
    operatorType firstOper  = UNKNOWN_OPERATOR;
    operatorType secondOper = UNKNOWN_OPERATOR;
    operatorType prevOper   = UNKNOWN_OPERATOR;

    unsigned int uniqueSymbols = 0;
    int symbCount = 0;
    unsigned int curSymbolMask = 0;

    treeNode* firstVarNode = NULL;
    char firstSymbol;
    treeNode* secondVarNode = NULL;
    char secondSymbol;

    bool isSubtraction = false;

    do {
        stack[++top] = root;
        while (top >= 0) {
            treeNode* node = stack[top--];
            treeNode* lNode = node->leftChild;
            treeNode* rNode = node->rightChild;

            exprElement expr = node->content;
            if (expr.type == OPERATOR) {
                prevOper = curOper;
                curOper = expr.data.oper;
            }
            isAppropriate = curOper == ADDITION || curOper == SUBTRACTION;

            if (lNode != NULL && isAppropriate) {
                stack[++top] = lNode;
            }
            if (rNode != NULL && isAppropriate) {
                stack[++top] = rNode;
            }
            if (isVariableNode(node)) {
                char var = node->content.data.variable;
                unsigned int symbol = 1u << (var - 'a');
                bool isUnique = (symbol & uniqueSymbols) == 0;
                // Found first variable
                if (firstVarNode == NULL && isUnique) {
                    uniqueSymbols |= symbol;
                    symbCount++;
                    firstVarNode = node;
                    curSymbolMask = symbol;
                    firstOper = curOper;
                }
                // Found second variable. Check if they are the same
                else {
                    secondVarNode = node;
                    if (firstVarNode == NULL) {
                        continue;
                    }
                    firstSymbol = firstVarNode->content.data.variable;
                    secondSymbol = secondVarNode->content.data.variable;
                    if (firstSymbol == ' ' || secondSymbol == ' ') {
                        continue;
                    }
                    if (firstSymbol == secondSymbol) {
                        secondOper = curOper;
                        break;
                    }
                }
            }
            secondVarNode = NULL;
        }
        // Reduce two found variables
        if (firstVarNode != NULL && secondVarNode != NULL) {
            exprElement evaluatedExpr;
            double lCoeff = firstVarNode->content.varCoeff;
            double rCoeff = secondVarNode->content.varCoeff;
            evaluatedExpr.type = VARIABLE;
            evaluatedExpr.data.variable = firstSymbol;

            if (isRightOperand(firstVarNode)) {
                if (firstOper == SUBTRACTION) {
                    isSubtraction = !isSubtraction;
                }
            }
            else {
                if (prevOper == SUBTRACTION) {
                    isSubtraction = !isSubtraction;
                    prevOper = UNKNOWN_OPERATOR;
                }
            }

            if (isRightOperand(secondVarNode)) {
                if (secondOper == SUBTRACTION) {
                    isSubtraction = !isSubtraction;
                }
            }
            else {
                if (prevOper == SUBTRACTION) {
                    isSubtraction = !isSubtraction;
                    prevOper = UNKNOWN_OPERATOR;
                }
            }

            if (isSubtraction) {
                evaluatedExpr.varCoeff = lCoeff - rCoeff;
                firstVarNode->content = evaluatedExpr;
            }
            else {
                evaluatedExpr.varCoeff = lCoeff + rCoeff;
                firstVarNode->content = evaluatedExpr;
            }
            secondVarNode->content.type = VALUE;
            secondVarNode->content.data.value = 0.0;
            secondVarNode->content.varCoeff = 0.0;

            uniqueSymbols &= ~curSymbolMask;
        }

        firstVarNode = NULL;
        secondVarNode = NULL;
        isSubtraction = false;
    } while (symbCount-- > 0);

    return 0;
}
 // Function that generally simplifies the tree
void simplifyTree(syntaxTree* tree, treeNode* root)
{
    evaluate(root);
    treeNode* stack[MAX_STACK_SIZE];
    int top = -1;
    stack[++top] = root;
    operatorType curOper = UNKNOWN_OPERATOR;
    // Search for every '+' or '-' in the tree then call
    // reduceSimilarTerms(node);
    while (top >= 0) {
        treeNode* node = stack[top--];
        treeNode* lNode = node->leftChild;
        treeNode* rNode = node->rightChild;

        if (lNode != NULL) {
            stack[++top] = lNode;
        }
        if (rNode != NULL) {
            stack[++top] = rNode;
        }

        exprElement expr = node->content;
        if (expr.type == OPERATOR) {
            curOper = expr.data.oper;
        }
        bool isAppropriate = curOper == ADDITION || curOper == SUBTRACTION;

        if (isAppropriate) {
            reduceSimilarTerms(node);
        }
    }
    evaluate(root);
}

void printTree(treeNode* root, int indent) 
{
    if (root == NULL) {
        return;
    }

    for (int i = 0; i < indent; i++) {
        if (i == indent - 1) {
            printf(" |-");
        }
        else {
            printf("   ");
        }
    }
    printf("[");
    printExprElement(root->content);
    printf("]\n");

    printTree(root->rightChild, indent + 1);
    printTree(root->leftChild, indent + 1);
    return;
}
 // Function to make an expression string ouf of AST
char* toInfix(treeNode* root, operatorType prevOper)
{
    char* result = malloc(MAX_LEN * sizeof(char));
    exprElement mid = root->content;
    
    if (isValueNode(root)) {
        if (root->content.data.value < 0) {
            sprintf(result, "(%.1lf)", mid.data.value);
        }
        else {
            sprintf(result, "%.1lf", mid.data.value);
        }
        return result;
    }
    if (isVariableNode(root)) {
        if (mid.varCoeff == 1.0) {
            sprintf(result, "%c", mid.data.variable);
        }
        else if (mid.varCoeff == 0.0) {
            sprintf(result, "0.0");
        }
        else if (mid.varCoeff < 0) {
            sprintf(result, "(%.1lf*%c)", mid.varCoeff, mid.data.variable);
        }
        else {
            sprintf(result, "%.1lf*%c", mid.varCoeff, mid.data.variable);
        }
        return result;
    }

    char op = operatorToChar(mid.data.oper);
    char* lhs = toInfix(root->leftChild, op);
    char* rhs = toInfix(root->rightChild, op);

    if (prevOper == '+' || prevOper == '-' || prevOper == 0) {
        sprintf(result, "%s %c %s", lhs, op, rhs);
    }
    else {
        sprintf(result, "(%s %c %s)", lhs, op, rhs);
    }

    free(lhs);
    free(rhs);

    return result;
}
     