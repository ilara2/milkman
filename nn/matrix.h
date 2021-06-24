
#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

class Matrix {
public:
    float **data;
    int rows, cols;

    Matrix();
    Matrix(int _rows, int _cols);
    Matrix(const Matrix&);
    Matrix& operator = (const Matrix&);
    Matrix(float arr[], int idx, int len);
    ~Matrix();

    void multiply_direct(Matrix &);
    void multiply_direct(float);
    static Matrix multiply(Matrix &, Matrix &);
    void multiply(Matrix &);

    static Matrix add(Matrix &, Matrix &);
    void add(Matrix &);

    static Matrix subtract(Matrix &, Matrix &);
    void subtract(Matrix &);

    static Matrix transpose(Matrix &);

    static Matrix sigmoid(Matrix &);
    Matrix derive_sigmoid();
    static void relu(Matrix *&, Matrix&);
    static void softmax(Matrix *&, Matrix&);
    
    static Matrix abs(Matrix &);
    Matrix abs();
    Matrix round();

    float sum();
    void randomize();
    void print();
    float randfloat(float min, float max);
    void printDim();

    void save(FILE*);
    void load(FILE*);
    void clearData();
};

#endif
