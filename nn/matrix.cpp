
#include "matrix.h"
#define euler 2.71828

Matrix::Matrix() {
    data = nullptr;
    rows = 0;
    cols = 0;
}

Matrix::Matrix(int _rows, int _cols) {
    rows = _rows;
    cols = _cols;
    data = new float*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new float[cols];
        for (int j = 0; j < cols; j++) {
            data[i][j] = 0;
        }
    }
}

Matrix& Matrix::operator=(const Matrix& obj) {
    clearData();
    rows = obj.rows;
    cols = obj.cols;
    data = new float*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new float[cols];
        for (int j = 0; j < cols; j++) {
            data[i][j] = obj.data[i][j];
        }
    }
    // return *this;
};

Matrix::Matrix(const Matrix &obj) {
    rows = obj.rows;
    cols = obj.cols;
    data = new float*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new float[cols];
        for (int j = 0; j < cols; j++) {
            data[i][j] = obj.data[i][j];
        }
    }
}

Matrix::Matrix(float arr[], int idx, int len) {
    rows = len;
    cols = 1;
    data = new float*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new float[cols];
        data[i][0] = (float)arr[i+idx];
    }
}

Matrix::~Matrix() {
    clearData();
}

Matrix Matrix::multiply(Matrix &a, Matrix &b) {
    if (a.cols != b.rows) {
        printf("Error: Matrix Matrix::multiply(Matrix *&source, Matrix &a, Matrix &b)\n"
            "Dimensions do not match\n");
        exit(0);
    }
    Matrix tmp(a.rows, b.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < b.cols; j++) {
            for (int k = 0; k < a.cols; k++) {
                tmp.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return tmp;
}

void Matrix::multiply(Matrix &a) {
    if (cols != a.rows) {
        printf("Error: void Matrix::multiply(Matrix *&source, Matrix &a, Matrix &b)\n"
            "Dimensions do not match\n");
        exit(0);
    }
    Matrix tmp = multiply(*this, a);
    *this = tmp;
}

void Matrix::multiply_direct(Matrix &a) {
    if (a.rows != rows || a.cols != cols) {
        printf("Error: void Matrix::multiply(Matrix &a)\n"
            "Dimensions do not match\n");
        exit(0);
    }
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            data[i][j] *= a.data[i][j];
        }
    }
}

void Matrix::multiply_direct(float a) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[i][j] *= a;
        }
    }
}

Matrix Matrix::add(Matrix &a, Matrix &b) {
    if (a.rows != b.rows || a.cols != b.cols) {
        printf("Error: void Matrix::add(Matrix *&source, Matrix &a, Matrix &b)\n"
            "Dimensions do not match\n");
        exit(0);
    }
    Matrix tmp(a.rows, b.cols);
    for (int i = 0; i < tmp.rows; i++) {
        for (int j = 0; j < tmp.cols; j++) {
            tmp.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return tmp;
}

void Matrix::add(Matrix &a) {
    if (a.rows != rows || a.cols != cols) {
        printf("Error: void Matrix::add(Matrix &a)\n"
            "Dimensions do not match\n");
        exit(0);
    }
    Matrix tmp = add(*this, a);
    *this = tmp;
}

Matrix Matrix::subtract(Matrix &a, Matrix &b) {
    if (a.rows != b.rows || a.cols != b.cols) {
        printf("Error: void Matrix::subtract(Matrix *&source, Matrix &a, Matrix &b)\n"
            "Dimensions do not match\n");
        exit(0);
    }
    Matrix tmp(a.rows, b.cols);
    for (int i = 0; i < tmp.rows; i++) {
        for (int j = 0; j < tmp.cols; j++) {
            tmp.data[i][j] = a.data[i][j] - b.data[i][j];
        }
    }
    return tmp;
}

void Matrix::subtract(Matrix &a) {
    if (a.rows != rows || a.cols != cols) {
        printf("Error: void Matrix::subtract(Matrix &a)\n"
            "Dimensions do not match\n");
        exit(0);
    }
    Matrix tmp = subtract(*this, a);
    *this = tmp;
}

Matrix Matrix::transpose(Matrix &a) {
    Matrix tmp(a.cols, a.rows);
    for (int i = 0; i < tmp.rows; i++) {
        for (int j = 0; j < tmp.cols; j++) {
            tmp.data[i][j] = a.data[j][i];
        }
    }
    return tmp;
}

Matrix Matrix::sigmoid(Matrix& a) {
    Matrix tmp(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            tmp.data[i][j] = 1 / (1 + pow(euler, -1 * a.data[i][j] ) );
        }
    }
    return tmp;
}

Matrix Matrix::derive_sigmoid() {
    Matrix t(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            t.data[i][j] = data[i][j] * (1 - data[i][j]);
        }
    }
    return t;
}

void Matrix::relu(Matrix *&source, Matrix& a) {
    source = new Matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            source->data[i][j] = (a.data[i][j] > 0)?a.data[i][j]:0;
        }
    }
}

void Matrix::softmax(Matrix *&source, Matrix& a) {
    if (a.cols != 1) {
        printf("Error: void Matrix::softmax(Matrix *&source, Matrix& a)\n"
            "Matrix must only have one column\n");
        exit(0);
    }
    source = new Matrix(a.rows, a.cols);
    float denom = 0;
    for (int i = 0; i < a.rows; i++) {
        denom += pow(euler, a.data[i][0]);
    }
    for (int i = 0; i < a.rows; i++) {
        source->data[i][0] = pow(euler, a.data[i][0])/denom;
    }
}

Matrix Matrix::abs(Matrix &a) {
    Matrix tmp(a.rows, a.cols);
    for (int i = 0; i < tmp.rows; i++) {
        for (int j = 0; j < tmp.cols; j++) {
            tmp.data[i][j] = fabs(a.data[i][j]);
        }
    }
    return tmp;
}

Matrix Matrix::abs() {
    Matrix t(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            t.data[i][j] = fabs(data[i][j]);
        }
    }
    return t;
}

Matrix Matrix::round() {
    Matrix t(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            t.data[i][j] = (data[i][j] >= .5) ? 1 : 0;
        }
    }
    return t;
}

void Matrix::randomize() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[i][j] = randfloat(-1, 1);
        }
    }
}

void Matrix::print() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%8.5f,", data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

float Matrix::randfloat(float min, float max) {
    float tmp = (float)rand() / RAND_MAX;
    tmp *= (max - min);
    tmp += min;
    return tmp;
}

void Matrix::printDim() {
    printf("%dX%d\n", rows, cols);
}

float Matrix::sum() {
    float ret = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            ret += data[i][j];
        }
    }
    return ret;
}

void Matrix::save(FILE* file) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%8.5f,", data[i][j]);
        }
        fprintf(file, "\n");
    }
}

void Matrix::load(FILE* file) {
    if (!file) {
        printf("Could not load file\n");
        return;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fscanf(file, "%f,", &data[i][j]);
        }
        fscanf(file, "\n");
    }
}

void Matrix::clearData() {
    if (data == nullptr) return;
    for (int i = 0; i < rows; i++) {
        delete [] data[i];
        data[i] = 0;
    }
    delete [] data;
    data = 0;
}
