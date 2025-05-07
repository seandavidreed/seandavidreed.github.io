/*
 * Date: 2025-03-05
 * Goal: Write Bubble Sort from scratch as an exercise.
 * Pseudocode:
 *
 * For i = 1 to n
 * 	For j = 1 to n - i
 * 		if ( a[j] > a[j + 1] ) Swap(a[j], a[j + 1])
 * 	End-for
 * End-for
 */

#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int arr[], int size);
void print(int arr[], int size, char *message);

int main() {
	// Initialize and print unsorted array 
	int arr[10] = { 6, 4, 2, 8, 3, 9, 1, 10, 5, 7 };
	print(arr, 10, "Unsorted Array:");

	// Call bubble_sort on unsorted array
	bubble_sort(arr, 10);
	
	// Print sorted array
	print(arr, 10, "Sorted Array:");
	return 0;
}

void bubble_sort(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}	
	} 
}

void print(int arr[], int size, char *message) {
	printf("%s\n", message);
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n\n");
}
