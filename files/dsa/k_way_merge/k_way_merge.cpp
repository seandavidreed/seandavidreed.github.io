#include <iostream>
#include <utility>

using myPair = std::pair<int, int>;

class MinHeap {
public:
	MinHeap(int size) {
	       	minHeap = new myPair[size];
		size = size;
		heapSize = 0;
	}

	int insert(myPair keyPair) {
		// Check if min-heap is already full
		if (heapSize == size) {
			return -1;
		}
		
		// Find correct location in min-heap for new element
		int i = heapSize;
		while (keyPair.first < minHeap[parent(i)].first && i > 0) {
			minHeap[i] = minHeap[parent(i)];
			i = parent(i);
		}
		
		// Insert key into min-heap at the correct location
		minHeap[i] = keyPair;
		heapSize++;

		std::cout << "INSERT" << std::endl;
		this->print();

		return 0;
	}

	void bubbleDown(int key) {
		while (1) {
			int left = leftChild(key+1) - 1;
			int right = rightChild(key+1) - 1;

			int smallest;
			if (left < heapSize && minHeap[left].first < minHeap[key].first) {
				smallest = left;
			}
			else {
				smallest = key;
			}

			if (right < heapSize && minHeap[right].first < smallest) {
				smallest = right;
			}

			if (smallest == key) break;

			myPair temp = minHeap[key];
			minHeap[key] = minHeap[smallest];
			minHeap[smallest] = temp;

			key = smallest;
		}

		std::cout << "BUBBLE-DOWN" << std::endl;
		this->print();
	}

	myPair extractMin() {	
		myPair keyPair = minHeap[0];
		heapSize--;
		minHeap[0] = minHeap[heapSize];
		std::cout << "EXTRACT-MIN" << std::endl;
		this->print();

		if (heapSize > 1) bubbleDown(0);

		return keyPair;
	}

	int isEmpty() {
		std::cout << "Heap Size: " << heapSize << std::endl;
		if (heapSize == 0) return 1;
		else return 0;
	}

	int leftChild(int key) { return key * 2; }
	int rightChild(int key) { return (key * 2) + 1; }
	int parent(int key) { return int(key / 2); }

	void print() {
		for (int i = 0; i < heapSize; i++) {
			std::cout << '(' << minHeap[i].first << ", ";
			std::cout << minHeap[i].second << ") ";
		}
		std::cout << std::endl;
	}
private:
	myPair* minHeap;
	int size;
	int heapSize;
};

template<std::size_t N>
int* kWayMerge(int arrays[][N], int n, int m) {
	// Declare a min-heap with aggregate size of arrays.
	MinHeap minHeap(n);

	// Initialize min-heap with the heads the arrays.
	for (int i = 0; i < n; i++) {
		myPair p(arrays[i][0], i);
		minHeap.insert(p);
	}
	
	// Initialize array of indices
	int indices[n] = {};
	std::fill_n(indices, n, 1);

	// Declare output array
	int* output = new int[n*m];
	int k = 0;

	while (1) {
		// Get smallest element from min-heap
		myPair min = minHeap.extractMin();
		
		// Add element to output array
		output[k] = min.first;
		k++;

		// Get index for next element to pull from arrays.
		int i = min.second;
		int j = indices[i];

		// If the chosen array is empty, find one that isn't.
		if (j == m) {	
			int empty = 1;
			for (int l = 0; l < n; l++) {
				j = indices[l];
				if (j < m) {
					empty = 0;
					i = l;
					break;
				}
			}
			if (empty) {
				while (!minHeap.isEmpty()) {
					myPair min = minHeap.extractMin();
					output[k] = min.first;
					k++;
				}
				break;
			}
		}
		indices[i]++;
	
		// Initialize new keyPair
		// Insert it into min-heap
		myPair keyPair(arrays[i][j], i);
		std::cout << "FLAG" << std::endl;
		minHeap.insert(keyPair);
		
	}

	return output;
}
