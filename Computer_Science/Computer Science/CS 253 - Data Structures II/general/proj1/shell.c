
/******************************************************************************
 * Sort an array in ascending order using Shell's Method
 * PRE: array is a pointer to the array to be sorted
 *      size is the number of elements in the array
 * POST: array points to the sorted array
 *****************************************************************************/
void ShellSort(int *array, int size) {
	int off;
	int x, y;
	int temp;

	for(off = size >> 1; off; off >>= 1) {
		do {
			for(y = x = 0; x < size - off; x++) {
				if(array[x] > array[x + off]) {
					temp = array[x];
					array[x] = array[x + off];
					array[x + off] = temp;
					y = 1;
				}
			}
		} while(y);
	}
}
