#ifndef _NEURAL_NETWORK_DATA_SET_
#define _NEURAL_NETWORK_DATA_SET_

#include "Matrix.h"

#define NUM_OUTPUTS 10 // 0-9

int endianSwap(int num);

typedef struct DataSet {
    int size;
    int imageSize;
    Matrix** inputs;
    Matrix** outputs;
} DataSet;

DataSet* DataSet__create(int size, char* imagesFilename, char* labelsFilename);

void DataSet__destroy(DataSet* dataSet);

#endif