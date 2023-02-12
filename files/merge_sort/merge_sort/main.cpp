#include <iostream>

const unsigned int _size {400};

void mergeSort1000(const unsigned int startElem, const unsigned int endElem, int arr[]) {
    // Base Case
    if (startElem == endElem) return;

    // Recursive Case
    const unsigned int mid {(startElem + endElem) / 2};
    mergeSort1000(startElem, mid, arr);
    mergeSort1000(mid + 1, endElem, arr);

    unsigned int lptr {startElem};
    unsigned int rptr {mid + 1};

    static int aux[1000] {};
    for (int i = startElem; i <= endElem; ++i) {
        if (lptr == (mid + 1)) aux[i] = arr[rptr++];
        else if (rptr == (endElem + 1)) aux[i] = arr[lptr++];
        else if (arr[lptr] >= arr[rptr]) aux[i] = arr[rptr++];
        else if (arr[lptr] < arr[rptr]) aux[i] = arr[lptr++];
    }

    for (int i = 0; i <= endElem; ++i)
        arr[i] = aux[i];
}

int main() {

    int testArray[_size];

    srand(time(NULL));
    for (int i = 0; i < _size; ++i) {
        testArray[i] = rand() % _size;
    }

    for (int i = 0; i < _size; ++i) {
        std::cout << testArray[i] << ' ';
    }
    std::cout << std::endl;
    mergeSort1000(0, _size - 1, testArray);

    for (int i = 0; i < _size; ++i) {
        std::cout << testArray[i] << ' ';
    }
    std::cout << std::endl;

    return 0;
}