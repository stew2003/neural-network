#include <math.h>
#include "math.h"

// squishes any number to between 0 and 1
double sigmoid(double x) {
    return (1 / (1 + exp(-x)));
}

// the derivative of the sigmoid function
double sigmoidPrime(double x) {
    // https://towardsdatascience.com/derivative-of-the-sigmoid-function-536880cf918e
    return sigmoid(x) * (1 - sigmoid(x));
}