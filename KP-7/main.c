#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "spmatrix.h"

#define MAX_LEN 250
#define MAX_SIZE 100

void startMenu(void)
{
    printf("1. Enter new matrix.\n");
    printf("2. Choose a matrix to work with.\n");
    printf("0. Quit.\n");
}

void chooseMatrix(sparseMatrix** matrixList) 
{
    printf("] Here is the list of matrices:\n");
    for (int i = 0; i < MAX_SIZE; i++) {
        if ( matrixList[i] == NULL || isNilElement( &matrixList[i]->vector[0] ) ) {
            break;
        }
        printf("]>===<::>---\n");
        printf("%3d)\n", i + 1);
        printSparseAsDense(matrixList[i]);
    }
    printf("]>===<::>---\n");
    printf("Choose the matrix: ");
}

void actionMenu(void)
{
    printf("    1. Multiply by a value.\n");
    printf("    2. Calculate MATROCHLEN with the matrix.\n");
    printf("    3. Print in a sparse format.\n");
    printf("    4. Print in a dense format.\n");
    printf("    0. Go back.\n");
}

void addToList(sparseMatrix** matrixList, sparseMatrix* matrix)
{
    for (int index = 0; index < MAX_SIZE; index++) {
        if ( matrixList[index] == NULL && !isNilElement( &matrix->vector[0] ) ) {
            matrixList[index] = matrix;
            return;
        }
    }
}

int main(int argc, char** argv)
{
    bool isFile = false;
    char filename[MAX_LEN];
    FILE* inputStream;
    
    if (argc == 2) {
        printf("Reading data from %s file.\n", argv[1]);
        isFile = true;
        strncpy(filename, argv[1], MAX_LEN);
        inputStream = fopen(filename, "r");
        if (inputStream == NULL) {
            perror("Error");
            exit(ENOENT);
        }
    }
    else if (argc == 1) {
        printf("Reading data from user input.\n");
        inputStream = stdin;
    }
    else {
        printf("Usage: 'main.out <data_file>' or from user input\n");
        exit(1);
    }

    sparseMatrix** matrixList = calloc( MAX_SIZE, sizeof(sparseMatrix*) );

    if ( isFile ) {
        while ( true ) {
            sparseMatrix* matrix = initSparseMatrix();
            int readRet = 0;
            readRet = readSparseMatrix(matrix, inputStream);
            if ( readRet != 1 ) {
                if ( readRet == -3 ) { // Matrix was too big
                    freeSparseMatrix(matrix);
                    continue;
                }
                break;
            }
            addToList(matrixList, matrix);
        }
        fclose(inputStream);
    } 
    int option;
    do {
        startMenu();
        scanf("%d", &option);
        switch (option) {
            case 1: {
                sparseMatrix* matrix = initSparseMatrix();
                readSparseMatrix(matrix, stdin);
                addToList(matrixList, matrix);
                printf("Added.\n");
                break;
            }
            case 2: {
                int matrixChoice;
                chooseMatrix(matrixList);
                scanf("%d", &matrixChoice);
                if (matrixChoice < 1) {
                    fprintf(stderr, "Incorrect input.\n");
                    break;
                }
                sparseMatrix* currentMatrix; 
                if ( ( currentMatrix = matrixList[matrixChoice - 1] ) == NULL ) {
                    printf("There is no such matrix in the list.\n");
                    break;
                }
                do {
                    actionMenu();
                    scanf("%d", &matrixChoice);
                    switch (matrixChoice) {
                        case 1: { // Multiply by a value
                            int coeff;
                            printf("Enter coefficient: ");
                            scanf("%d", &coeff);
                            multiplyByConstant(currentMatrix, coeff);
                            printf("Done.\n");
                            break;
                        }
                        case 2: {
                            if ( !isSquare(currentMatrix) ) {
                                printf("Rejected. Matrix is not square.\n");
                                break;
                            }
                            int a, b; // Coefficients
                            sparseMatrix* identityMatrix = initSparseIdentityMatrix(currentMatrix->rows);
                            printf("Enter coefficients {a, b} for matrices: a * M + b * E: ");
                            scanf("%d", &a);
                            scanf("%d", &b);
                            multiplyByConstant(currentMatrix, a);
                            multiplyByConstant(identityMatrix, b);
                            sparseMatrix* resultMatrix = initSparseMatrix();
                            addMatrices(currentMatrix, identityMatrix, resultMatrix);
                            addToList(matrixList, resultMatrix);
                            printf("] Result: \n");
                            printf("]>===<::>---\n");
                            printSparseAsDense(resultMatrix);
                            printf("]>===<::>---\n");
                            printf("The result is added to the list as the last element.\n");
                            currentMatrix = resultMatrix;
                            printf("The result is now the matrix you're working with.\n");
                            freeSparseMatrix(identityMatrix);
                            break;
                        }
                        case 3: {
                            printf("]>===<::>---\n");
                            printSparseMatrix(currentMatrix);
                            printf("]>===<::>---\n");
                            break;
                        }
                        case 4: {
                            printf("]>===<::>---\n");
                            printSparseAsDense(currentMatrix);
                            printf("]>===<::>---\n");
                            break;
                        }
                        case 0: {
                            //free
                            break;
                        }
                    }
                } while (matrixChoice != 0);
                break;
            }
            case 0: {
                break;
            }
        }
    } while (option != 0);

    for (int i = 0; i < MAX_SIZE; i++) {
        if ( matrixList[i] == NULL ) {
            break;
        }
        freeSparseMatrix(matrixList[i]);
    }
    free(matrixList);
    
    return 0;
}
