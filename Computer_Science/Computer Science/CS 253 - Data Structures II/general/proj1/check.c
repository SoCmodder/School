
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

	FILE *inFile;
	long last, cur;
	long inversions;
	long count;

	if(argc != 2) {
		printf("usage: check <filename>\n");
		exit(1);
	}

	inFile = fopen(argv[1], "r");
	if(!inFile) {
		printf("error: could not open %s for read\n", argv[1]);
		exit(1);
	}

	cur = 0;
	inversions = 0;
	count = 0;
	last = 0;
	for(;;) {
		fscanf(inFile, " %ld", &cur);
		if(feof(inFile)) {
			break;
		}
		if(cur < last) {
			++inversions;
		}
		last = cur;
		++count;
	}

	if(!count) {
		printf("file is empty\n");
	} else {
		printf("%ld inversions\n", inversions);
		printf("%ld numbers\n", count);
		printf("File is %f%% sorted\n",
			100.0 * ((double)(count - inversions) / (double)count));
	}

	fclose(inFile);
	exit(0);
}
