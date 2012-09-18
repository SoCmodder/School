
/******************************************************************************
 * Sort an array in ascending order using Insertion Sort
 * PRE: array is a pointer to the array to be sorted
 *      size is the number of elements in the array
 * POST: array points to the sorted array
 *****************************************************************************/
void InsertionSort(int *array, int size) {
	int x, y;
	int temp;

	for(x = 0; x < size; x++) {
		temp = array[x];
		for(y = x; y > 0 && temp < array[y - 1]; y--) {
			array[y] = array[y - 1];
		}
		array[y] = temp;
	}
}

