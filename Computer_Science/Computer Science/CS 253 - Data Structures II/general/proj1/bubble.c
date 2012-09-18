
/******************************************************************************
 * Sort an array in ascending order using Bubble Sort
 * PRE: array is a pointer to the array to be sorted
 *      size is the number of elements in the array
 * POST: array points to the sorted array
 *****************************************************************************/
void BubbleSort(int *array, int size) {
	int x, y;
	int temp;

	do {
		y = 0;
		for(x = 0; x < size - 1; x++) {
			if(array[x] > array[x + 1]) {
				temp = array[x];
				array[x] = array[x + 1];
				array[x + 1] = temp;
				y = 1;
			}
		}
	} while(y);
}
