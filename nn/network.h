

#ifndef NETWORK_H_
#define NETWORK_H_


#include "matrix.h"


class Network {
public:
    // Nodes
    Matrix input, hidden, output;

    // Layers
    Matrix input_weights, hidden_weights;
    Matrix original_input_weights, original_hidden_weights;

    // Bias
    Matrix hidden_bias, output_bias;
    Matrix og_hidden_bias, og_output_bias;

    // Errors
    Matrix hidden_error, output_error;

    // Variable
    float l_rate;

    Network(int _input, int _hidden, int _output);
    void feed(int **data, int);
    Matrix predict(int **data, int len);
    Matrix predictShow(int **data, int len);
    void print();
    void fill();
    void randomize();
    void goBack();
    void weights();
};


#endif