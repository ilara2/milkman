
#ifndef NETWORK_H_
#define NETWORK_H_

#include "matrix.h"

class Network {
private:
    const int* const npl;
    int num_layers;
    float l_rate;
    Matrix *weights, *bias;
    
public:
    Network(const int* const, int);
    ~Network();
    void feed(float**, int);
    Matrix* predict(float*);
    float err(float**, int);
    void print();
    void save(const char*);
    void load(const char*);
    void setLearningRate(float);
    void test();
};

#endif