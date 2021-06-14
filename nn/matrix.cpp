
#include "matrix.h"
#define euler 2.71828

int Matrix::created = 0;
int Matrix::destroyed = 0;

// Constructors
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
    data = new double*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new double[cols];
    }
}

Matrix& Matrix::operator=(const Matrix& obj) {
    rows = obj.rows;
    cols = obj.cols;
    data = new double*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new double[cols];
        for (int j = 0; j < cols; j++) {
            data[i][j] = obj.data[i][j];
        }
    }
};

Matrix::Matrix(const Matrix &obj) {
    // printf("%d created\n", ++created);
    rows = obj.rows;
    cols = obj.cols;
    data = new double*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new double[cols];
        for (int j = 0; j < cols; j++) {
            data[i][j] = obj.data[i][j];
        }
    }
}

Matrix::Matrix(double arr[], int idx, int len) {
    // printf("%d created\n", ++created);
    rows = len;
    cols = 1;
    data = new double*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new double[cols];
        data[i][0] = (double)arr[i+idx];
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
            double sum = 0;
            for (int k = 0; k < a.cols; k++) {
                sum += a.data[i][k] *b.data[k][j];
            }
            tmp.data[i][j] = sum;
        }
    }

    return tmp;
}

Matrix Matrix::multiply(Matrix a, double b) {
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

Matrix Matrix::add(Matrix a, double b) {
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

Matrix Matrix::subtract(Matrix a, double b) {
    Matrix tmp = Matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            tmp.data[i][j] = a.data[i][j] - b;
        }
    }
    return tmp;
}

Matrix Matrix::subtract(double b, Matrix a) {
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
            tmp.data[i][j] = 1 / (1 + pow(euler, -1 * a.data[i][j] ) );
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
            double sum = 0;
            for (int k = 0; k < a.cols; k++) {
                sum += data[i][k] * a.data[k][j];
            }
            tmp.data[i][j] = sum;
        }
    }

    data = tmp.data;
}

void Matrix::multiply(double a) {
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
            data[i][j] = randdouble(-1, 1);
        }
    }
}

void Matrix::print() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%8.5f  ", data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

double Matrix::randdouble(double min, double max) {
    double tmp = (double)rand() / RAND_MAX;
    tmp *= (max - min);
    tmp += min;
    return tmp;
}

void Matrix::printDim() {
    printf("%dX%d\n", rows, cols);
}


double Matrix::average() {
    double sum = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sum += data[i][j];
        }
    }
    return sum/(rows*cols);
}

double Matrix::sum() {
    double ret = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            ret += data[i][j];
        }
    }
    return ret;
}

void Matrix::set() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            data[i][j] = 0;
        }
    }
}
