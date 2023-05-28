#include "mathparser.h"

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

void printExprElement(exprElement element)
{
    switch (element.type) {
        case VALUE: 
            printf("%.1lf", element.data.value);
            break;
        case VARIABLE: 
            printf("%c", element.data.variable);
            break;
        case OPERATOR: 
            printf("%c", operatorToChar(element.data.oper));
            break;
        default:
            break;
    }
}

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

rpnQueue* parseExpr(char* inputStr)
{
    int len = 0;
    for(len; inputStr[len] != '\0'; ++len);
    printf("Length of string: %d\n", len);

    operatorType operatorStack[MAX_STACK_SIZE];
    int stackTop = -1;
    rpnQueue* outputQueue = (rpnQueue*)malloc(sizeof(rpnQueue));
    outputQueue->queue = (exprElement*)calloc(MAX_LEN, sizeof(exprElement));
    outputQueue->size = 0;
    int queueTop = -1;

    for (int i = 0; i < len; i++)  {
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
                                              .data.variable = *currentPtr };
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
    for (int i = 0; i <= queueTop; i++) {
        printExprElement(outputQueue->queue[i]);
        printf(", ");
    }
    return outputQueue;
}

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

int isValueNode(treeNode* node)
{
    if (node == NULL) return -1;
    return node->content.type == VALUE;
}

int isVariableNode(treeNode* node)
{
    if (node == NULL) return -1;
    return node->content.type == VARIABLE;
}

syntaxTree* buildSyntaxTree(rpnQueue* rpn)
{
    exprElement* queue = rpn->queue;
    int top = rpn->size - 1;

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
    printf("\n===\n");
    printTree(tree->root, 0);
    return tree;
}

bool isLeaf(treeNode* node)
{
    if (node == NULL) return false;
    treeNode* lNode = node->leftChild;
    treeNode* rNode = node->rightChild;
    return (lNode == NULL && rNode == NULL);
}

treeNode* findLowestSubtree(treeNode* root) 
{
    typedef struct {
        treeNode* ptr;
        int level;
    } stackElem;

    treeNode* result = NULL;
    stackElem stack[MAX_STACK_SIZE];
    int top = -1;
    int level = 0;
    int maxLevel = level;

    stack[++top] = (stackElem){ root, level };

    while (top >= 0) {
        int prevTop = top;
        stackElem curElem = stack[top--];
        treeNode* node = curElem.ptr;
        int level = curElem.level;

        treeNode* lNode = node->leftChild;
        treeNode* rNode = node->rightChild;
        if (lNode != NULL) {
            stack[++top] = (stackElem){lNode, level + 1};
        }
        if (rNode != NULL) {
            stack[++top] = (stackElem){rNode, level + 1};
        }  
        if (isLeaf(lNode) && isLeaf(rNode)) {
            if (level >= maxLevel) {
                maxLevel = level;
                result = node;
            }
        }
    }
    return result;
}

exprElement _eval(treeNode* node)
{
    if (node == NULL) return NULL;

}


exprElement evaluate(treeNode* node)
{
    typedef struct {
        double coefficient;
        exprElement var;
    } variableType;
    treeNode* lNode = node->leftChild;
    treeNode* rNode = node->rightChild;
    bool bothValues = isValueNode(lNode) && isValueNode(rNode);
    bool varAndValue = (isValueNode(lNode) && isVariableNode(rNode)) ||
                       (isVariableNode(lNode) && isValueNode(rNode));
    
    if (bothValues) {
        operatorType op = node->content.data.oper;
        double lhs = lNode->content.data.value;
        double rhs = rNode->content.data.value;
        exprElement result;
        result.type = VALUE;
        switch (op) {
            case ADDITION:
                result.data.value = lhs + rhs;
                break;
            case SUBTRACTION:
                result.data.value = lhs - rhs;
                break;
            case MULTIPLICATION:
                result.data.value = lhs * rhs;
                break;
            case DIVISION:
                result.data.value = lhs / rhs;
                break;
            default:
                break;
        }
        return result;
    }
    if (varAndValue) {

    }
}

void simplifyTree(syntaxTree* tree, treeNode* root)
{
    treeNode* lowestExpr = findLowestSubtree(root); 
    //evaluate(tree, root);
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

char* toInfix(treeNode* root, bool evaluate)
{
    char* result = malloc(MAX_LEN * sizeof(char));
    exprElement mid = root->content;

    if (isValueNode(root)) {
        sprintf(result, "%.1lf", mid.data.value);
        return result;
    }
    if (isVariableNode(root)) {
        sprintf(result, "%c", mid.data.variable);
        return result;
    }

    char op = operatorToChar(mid.data.oper);

    char* lhs = toInfix(root->leftChild, evaluate);
    char* rhs = toInfix(root->rightChild, evaluate);

    sprintf(result, "(%s %c %s)", lhs, op, rhs);

    free(lhs);
    free(rhs);

    return result;
}
     