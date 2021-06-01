

#include "matrix.h"


int Matrix::cnt = 0;

// Constructors
Matrix::Matrix() {
    data = NULL;
    rows = 0;
    cols = 0;
}

Matrix::Matrix(int _rows, int _cols) {
    rows = _rows;
    cols = _cols;
    data = new float*[rows];

    for (int i = 0; i < rows; i++) {
        data[i] = new float[cols];
    }

    randomize();
    // fill();
}

Matrix::Matrix(int arr[], int idx, int len) {
    rows = len;
    cols = 1;
    data = new float*[rows];

    for (int i = 0; i < rows; i++) {
        data[i] = new float[cols];
        data[i][0] = (float)arr[i+idx];
    }
}

//  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //
// Static Function
Matrix Matrix::multiply(Matrix a, Matrix b) {
    if (a.cols != b.rows) {
        printf("Matrix multiplication must match\n");
        exit(0);
    }

    Matrix tmp = Matrix(a.rows, b.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < b.cols; j++) {
            // tmp.data[i][j] = ;
            float sum = 0;
            for (int k = 0; k < a.cols; k++) {
                sum += a.data[i][k] *b.data[k][j];
            }
            tmp.data[i][j] = sum;
        }
    }

    return tmp;
}

Matrix Matrix::multiply(Matrix a, float b) {
    Matrix tmp = Matrix(a.rows, a.cols);

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            tmp.data[i][j] = a.data[i][j] * b;
        }
    }
    return tmp;
}

Matrix Matrix::multiply_direct(Matrix a, Matrix b) {
    if (a.rows != b.rows || a.cols != b.cols) {
        printf("Matrix multiplication must match\n");
        exit(0);        
    }
    Matrix tmp = Matrix(a.rows, a.cols);

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            tmp.data[i][j] = a.data[i][j] * b.data[i][j];
        }
    }
    return tmp;
}


Matrix Matrix::add(Matrix a, Matrix b) {
    if (a.rows != b.rows && a.cols != b.cols) {
        printf("Cannot add matrices of different sizes");
        exit(0);
    }
    Matrix tmp = Matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            tmp.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return tmp;
}

Matrix Matrix::add(Matrix a, float b) {
    Matrix tmp = Matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            tmp.data[i][j] = a.data[i][j] + b;
        }
    }
    return tmp;
}


Matrix Matrix::subtract(Matrix a, Matrix b) {
    if (a.rows != b.rows && a.cols != b.cols) {
        printf("Cannot add matrices of different sizes");
        exit(0);
    }
    Matrix tmp = Matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            tmp.data[i][j] = a.data[i][j] - b.data[i][j];
        }
    }
    return tmp;
}

Matrix Matrix::subtract(Matrix a, float b) {
    Matrix tmp = Matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            tmp.data[i][j] = a.data[i][j] - b;
        }
    }
    return tmp;
}

Matrix Matrix::subtract(float b, Matrix a) {
    Matrix tmp = Matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            tmp.data[i][j] = b - a.data[i][j];
        }
    }
    return tmp;
}

Matrix Matrix::transpose(Matrix a) {
    Matrix tmp = Matrix(a.cols, a.rows);
    for (int i = 0; i < a.cols; i++) {
        for (int j = 0; j < a.rows; j++) {
            tmp.data[i][j] = a.data[j][i];
        }
    }
    return tmp;
}

Matrix Matrix::sigmoid(Matrix a) {
    Matrix tmp = Matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            tmp.data[i][j] = 1 / (1 + pow(e, -1 * a.data[i][j] ) );
        }
    }
    return tmp;
}

Matrix Matrix::d_sigmoid(Matrix a) {
    Matrix tmp = Matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            tmp.data[i][j] = a.data[i][j] * (1 - a.data[i][j]);
        }
    }
    return tmp;
}

Matrix Matrix::abs(Matrix a) {
    Matrix tmp = Matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            tmp.data[i][j] = fabs(a.data[i][j]);
        }
    }
    return tmp;
}

Matrix Matrix::copy(Matrix a) {

    Matrix tmp = Matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            tmp.data[i][j] = a.data[i][j];
        }
    }
    return tmp;
}

//  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //

void Matrix::multiply(Matrix a) {
    if (cols != a.rows) {
        printf("Matrix multiplication must match\n");
        exit(0);
    }

    Matrix tmp = Matrix(rows, a.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            float sum = 0;
            for (int k = 0; k < a.cols; k++) {
                sum += data[i][k] * a.data[k][j];
            }
            tmp.data[i][j] = sum;
        }
    }

    data = tmp.data;
}

void Matrix::multiply(float a) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[i][j] *= a;
        }
    }
}

void Matrix::multiply_direct(Matrix a) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[i][j] *= a.data[i][j];
        }
    }
}

void Matrix::add(Matrix a) {
    if (rows != a.rows && cols != a.cols) {
        printf("Cannot add matrices of different sizes");
        exit(0);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[i][j] += a.data[i][j];
        }
    }
}

void Matrix::randomize() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
        // for (int j = i; j < cols; j++) {
            // data[i][j] = randFloat(-0.5, 0.5);
            data[i][j] = randFloat(-1, 1);
            // if (i != j) {
            //  data[j][i] = -1 * data[i][j];
            // }
            // data[i][j] = 0.5;
        }
    }
}

void Matrix::fill() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[i][j] = 1.0 * ++cnt;
        }
    }   
}

void Matrix::print() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%.5f\t", data[i][j]);
        }
        printf("\n");
    }   
}

float Matrix::randFloat(float min, float max) {
    float tmp = (float)rand() / RAND_MAX;
    tmp *= (max - min);
    tmp += min;
    return tmp;
}

void Matrix::printDim() {
    printf("%dX%d\n", rows, cols);
}


float Matrix::average() {
    float sum = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sum += data[i][j];
        }
    }
    return sum/(rows*cols);
}

void Matrix::set(float arr[]) {
}