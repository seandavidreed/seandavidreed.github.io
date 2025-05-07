#include <random>
#include <ctime>
#include "k_way_merge.cpp"

void test1(MinHeap& minHeap, int size) {
	std::mt19937 mt(time(nullptr));
	for (int i = 0; i < size; i++) {
		int num = mt() % 30;
		myPair p(num, i);
		minHeap.insert(p);
	}
}

int main() {
	const int n = 7;
	const int m = 4;
	int arrays[n][m] = {
		{1,6,9,10},
		{12,18,19,34},
		{1,2,3,4},
		{4,8,9,67},
		{34,45,46,50},
		{12,13,20,21},
		{3,7,12,79}
	};

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::cout << arrays[i][j] << ' ';
		}
	}
	std::cout << std::endl;

	int* output = kWayMerge(arrays, n, m);

	for (int i = 0; i < n*m; i++) {
		std::cout << output[i] << ' ';
	}
	std::cout << std::endl;

	return 0;
}
