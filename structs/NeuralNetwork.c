#include <stdio.h>
#include <stdlib.h>
#include "../utils/math.h"
#include "NeuralNetwork.h"
#include "Matrix.h"

// construct and allocate a new neural network
NeuralNetwork* NeuralNetwork__create(int layers, int* nodes) {
    // allocate memory for base neural network
    NeuralNetwork * neuralNetwork = malloc(sizeof(NeuralNetwork));

    // set the layers and parameters of the neural network
    neuralNetwork->layers = layers;

    // allocate memory for the nodes matrix list
    neuralNetwork->nodes = malloc(sizeof(Matrix*) * layers);

    // allocate memory for the weights matricies
    neuralNetwork->weights = malloc(sizeof(Matrix*) * (layers - 1));
    
    // allocate memory for the biases matricies
    neuralNetwork->biases = malloc(sizeof(Matrix*) * (layers - 1));

    // initialize all of the matricies based on the parameters
    for (int i = 0; i < (neuralNetwork->layers - 1); i++) {
        // weight matrix has nodes[i+1] rows and nodes[i] columns
        neuralNetwork->weights[i] = Matrix__create(nodes[i+1], nodes[i]);
        // biases matrix has nodes[i+1] rows and only 1 column
        neuralNetwork->biases[i] = Matrix__create(nodes[i+1], 1);
    }

    return neuralNetwork;
}

// destroy a neural network
void NeuralNetwork__destroy(NeuralNetwork* neuralNetwork) {

    //destroy all of the matricies
    for (int i = 0; i < neuralNetwork->layers; i++) {
        if (neuralNetwork->nodes[i] != NULL) {
            Matrix__destroy(neuralNetwork->nodes[i]);
        }
        if (i < (neuralNetwork->layers - 1)) { 
            Matrix__destroy(neuralNetwork->weights[i]);
            Matrix__destroy(neuralNetwork->biases[i]);
        }
    }

    //free the pointers to the matricies
    free(neuralNetwork->weights);
    free(neuralNetwork->biases);
    free(neuralNetwork->nodes);

    // free the pointer to the struct
    free(neuralNetwork);

    return;
}

// randomize all the values in a neural network
void NeuralNetwork__randomize(NeuralNetwork* neuralNetwork, double min, double max) {
    // loop through all of the matricies
    for (int i = 0; i < (neuralNetwork->layers - 1); i++) {
        Matrix__randomize(neuralNetwork->weights[i], min, max);
        Matrix__randomize(neuralNetwork->biases[i], min, max);
    }
    return;
}

// print out a neural network neatly
void NeuralNetwork__print(NeuralNetwork* neuralNetwork) {

    // loop through all of the matricies
    for (int i = 0; i < neuralNetwork->layers; i++) {
        // print the values (only if evaluate has been called first)
        if(neuralNetwork->nodes[i] != NULL) {
            printf("Layer %d values\n", i);
            Matrix__print(neuralNetwork->nodes[i]);
            printf("\n");
        }

        // make sure the weights and biases are within bounds
        if (i < (neuralNetwork->layers -1)) {
            printf("Layer %d weights\n", i);
            Matrix__print(neuralNetwork->weights[i]);

            printf("\n");

            printf("Layer %d biases.\n", i);
            Matrix__print(neuralNetwork->biases[i]);

            printf("\n\n");
        }
    } 
    return;  
}

// evaluate a neural network based on a matrix of inputs
void NeuralNetwork__evaluate(Matrix* inputs, NeuralNetwork* neuralNetwork) {
    // set up the matricies to store the node values
    Matrix* multipliedMatrix;
    Matrix* addedMatrix;

    // set the first row of nodes to the inputs
    neuralNetwork->nodes[0] = inputs;

    // loop through all of the layers
    for(int i = 1; i < neuralNetwork->layers; i++) {
        multipliedMatrix = Matrix__dot(neuralNetwork->weights[i-1], neuralNetwork->nodes[i-1]);
        addedMatrix = Matrix__add(multipliedMatrix, neuralNetwork->biases[i-1]);
        neuralNetwork->nodes[i] = Matrix__alter(addedMatrix, sigmoid);

        Matrix__destroy(multipliedMatrix);
        Matrix__destroy(addedMatrix);
    }
    return;
}

