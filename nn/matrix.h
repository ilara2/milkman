
#ifndef MATRIX_H_
#define MATRIX_H_

#define e 2.71828

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

class Matrix {
public:
    static int cnt;
    float **data;
    int rows, cols;

    // Constructors
    Matrix();
    Matrix(int _rows, int _cols);
    Matrix(int arr[], int idx, int len);

    
    static Matrix multiply(Matrix a, Matrix b);
    static Matrix multiply(Matrix a, float b);

    static Matrix multiply_direct(Matrix a, Matrix b);

    static Matrix add(Matrix a, Matrix b);
    static Matrix add(Matrix a, float b);

    static Matrix subtract(Matrix a, Matrix b);
    static Matrix subtract(Matrix a, float b);
    static Matrix subtract(float a, Matrix b);

    static Matrix transpose(Matrix a);
    static Matrix sigmoid(Matrix a);
    static Matrix d_sigmoid(Matrix a);
    static Matrix abs(Matrix a);

    static Matrix copy(Matrix a);

    void multiply(Matrix a);
    void multiply(float a);
    void multiply_direct(Matrix a);

    void add(Matrix a);
    float average();
    void set(float arr[]);

    void randomize();
    void fill();
    void print();
    float randFloat(float min, float max);
    void printDim();
};

#endif
