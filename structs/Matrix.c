#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include "../utils/math.h"

// construct and allocate new matrix with any number of rows and columns
Matrix* Matrix__create(int rows, int cols) {
    // allocate memory for the bare matrix
    Matrix* matrix = malloc(sizeof(Matrix)); 

    // initalize the row and columns values of the matrix
    matrix->rows = rows;
    matrix->cols = cols;

    // allocate memory for the rows
    matrix->values = malloc(rows * sizeof(float*));

    //allocate memory for the columns and initialize as 0s (calloc)
    for (int i = 0; i < rows; i++) {
        matrix->values[i] = calloc(cols, sizeof(float));
    }

    return matrix;
};

// deallocate memory and destroy a martix
void Matrix__destroy(Matrix* matrix) {
    // free all of the rows (delete the columns)
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->values[i]);
    }

    // free the pointer to the two-dimensional array (delete the rows)
    free(matrix->values);

    // free the pointer to the struct
    free(matrix);
    return;
};

// randomizeall of the values in a matrix between a min and a max
void Matrix__randomize(Matrix* matrix, float min, float max) {
    // loop through every item in the matrix
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            matrix->values[i][j] = ((float) rand()/RAND_MAX) * (max-min) + min;
        }
    }

    return;
};

// find the value of a matrix at a position
float Matrix__at(Matrix* matrix, int rowPos, int colPos) {
    // check if the positions are within the bounds of the matrix
    if (rowPos < matrix->rows && colPos < matrix->cols) {
        return matrix->values[rowPos][colPos];
    } else {
        perror("Cannot find value at those positions. Positions out of bounds"), exit(1);
    }
}

// set the value of a matrix at a position
void Matrix__set(Matrix* matrix, int rowPos, int colPos, float value) {
    // check if the positions are within the bounds of the matrix
    if (rowPos < matrix->rows && colPos < matrix->cols) {
       matrix->values[rowPos][colPos] = value;
    } else {
        perror("Cannot set value at those positions. Positions out of bounds"), exit(1);
    }
}

// find the dot product of two matricies
Matrix* Matrix__dot(Matrix* matrix1, Matrix* matrix2) {
    // make sure the matricies are compatible for multipliation
    if (matrix1->cols == matrix2->rows) {
        // initialize a new matrix with the correct dimensions
        Matrix* product = Matrix__create(matrix1->rows, matrix2->cols);

        // do the matrix math
        for (int i = 0; i < matrix1->rows; i++) {
            for (int j = 0; j < matrix2->cols; j++) {
                for (int n = 0; n < matrix1->cols; n++) {
                    Matrix__set(product, i, j, (Matrix__at(product, i, j) + (Matrix__at(matrix1, i, n) * Matrix__at(matrix2, n, j))));
                    // product->values[i][j] += matrix1->values[i][n] * matrix2->values[n][j];
                }
            }
        }

        return product;
    } else {
        perror("Cannot take the dot product of these matricies"), exit(1);
    }
}

// add two matricies together
Matrix* Matrix__add(Matrix* matrix1, Matrix* matrix2) {
    //make sure the matricies have the exact same dimensions
    if (matrix1->rows == matrix2->rows && matrix1->cols == matrix2->cols) {
        // initialize a new matrix with the same dimensions
        Matrix* sum = Matrix__create(matrix1->rows, matrix1->cols);

        //loop through every item of the two matricies
        for (int i = 0; i < sum->rows; i++) {
            for (int j = 0; j < sum->cols; j++) {
                // set the new value to be the sum of the value of the two matricies
                Matrix__set(sum, i, j, (Matrix__at(matrix1, i, j) + Matrix__at(matrix2, i, j)));
                // sum->values[i][j] = matrix1->values[i][j] + matrix2->values[i][j];
            }
        }

        return sum;
    } else {
        perror("Cannot add these matricies"), exit(1);
    }
}

// multiply every item in a matrix by a scalar
Matrix* Matrix__scale(Matrix* matrix, float scalar) {
    // initialize a new matrix
    Matrix* scaled = Matrix__create(matrix->rows, matrix->cols);

    // loop through every item in the matrix
    for (int i = 0; i < scaled->rows; i++) {
        for (int j = 0; j < scaled->cols; j++) {
            // set the new value to be the sum of the value of the two matricies
            Matrix__set(scaled, i, j, (Matrix__at(matrix, i, j) * scalar));
            // scaled->values[i][j] = matrix->values[i][j] * scalar;
        }
    }

    return scaled;
}

// alter every item in a matrix by a function
Matrix* Matrix__alter(Matrix* matrix, float (*f)(float)) {
    // initialize a new matrix
    Matrix* altered = Matrix__create(matrix->rows, matrix->cols);

    // loop through every item in the new matrix

    for (int i = 0; i < altered->rows; i++) {
        for (int j = 0; j < altered->cols; j++) {
            // set the new value to be the sum of the value of the two matricies
            Matrix__set(altered, i, j, (*f)(Matrix__at(matrix, i, j)));
            // altered->values[i][j] = (*f)(matrix->values[i][j]);
        }
    }

    return altered;
}

//neatly print out a matrix
void Matrix__print(Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%f ", Matrix__at(matrix, i, j));
        }
        printf("\n");
    }
    return;
}