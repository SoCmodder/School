
#include <stdlib.h>


struct ProxmapNode {
	enum {EMPTY, NOT_MOVED, MOVED} status;
	unsigned int proxmap;
	unsigned int location;
	unsigned int key;
};

void ProxmapSort(int *in, int size) {
	unsigned int x, y;
	unsigned int total;
	unsigned int key, temp;
	float f;
	struct ProxmapNode *a;

	a = malloc(size * sizeof(struct ProxmapNode));

	key = in[0];
	for(x = 0; x < size; x++) {
		a[x].proxmap = 0;
		a[x].status = NOT_MOVED;
		a[x].key = in[x];
		if(in[x] > key) {
			key = in[x];
		}
	}

	for(x = 0; x < size; x++) {
		f = (float)a[x].key / key;
		y = f * size;
		a[x].location = y;
		++a[y].proxmap;
	}

	total = 0;
	for(x = 0; x < size; x++) {
		if(a[x].proxmap) {
			y = a[x].proxmap;
			a[x].proxmap = total;
			total += y;
		}
	}

	for(x = 0; x < size; x++) {
		a[x].location = a[a[x].location].proxmap;
	}

	for(x = 0; x < size; x++) {
		if(a[x].status == NOT_MOVED) {
			y = a[x].location;
			key = a[x].key;
			a[x].status = EMPTY;
			for(;;) {
				if(a[y].status == NOT_MOVED) {
					temp = a[y].key;
					a[y].key = key;
					key = temp;
					a[y].status = MOVED;
					y = a[y].location;
				} else if(a[y].status == MOVED) {
					if(key < a[y].key) {
						temp = a[y].key;
						a[y].key = key;
						key = temp;
					}
					++y;
				} else {
					a[y].key = key;
					a[y].status = MOVED;
					break;
				}
			}
		}
	}

	for(x = 0; x < size; x++) {
		in[x] = a[x].key;
	}
	free(a);
}


