
#ifndef NETWORK_H_
#define NETWORK_H_

#include "matrix.h"

class Network {
public:
    const int* const npl;
    int num_layers;
    float l_rate;
    Matrix *weights, *bias;
    
    Network(const int* const, int);
    void feed(double**, int);
    Matrix predict(double*);
    Matrix err(double**, int);
    void print();
};

#endif