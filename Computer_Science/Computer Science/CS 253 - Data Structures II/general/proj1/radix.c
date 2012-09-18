
#include <stdlib.h>

const int NUM_BUCKETS = 100;

/******************************************************************************
 * Sort an array in ascending order using Radix Sort
 * PRE: array is a pointer to the array to be sorted
 *      size is the number of elements in the array
 * POST: array points to the sorted array
 *****************************************************************************/
void RadixSort(int *array, int size) {
	int x, y, z;
	int *buckets[NUM_BUCKETS];
	int count[NUM_BUCKETS];
	int mask;

	for(x = 0; x < NUM_BUCKETS; x++) {
		buckets[x] = malloc(size * sizeof(int));
	}

	for(mask = 1; mask; mask = mask << 1) {
		for(x = 0; x < NUM_BUCKETS; count[x++] = 0);

		for(x = 0; x < size; x++) {
			if(array[x] & mask) {
				z = 1;
			} else {
				z = 0;
			}
			buckets[z][count[z]++] = array[x];
		}

		z = 0;
		for(x = 0; x < NUM_BUCKETS; x++) {
			for(y = 0; y < count[x]; y++) {
				array[z++] = buckets[x][y];
			}
		}
	}

	for(x = 0; x < NUM_BUCKETS; x++) {
		free(buckets[x]);
	}
}
