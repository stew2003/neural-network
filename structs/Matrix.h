#ifndef _NEURAL_NETWORK_MATRIX_
#define _NEURAL_NETWORK_MATRIX_

typedef struct Matrix
{
    int rows;
    int cols;
    double** values; //first pointer points to the rows, second to the columns
} Matrix;

// allocate memory and initialize an empty matrix of any size
Matrix* Matrix__create(int rows, int cols);

// free up the memory and destroy any matrix
void Matrix__destroy(Matrix* matrix);

// randomize the values of a matrix
void Matrix__randomize(Matrix* matrix, double min, double max);

// find the value of a matrix at any position within its bounds
double Matrix__at(Matrix* matrix, int rowPos, int colPos);

// set the value of a matrix within its bounds
void Matrix__set(Matrix* matrix, int rowPos, int colPos, double value);

// find the dot product (multiply) two matricies together
Matrix* Matrix__dot(Matrix* matrix1, Matrix* matrix2);

// add two matricies together
Matrix* Matrix__add(Matrix* matrix1, Matrix* matrix2);

// scale every item in a matrix by a scalar
Matrix* Matrix__scale(Matrix* matrix, double scalar);

// change every item in a matrix by a function
Matrix* Matrix__alter(Matrix* matrix, double (*f)(double));

// print out a matrix in a neat way
void Matrix__print(Matrix* matrix);

#endif