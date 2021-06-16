
#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

class Matrix {
public:
    double **data;
    int rows, cols;

    static int created;
    static int destroyed;

    Matrix();
    Matrix(int _rows, int _cols);
    Matrix(const Matrix&);
    Matrix& operator = (const Matrix&);
    Matrix(double arr[], int idx, int len);

    ~Matrix();

    static Matrix multiply(Matrix a, Matrix b);
    static Matrix multiply(Matrix a, double b);
    static Matrix multiply_direct(Matrix a, Matrix b);

    static Matrix add(Matrix a, Matrix b);
    static Matrix add(Matrix a, double b);
    static Matrix subtract(Matrix a, Matrix b);
    static Matrix subtract(Matrix a, double b);
    static Matrix subtract(double a, Matrix b);

    static Matrix transpose(Matrix a);
    static Matrix sigmoid(Matrix a);
    static Matrix d_sigmoid(Matrix a);
    static Matrix abs(Matrix a);

    static Matrix copy(Matrix a);

    void multiply(Matrix a);
    void multiply(double a);
    void multiply_direct(Matrix a);

    void add(Matrix a);
    double average();
    double sum();
    void set();
    void randomize();
    void print();
    double randdouble(double min, double max);
    void printDim();

    void save(FILE*);
    void load(FILE*);
};

#endif
