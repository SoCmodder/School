
#include "sort.h"

struct SortRoutine {
	int number;
	char *name;
	void (*function)(int*,int);
};

const struct SortRoutine SORT_ROUTINES[] = {
//	number,	name,			function

	{1,	"Bubble",		BubbleSort	},
	{2,	"Heap",			HeapSort	},
	{3,	"Insertion",		InsertionSort	},
	{4,	"Merge",		MergeSort	},
	{5,	"Multiple List",	MultipleListSort},
	{6,	"Proxmap",		ProxmapSort	},
	{7,	"Quick",		QuickSort	},
	{8,	"Radix",		RadixSort	},
	{9,	"Selection",		SelectionSort	},
	{10,	"Shell",		ShellSort	},

	{0,	0,			0		}
	
};

const int BLOCK_SIZE = 128;

void DisplayUsage() {
	int x;

	printf("usage: soft <method> <infile> <outfile>\n");
	printf("methods:\n");

	for(x = 0; SORT_ROUTINES[x].number; x++) {
		printf("\t%2d %s\n", SORT_ROUTINES[x].number,
			SORT_ROUTINES[x].name);
	}
}

int main(int argc, char **argv) {
	FILE *inFile;
	FILE *outFile;
	struct timeval startTime, stopTime;
	unsigned long long totalTime;
	int len, max;
	int *array;
	int x, num;

	if(argc != 4) {
		DisplayUsage();
		exit(1);
	}

	inFile = fopen(argv[2], "r");
	if(!inFile) {
		printf("error opening %s for read\n", argv[2]);
		exit(1);
	}

	outFile = fopen(argv[3], "w");
	if(!outFile) {
		printf("error opening %s for write\n", argv[3]);
		fclose(inFile);
		exit(1);
	}

	printf("Initializing...\n");

	max = BLOCK_SIZE;
	len = 0;
	array = malloc(max * sizeof(int));
	for(;;) {
		fscanf(inFile, " %d\n", &array[len]);
		++len;
		if(feof(inFile)) {
			break;
		}
		if(len >= max) {
			max += BLOCK_SIZE;
			array = realloc(array, max * sizeof(int));
		}
	}

	num = atoi(argv[1]);
	for(x = 0; SORT_ROUTINES[x].number; x++) {
		if(SORT_ROUTINES[x].number == num) {

			printf("Sorting...\n");
			gettimeofday(&startTime, 0);
			(SORT_ROUTINES[x].function)(array, len);
			gettimeofday(&stopTime, 0);
			printf("Done\n");

			break;
		}
	}

	if(!SORT_ROUTINES[x].number) {
		DisplayUsage();
		fclose(inFile);
		fclose(outFile);
		exit(1);
	}

	totalTime = (stopTime.tv_sec - startTime.tv_sec);
	totalTime *= 1000000;
	totalTime += (stopTime.tv_usec - startTime.tv_usec);

	printf("Sort took %lld microseconds\n", totalTime);

	for(x = 0; x < len; x++) {
		fprintf(outFile, "%d\n", array[x]);
	}

	free(array);
	fclose(inFile);
	fclose(outFile);
	exit(0);
}


