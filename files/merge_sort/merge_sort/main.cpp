#include <iostream>

const unsigned int _size = 50;

void mergeSort(const unsigned int i, const unsigned int j, int arr[], int aux[]) {
    // Base Case
    if (i == j) return;

    // Recursive Case
    const unsigned int mid = (i + j) / 2;
    mergeSort(i, mid, arr, aux);
    mergeSort(mid + 1, j, arr, aux);

    int lptr = i;
    int rptr = mid + 1;

    for (int k = i; k <= j; ++k) {
        if (lptr == (mid + 1)) aux[k] = arr[rptr++];
        else if (rptr == (j + 1)) aux[k] = arr[lptr++];
        else if (arr[lptr] >= arr[rptr]) aux[k] = arr[rptr++];
        else if (arr[lptr] < arr[rptr]) aux[k] = arr[lptr++];
    }

    for (int k = 0; k <= j; ++k) {
        arr[k] = aux[k];
    }
}

int main() {

    int testArray[_size];
    int auxArray[_size];

    srand(time(NULL));
    for (int i = 0; i < _size; ++i) {
        testArray[i] = rand() % _size;
    }

    for (int i = 0; i < _size; ++i) {
        std::cout << testArray[i] << ' ';
    }
    std::cout << std::endl;
    mergeSort(0, _size - 1, testArray, auxArray);

    for (int i = 0; i < _size; ++i) {
        std::cout << testArray[i] << ' ';
    }
    std::cout << std::endl;

    return 0;
}