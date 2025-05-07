#include <iostream>
#include <cstdlib>

class Matrix {
    // Attributes
    int **matrix {};
    int _rows {}, _cols {};

public:
    // Constructor
    Matrix(int rows, int cols) {
        _rows = rows;
        _cols = cols;
        matrix = new int*[rows];
        for (int i = 0; i < _rows; ++i) {
            matrix[i] = new int[_cols];
        }
    }

    // Destructor
    ~Matrix() {
        for (int i = 0; i < _rows; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    // Methods
    void populate() {
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                std::cout << "For Element [" << i << "][" << j << "]: ";
                std::cin >> matrix[i][j];
            }
        }
    }

    void randPopulate() {
        srand(time(NULL));
        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                matrix[i][j] = rand() % 1000;
            }
        }
    }

    void sort() {
        int iSmall {0}, jSmall {0};
        int iStart {0}, jStart {0};
        int i {0}, j {1};
        bool changes {1};

        while (changes) {
            changes = 0;
            while (i < _rows) {
                if (matrix[i][j] < matrix[iSmall][jSmall]) {
                    iSmall = i;
                    jSmall = j;
                    changes = 1;
                }
                ++j;
                if (j == _cols) {
                    ++i;
                    j = 0;
                }
            }

            int temp = matrix[iSmall][jSmall];
            matrix[iSmall][jSmall] = matrix[iStart][jStart];
            matrix[iStart][jStart] = temp;

            ++jStart;
            if (jStart == _cols) {
                ++iStart;
                jStart = 0;
            }

            i = iStart;
            j = jStart;
            
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

    void printAddresses() {
        for (int i = 0; i < _rows; ++i) {
            std::cout << "{ ";
            for (int j = 0; j < _cols; ++j) {
                std::cout << &matrix[i][j] << ", ";
            }
            std::cout << "}," << std::endl;
        }
    }
};

int main() {

    Matrix matrix(2, 8);
    matrix.randPopulate();
    matrix.printAddresses();

    std::cout << std::endl;
    
    matrix.print();

    std::cout << std::endl;

    matrix.sort();
    matrix.print();

    return 0;
}