
#include "matrix.h"
#define euler 2.71828

int Matrix::created = 0;
int Matrix::destroyed = 0;

Matrix::Matrix() {
    // printf("%d created\n", ++created);
    data = NULL;
    rows = 0;
    cols = 0;
}

Matrix::Matrix(int _rows, int _cols) {
    // printf("%d created\n", ++created);
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
    rows = obj.rows;
    cols = obj.cols;
    data = new float*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new float[cols];
        for (int j = 0; j < cols; j++) {
            data[i][j] = obj.data[i][j];
        }
    }
};

Matrix::Matrix(const Matrix &obj) {
    // printf("%d created\n", ++created);
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
    // printf("%d created\n", ++created);
    rows = len;
    cols = 1;
    data = new float*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new float[cols];
        data[i][0] = (float)arr[i+idx];
    }
}

Matrix::~Matrix() {
    // printf("\t%d destroyed\n", ++destroyed);
    printf("\r");
    for (int i = 0; i < rows; i++) {
        delete [] data[i];
    }
    delete [] data;
}

void Matrix::multiply(Matrix &source, Matrix &a, Matrix &b) {
    if (a.cols != b.rows) {
        printf("Error: void Matrix::multiply(Matrix *&source, Matrix &a, Matrix &b)\n"
            "Dimensions do not match\n");
        exit(0);
    }
    source = Matrix(a.rows, b.cols);
    for (int i = 0; i < source.rows; i++) {
        for (int j = 0; j < source.cols; j++) {
            for (int k = 0; k < a.cols; k++) {
                source.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
}

void Matrix::multiply(Matrix &a) {
    if (cols != a.rows) {
        printf("Error: void Matrix::multiply(Matrix &a)\n"
            "Dimensions do not match\n");
        exit(0);
    }
    Matrix t = *this;
    multiply(*this, t, a);
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

void Matrix::add(Matrix &source, Matrix &a, Matrix &b) {
    if (a.rows != b.rows || a.cols != b.cols) {
        printf("Error: void Matrix::add(Matrix *&source, Matrix &a, Matrix &b)\n"
            "Dimensions do not match\n");
        exit(0);
    }    
    source = Matrix(a.rows, b.cols);
    for (int i = 0; i < source.rows; i++) {
        for (int j = 0; j < source.cols; j++) {
            source.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
}

void Matrix::add(Matrix &a) {
    if (a.rows != rows || a.cols != cols) {
        printf("Error: void Matrix::add(Matrix &a)\n"
            "Dimensions do not match\n");
        exit(0);
    }
    Matrix t = *this;
    add(*this, t, a);
}

void Matrix::subtract(Matrix &source, Matrix &a, Matrix &b) {
    if (a.rows != b.rows || a.cols != b.cols) {
        printf("Error: void Matrix::subtract(Matrix *&source, Matrix &a, Matrix &b)\n"
            "Dimensions do not match\n");
        exit(0);
    }    
    source = Matrix(a.rows, b.cols);
    for (int i = 0; i < source.rows; i++) {
        for (int j = 0; j < source.cols; j++) {
            source.data[i][j] = a.data[i][j] - b.data[i][j];
        }
    }
}

void Matrix::subtract(Matrix &a) {
    if (a.rows != rows || a.cols != cols) {
        printf("Error: void Matrix::subtract(Matrix &a)\n"
            "Dimensions do not match\n");
        exit(0);
    }
    Matrix t = *this;
    subtract(*this, t, a);
}

void Matrix::transpose(Matrix &source, Matrix &a) {
    source = Matrix(a.cols, a.rows);
    for (int i = 0; i < a.cols; i++) {
        for (int j = 0; j < a.rows; j++) {
            source.data[i][j] = a.data[j][i];
        }
    }
}

void Matrix::sigmoid(Matrix &source, Matrix& a) {
    source = Matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            source.data[i][j] = 1 / (1 + pow(euler, -1 * a.data[i][j] ) );
        }
    }
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

Matrix Matrix::sigmoid() {
    Matrix t(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            t.data[i][j] = data[i][j] * (1 - data[i][j]);
        }
    }
    return t;
}

void Matrix::abs(Matrix &source, Matrix &a) {
    source = Matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            source.data[i][j] = fabs(a.data[i][j]);
        }
    }
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
            float* tmp;
            fscanf(file, "%f,", &data[i][j]);
        }
        fscanf(file, "\n");
    }
}
