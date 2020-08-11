#ifndef _NEURAL_NETWORK_NEURAL_NETWORK_
#define _NEURAL_NETWORK_NEURAL_NETWORK_

#include "Matrix.h"

typedef struct NeuralNetwork
{
    int layers;
    Matrix** nodes;
    Matrix** weights; //two dimensional array of matricies
    Matrix** biases; //two dimensional array of matricies
} NeuralNetwork;

// allocate memory and create an empty neural network
NeuralNetwork* NeuralNetwork__create(int layers, int* params);

// deallocate memory and destroy a neural network
void NeuralNetwork__destroy(NeuralNetwork* neuralNetwork);

// randomize all of the values of a neural network
void NeuralNetwork__randomize(NeuralNetwork* neuralNetwork, double min, double max);

// print out a neural network neatly
void NeuralNetwork__print(NeuralNetwork* neuralNetwork);

// evaluate the neural network with a set of inputs
void NeuralNetwork__evaluate(Matrix* inputs, NeuralNetwork* neuralNetwork);

#endif