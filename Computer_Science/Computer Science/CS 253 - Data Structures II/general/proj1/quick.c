
/******************************************************************************
 * Sort an array in ascending order using QuickSort
 * PRE: array is a pointer to the array to be sorted
 *      size is the number of elements in the array
 * POST: array points to the sorted array
 *****************************************************************************/
void QuickSort(int *array, int size) {
	int pivot, temp;
	int a, b;

	a = 0;
	b = size - 1;
	pivot = array[0];
	for(;;) {
		while(array[a] < pivot) ++a;
		while(array[b] > pivot) --b;
		if(a > b) break;
		temp = array[a];
		array[a] = array[b];
		array[b] = temp;
		++a; --b;
	}

	if(size > 1) {
		QuickSort(array, a);
		QuickSort(array + a, size - a);
	}
}

