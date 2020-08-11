#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs/Matrix.h"
#include "structs/NeuralNetwork.h"
#include "structs/DataSet.h"
#include "utils/math.h"

int main() {
    srand(time(NULL));

    int nodes[] = {10, 5, 5, 4};
    NeuralNetwork* nn = NeuralNetwork__create(4, nodes);
    NeuralNetwork__randomize(nn, -10, 10);

    Matrix* inputs = Matrix__create(10, 1);
    Matrix__randomize(inputs, 0, 1);
 
    // NeuralNetwork__print(nn);
    NeuralNetwork__evaluate(inputs, nn);
    NeuralNetwork__print(nn);

    NeuralNetwork__destroy(nn);

    DataSet* dataSet = DataSet__create(10, "train-images-idx3-ubyte", "train-labels-idx1-ubyte");
    DataSet__destroy(dataSet);

    return 0;
}