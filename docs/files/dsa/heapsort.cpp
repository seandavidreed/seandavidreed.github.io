#include <iostream>
#include <chrono>
#include <vector>
#include <ctime>
#include <random>

template<typename T>
class HeapVector: std::vector<T> {
public:

    // Alias "this" pointer
    HeapVector& hv = *this;

    HeapVector(std::size_t size) {
        std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
        for (std::size_t i = 0; i < size; i++) {
            hv.push_back(mt() % size);
        }
    }

    friend std::ostream& operator<< (std::ostream& output, const HeapVector<T>& hv) {
        for (std::size_t i = 0; i < hv.size(); i++) {
            output << hv[i] << ", ";
        }
        output << std::endl << std::endl;
        return output;
    }

private:
    void heapify(HeapVector& hv, int size, int index) {
        int largest = index;
        int l = (index * 2) + 1;
        int r = (index * 2) + 2;

        if (l < size && hv[l] > hv[largest]) largest = l;
        if (r < size && hv[r] > hv[largest]) largest = r;

        if (largest != index) {
            hv[index] ^= hv[largest];
            hv[largest] ^= hv[index];
            hv[index] ^= hv[largest];
            heapify(hv, size, largest);
        }
    }

public:
    void sort() {
        for (int i = hv.size() / 2 - 1; i >= 0; i--) {
            heapify(hv, hv.size(), i);
        }

        for (int i = hv.size() - 1; i > 0; i--) {
            hv[0] ^= hv[i];
            hv[i] ^= hv[0];
            hv[0] ^= hv[i];
            heapify(hv, i, 0);
        }
    }
};

int main() {
    HeapVector<int> vec(100);
    std::cout << vec << std::endl;
    vec.sort();
    std::cout << vec << std::endl;
    return 0;
}