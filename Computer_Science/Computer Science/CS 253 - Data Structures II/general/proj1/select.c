
/******************************************************************************
 * Sort an array in ascending order using Selection Sort
 * PRE: array is a pointer to the array to be sorted
 *      size is the number of elements in the array
 * POST: array points to the sorted array
 *****************************************************************************/
void SelectionSort(int *array, int size) {
	int x, y, z;
	int temp;

	for(x = 0; x < size; x++) {
		z = x;
		temp = array[x];
		for(y = x + 1; y < size; y++) {
			if(array[y] < temp) {
				temp = array[y];
				z = y;
			}
		}

		array[z] = array[x];
		array[x] = temp;
	}
}
