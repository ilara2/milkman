
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

    static int created;
    static int destroyed;

    Matrix();
    Matrix(int _rows, int _cols);
    Matrix(const Matrix&);
    Matrix& operator = (const Matrix&);
    Matrix(float arr[], int idx, int len);
    ~Matrix();

    void multiply_direct(Matrix &);
    void multiply_direct(float);
    static void multiply(Matrix &, Matrix &, Matrix &);
    void multiply(Matrix &);

    static void add(Matrix &, Matrix &, Matrix &);
    void add(Matrix &);

    static void subtract(Matrix &, Matrix &, Matrix &);
    void subtract(Matrix &);

    static void transpose(Matrix &, Matrix &);

    static void sigmoid(Matrix &, Matrix&);
    Matrix sigmoid();
    static void relu(Matrix *&, Matrix&);
    static void softmax(Matrix *&, Matrix&);
    static void abs(Matrix &, Matrix &);
    Matrix abs();
    Matrix round();

    float sum();
    void randomize();
    void print();
    float randfloat(float min, float max);
    void printDim();

    void save(FILE*);
    void load(FILE*);
};

#endif
