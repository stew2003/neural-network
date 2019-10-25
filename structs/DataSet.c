#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "DataSet.h"
#include "Matrix.h"

// create a dataset from a file of inputs and a file of outputs
DataSet* DataSet__create(int size, char* inputFilename, char* labelFilename) {

    // allocate memory for the dataSet
    DataSet* dataSet = malloc(sizeof(DataSet*));

    dataSet->size = size;

    // allocate memory for the input matrix
    dataSet->inputs = malloc(sizeof(Matrix*) * size);
    dataSet->inputs[0] = Matrix__create(5,5);

    // allocate memory for the output matrix
    dataSet->expectedOutputs = malloc(sizeof(Matrix*) * size);
    dataSet->expectedOutputs[0] = Matrix__create(5,5);

    // open the input file and output file
    FILE* inputFile = fopen(inputFilename, "r");

    //make sure both files were opened correctly
    if (inputFile == NULL) {
        perror("Files cannot be opened."), exit(1);
    }

    // printf("Hello!\n");
    int magic_number_bytes[4];
    magic_number_bytes[0] = fgetc(inputFile);
    magic_number_bytes[1] = fgetc(inputFile);
    magic_number_bytes[2] = fgetc(inputFile);
    magic_number_bytes[3] = fgetc(inputFile);

    int comp_size[4];
    comp_size[0] = fgetc(inputFile);
    comp_size[1] = fgetc(inputFile);
    comp_size[2] = fgetc(inputFile);
    comp_size[3] = fgetc(inputFile);

    printf("Char: %d %d %d %d", comp_size[0], comp_size[1], comp_size[2], comp_size[3]);

    fclose(inputFile);

    return dataSet;
}

// free all memory associated with a dataset
void DataSet__destroy(DataSet* dataSet) {
    
    //destroy all of the matricies
    for (int i = 0; i < dataSet->size; i++) {
        Matrix__print(dataSet->inputs[i]);
        Matrix__destroy(dataSet->inputs[i]);

        Matrix__print(dataSet->expectedOutputs[i]);
        Matrix__destroy(dataSet->expectedOutputs[i]);
    }

    //free the pointers to the matricies
    free(dataSet->inputs);
    free(dataSet->expectedOutputs);

    // free the pointer to the struct
    free(dataSet);

    return;
}