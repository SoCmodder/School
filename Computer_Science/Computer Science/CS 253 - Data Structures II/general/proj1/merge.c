
#include <stdlib.h>

/******************************************************************************
 * Sort an array in ascending order using Merge Sort
 * PRE: array is a pointer to the array to be sorted
 *      size is the number of elements in the array
 * POST: array points to the sorted array
 *****************************************************************************/
void MergeSort(int *array, int size) {
	int start, stop, middle;
	int x, y, z, i;
	int *lp, *tp, *temp;

	lp = malloc(size * sizeof(int));
	tp = array;
	for(i = 2; i < size << 1; i <<= 1) {
		for(start = 0; start < size; start += i) {
			stop = start + i - 1;
			middle = (stop + start) >> 1;
			if(stop >= size) stop = size - 1;
			if(middle >= size) middle = start;
			x = z = start; y = middle + 1;
			while(x <= middle && y <= stop) {
				if(tp[x] > tp[y]) lp[z++] = tp[y++];
				else lp[z++] = tp[x++];
			}
			while(x <= middle) lp[z++] = tp[x++];
			while(y <= stop) lp[z++] = tp[y++];
		}
		temp = tp; tp = lp; lp = temp;
	}
	if(tp != array) {
		for(x = 0; x < size; x++) {
			array[x] = tp[x];
		}
		free(tp);
	} else {
		free(lp);
	}
}
