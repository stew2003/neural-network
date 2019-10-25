#include <math.h>
#include "math.h"

// squishes any number to between 0 and 1
float sigmoid(float x) {
    return (1 / (1 + exp(-x)));
}

// the derivative of the sigmoid function
float sigmoidPrime(float x) {
    // https://towardsdatascience.com/derivative-of-the-sigmoid-function-536880cf918e
    return sigmoid(x) * (1 - sigmoid(x));
}