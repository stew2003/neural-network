#ifndef _NEURAL_NETWORK_DATA_SET_
#define _NEURAL_NETWORK_DATA_SET_

#include "Matrix.h"

#define SIZE_OF_INPUTS 784 // 28*28 images
#define NUM_OUTPUTS 10 // 0-9

typedef struct DataSet {
    int size;
    Matrix** inputs;
    Matrix** expectedOutputs;
} DataSet;

DataSet* DataSet__create(int size, char* inputFilename, char* labelFilename);

void DataSet__destroy(DataSet* dataSet);

#endif