#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "DataSet.h"
#include "Matrix.h"

// swap all the bytes within an unsigned integer
// https://stackoverflow.com/questions/2182002/convert-big-endian-to-little-endian-in-c-without-using-provided-func
int endianSwap(int num) {
  return ((num>>24)&0xff) | // move byte 3 to byte 0
         ((num<<8)&0xff0000) | // move byte 1 to byte 2
         ((num>>8)&0xff00) | // move byte 2 to byte 1
         ((num<<24)&0xff000000); // byte 0 to byte 3
}

// create a dataset from a file of inputs and a file of outputs
DataSet* DataSet__create(int size, char* imagesFilename, char* labelsFilename) {

    // open the images file
    FILE* imagesFile = fopen(imagesFilename, "rb");

    //make sure images file was opened correctly
    if (imagesFile == NULL) { perror("Images file cannot be opened."), exit(1); }

    int magicNumber, numImages, numRows, numCols, imageSize;

    // read the first 4 bytes of the images file as the "magic number"
    fread(&magicNumber, 4, 1, imagesFile);
    magicNumber = endianSwap(magicNumber);
    if (magicNumber != 0x00000803) { perror("Invalid image file."), exit(1); }

    // read the next 4 bytes of the images file as the number of images
    fread(&numImages, 4, 1, imagesFile);
    numImages = endianSwap(numImages);
    printf("There are %d images in this set.\n", numImages);

    // read the next 4 bytes of the images file as the width in pixels of each image
    fread(&numRows, 4, 1, imagesFile);
    numRows = endianSwap(numRows);

    // read the next 4 bytes of the images file as the height in pixels of each image
    fread(&numCols, 4, 1, imagesFile);
    numCols = endianSwap(numCols);
    printf("Each image is %dx%d.\n", numRows, numCols);
    imageSize = numRows * numCols;


    // open the label file
    FILE* labelsFile = fopen(labelsFilename, "rb");

    // make sure images file was opened correctly
    if (labelsFile == NULL) { perror("Labels file be opened."), exit(1); }

    int numLabels;

    // read the first 4 bytes of the labels file as the "magic number"
    fread(&magicNumber, 4, 1, labelsFile);
    magicNumber = endianSwap(magicNumber);
    if (magicNumber != 0x00000801) { perror("Invalid labels file."), exit(1); }

    // read the next 4 bytes of the labels file as the number of labels
    fread(&numLabels, 4, 1, labelsFile);
    numLabels = endianSwap(numLabels);
    printf("There are %d labels in this set.\n", numLabels);


    // validate that the size of the dataset is not bigger than the size of the data provided
    if (size > numImages || size > numLabels) { perror("Cannot create dataset larger than data provided."), exit(1); }

    // allocate memory for the dataSet now that we know files are valid
    DataSet* dataSet = malloc(sizeof(DataSet));

    dataSet->size = size;
    dataSet->imageSize = imageSize;

    // allocate memory for the input matrix
    dataSet->inputs = malloc(sizeof(Matrix*) * size);

    // allocate memory for the output array
    dataSet->outputs = malloc(sizeof(Matrix*) * size);

    // populate the dataset with information from the opened files
    unsigned char pixel, label;
    for (int i = 0; i < size; i++) {
        dataSet->inputs[i] = Matrix__create(imageSize, 1); // allocate a vector of the image
        dataSet->outputs[i] = Matrix__create(NUM_OUTPUTS, 1); //allocate ouput vector
        // // populate the image vector
        for (int j = 0; j < imageSize; j++) {
            pixel = 0;
            fread(&pixel, 1, 1, imagesFile);
            Matrix__set(dataSet->inputs[i], j, 0, (double) pixel);
        }

        // populate the dataset
        label = 0;
        fread(&label, 1, 1, labelsFile);
        Matrix__set(dataSet->outputs[i], label, 0, 1.0);    
    }

    fclose(imagesFile);
    fclose(labelsFile);

    return dataSet;
}

// free all memory associated with a dataset
void DataSet__destroy(DataSet* dataSet) {
    
    //destroy all of the matricies
    for (int i = 0; i < dataSet->size; i++) {
        Matrix__destroy(dataSet->inputs[i]);
        Matrix__destroy(dataSet->outputs[i]);
    }

    //free the pointers to the matricies
    free(dataSet->inputs);
    free(dataSet->outputs);

    // free the pointer to the struct
    free(dataSet);

    return;
}