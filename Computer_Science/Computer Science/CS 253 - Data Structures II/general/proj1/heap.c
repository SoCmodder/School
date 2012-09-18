
void HeapSift(int *array, int x, int size) {
	int root;
	int y, finished;

	root = array[x];
	y = x << 1;

	finished = (y > size);
	while(!finished) {
		if(y < size) {
			if(array[y + 1] > array[y]) {
				++y;
			}
		}
		if(array[y] > root) {
			array[x] = array[y];
			x = y;
			y = x << 1;
			finished = (y > size);
		} else {
			finished = 1;
		}
	}
	array[x] = root;
}

void HeapSort(int *array, int size) {
	int temp;
	int x;

	--array;

	/* Heapify */
	for(x = size >> 1; x > 1; x--) {
		HeapSift(array, x, size);
	}

	for(x = size; x > 1; x--) {
		HeapSift(array, 1, x);
		temp = array[1];
		array[1] = array[x];
		array[x] = temp;
	}
}

