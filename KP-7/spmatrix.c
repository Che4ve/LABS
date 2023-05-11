#include "spmatrix.h"

sparseMatrix* initSparseMatrix(void)
{
    sparseMatrix* matrix = malloc( sizeof(sparseMatrix) );
    matrix->vectorAllocatedSize = VECTOR_DEFAULT_SIZE;
    matrix->vector = calloc( matrix->vectorAllocatedSize, sizeof(vectorElement) );
    matrix->rows = 0;
    matrix->cols = 0;
    matrix->vectorSize = 0;
    return matrix;
}

sparseMatrix* initSparseIdentityMatrix(int order)
{
    sparseMatrix* matrix = malloc( sizeof(sparseMatrix) );
    matrix->vectorAllocatedSize = VECTOR_DEFAULT_SIZE;
    matrix->vector = calloc( matrix->vectorAllocatedSize, sizeof(vectorElement) );
    matrix->rows = order;
    matrix->cols = order;
    matrix->vectorSize = 0;
    for (int i = 1; i <= order; i++) {
        if ( pushBack(matrix, i, i, 1.0) == -1 ) {
            freeSparseMatrix(matrix);
            return NULL;
        };
    }
    matrix->vector[matrix->vectorSize - 1] = NilElem;
    return matrix;
}

int pushBack(sparseMatrix* matrix, int row, int col, double data)
{
    if ( matrix->vectorSize == VECTOR_MAX_ELEMENTS ) {
        return -1;
    }
    if ( data == 0 && matrix->cols != col ) {
        return 0;
    }

    vectorElement* vector = matrix->vector;

    // Realloc if reached maximum size
    if ( matrix->vectorSize + 1 >= matrix->vectorAllocatedSize ) {
        matrix->vectorAllocatedSize *= 2;
        matrix->vector = realloc(matrix->vector, matrix->vectorAllocatedSize * sizeof(vectorElement));
    }

    if ( memcmp(&vector[0], &NilElem, sizeof(vectorElement) ) == 0) {
        // prevElement is equal to NilElem
        vectorElement initElement = { 0, { .row = 1 } };
        matrix->vector[0] = initElement;
        matrix->vectorSize++;
    }
   
    int index = matrix->vectorSize;

    vectorElement prevElement = vector[index - 1];
    vectorElement newElement     = { col, { .value  = data } }; 
    vectorElement closureElement = {   0, { .row = row + 1 } };

    if ( data == 0 && matrix->cols == col ) {
        vector[index - 1] = closureElement;
        return 1;
    }

    if ( prevElement.qualifier == 0 && prevElement.data.row == row ) {
        vector[index] = newElement;
        matrix->vectorSize++;
        vector[index + 1] = closureElement;
        matrix->vectorSize++;
    } else {
        vector[index - 1] = newElement;
        matrix->vectorSize++;
        vector[index] = closureElement;
    }

    return 1;
}

double get(sparseMatrix* matrix, int row, int col) 
{
    int index = find(matrix, row, col);
    if (index == -1) {
        return 0;
    } else {
        return matrix->vector[index].data.value;
    }
}

int find(sparseMatrix* matrix, int row, int col) 
{
    int currentRow = 0;
    for (int index = 0; index < matrix->vectorSize; index++) {
        vectorElement currentElement = matrix->vector[index];
        if (currentElement.qualifier == 0) {
            currentRow = currentElement.data.row;
            continue;
        }
        if (currentElement.qualifier != col) {
            continue;
        }
        if (currentRow == row) {
            return index;
        }
    }
    return -1;
}

int isNilElement(vectorElement* element)
{
    return memcmp(element, &NilElem, sizeof(vectorElement)) == 0;
}

int isSquare(sparseMatrix* matrix)
{
    if (matrix == NULL) {
        return -1;
    }
    return matrix->rows == matrix->cols;
}


int multiplyByConstant(sparseMatrix* matrix, double constant)
{
    vectorElement* vector = matrix->vector;
    for (int i = 0; i < matrix->vectorSize; i++) {
        if (vector[i].qualifier == 0) {
            continue;
        }
        vector[i].data.value *= constant;
    }
    return 0;
}

int addMatrices(sparseMatrix* m1, sparseMatrix* m2, sparseMatrix* result)
{
    if ( (m1->rows != m2->rows) || (m1->cols != m2->cols) ) {
        fprintf(stderr, "Error: Matrices must have the same dimensions.\n");
        return -1;
    }
    result->rows = m1->rows;
    result->cols = m1->cols;

    for (int i = 1; i <= result->rows; i++) {
        for (int j = 1; j <= result->cols; j++) {
            double m1Value = get(m1, i, j);
            double m2Value = get(m2, i, j);
            pushBack(result, i, j, m1Value + m2Value);
        }
    }
    result->vector[result->vectorSize - 1] = NilElem;
    result->vector = realloc(result->vector, result->vectorSize * sizeof(vectorElement));
    return 0;
}

int readSparseMatrix(sparseMatrix* matrix, FILE* stream)
{
    if (stream == NULL) {
        perror("Unnable to read stream.");
        return -1;
    }
    if (feof(stream)) {
        return -2;
    }
    int rows, cols;
    if (stream == stdin) {
        printf("Enter number of rows and columns: ");
        fflush(stream);
    }
    if (fscanf(stream, "%d %d", &rows, &cols) != 2) {
        return -2; // Failed to read matrix size, so assume end of file
    }
    if (stream == stdin) {
        printf("Enter the matrix in a standard format: \n");
    }
    matrix->rows = rows;
    matrix->cols = cols;
    int pushRet = 0;
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            double value;
            fscanf(stream, "%lf", &value);
            pushRet = pushBack(matrix, i, j, value);
        }
    }
    if (pushRet == -1) {
        fprintf(stderr, "Error: Vector '%p' has reached element limit.\n", matrix->vector);
        return -3;
    }
    matrix->vector[matrix->vectorSize - 1] = NilElem;
    matrix->vectorAllocatedSize = matrix->vectorSize;
    matrix->vector = realloc(matrix->vector, matrix->vectorAllocatedSize * sizeof(vectorElement));
    return 1;
}

int printSparseMatrix(sparseMatrix* matrix)
{
    for (int i = 0; i < VECTOR_DEFAULT_SIZE; i++) {
        vectorElement elem = matrix->vector[i];
        if (elem.qualifier == 0) {
            // the data is an int (stored in the `column` field)
            int row = elem.data.row;
            if ( row ) {
                printf("(next row: %d)\n", row);
            }
            else {
                printf("(vector size: %d)\n", matrix->vectorSize);
            }
        } else {
            // the data is a double (stored in the `value` field)
            double value = elem.data.value;
            printf("(col: %d, val: %.2lf)\n", elem.qualifier, value);
        }
        if ( isNilElement(&elem) ) {
            // elem is equal to NilElem
            break;
        }
    }
    return 0;
}

int printSparseAsDense(sparseMatrix* matrix)
{
    for (int i = 1; i <= matrix->rows; i++) {
        for (int j = 1; j <= matrix->cols; j++) {
            printf("%5.1lf  ", get(matrix, i, j)); 
        }
        printf("\n");
    }
    return 0;
}

int freeSparseMatrix(sparseMatrix* matrix)
{
    if (matrix == NULL) {
        return -1;
    }
    free(matrix->vector);
    matrix->vector = NULL;
    free(matrix);
    return 0;
}
