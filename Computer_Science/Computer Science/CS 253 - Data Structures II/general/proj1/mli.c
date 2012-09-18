#include <stdlib.h>

const int MAX_LISTS = 1000;

typedef struct {
	int data;
	void *next;
} Element;

/******************************************************************************
 * Sort an array in ascending order using Multiple List Insertion
 * PRE: array is a pointer to the array to be sorted
 *      size is the number of elements in the array
 * POST: array points to the sorted array
 *****************************************************************************/
void MultipleListSort(int *array, int size) {
	int min, max, range;
	int x, y;
	Element *list[MAX_LISTS];
	Element *tp, *np;
	int numLists;

	/* Calculate the number lists */
	if(size > MAX_LISTS) {
		numLists = MAX_LISTS;
	} else {
		numLists = size;
	}

	/* Initialize the lists */
	for(x = 0;x < numLists; x++) {
		list[x] = 0;
	}

	/* Calculate the range */
	min = max = array[0];
	for(x = 0; x < size; x++) {
		if(array[x] > max) {
			max = array[x];
		} else if(array[x] < min) {
			min = array[x];
		}
	}
	range = (max - min) / numLists;

	/* Perform the insertion */
	for(x = 0; x < size; x++) {
		y = array[x] / (range + 1);
		np = malloc(sizeof(Element));
		if(list[y] && array[x] > list[y]->data) {
			for(tp = list[y]; tp->next; tp = tp->next) {
				if(array[x] < ((Element*)(tp->next))->data) {
					break;
				}
			}
			np->next = tp->next;
			tp->next = np;
		} else {
			np->next = list[y];
			list[y] = np;
		}
		np->data = array[x];
	}

	/* Merge the lists */
	for(y = x = 0; y < numLists; y++) {
		while(list[y]) {
			array[x++] = list[y]->data;
			tp = list[y]->next;
			free(list[y]);
			list[y] = tp;
		}
	}
}


