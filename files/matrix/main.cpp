#include <iostream>
#include <cstdlib>

class Matrix {

    int **matrix;
    int _rows, _cols;

public:

    Matrix(int rows, int cols) {
        _rows = rows;
        _cols = cols;
        matrix = new int*[rows];
        for (int i = 0; i < _rows; ++i) {
            matrix[i] = new int[_cols];
        }
    }

    ~Matrix() {
        for (int i = 0; i < _rows; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    void populate() {
        srand(time(NULL));
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                matrix[i][j] = rand() % 1000;
            }
        }
    }

    void print() {
        for (int i = 0; i < _rows; ++i) {
            std::cout << "{ ";
            for (int j = 0; j < _cols; ++j) {
                std::cout << matrix[i][j] << ", ";
            }
            std::cout << "}," << std::endl;
        }
    }
};

int main() {

    Matrix matrix(10, 10);
    matrix.populate();
    matrix.print();

    return 0;
}