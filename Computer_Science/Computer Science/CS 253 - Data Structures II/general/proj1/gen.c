
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int main(int argc, char **argv) {
	FILE *outFile;
	unsigned long num;
	unsigned long x, y;
	unsigned int *used;

	if(argc != 4) {
		printf("usage: gen <type> <number> <filename>\n");
		printf("types:\n");
		printf("\t1 - 0%% inverted without repetitions\n");
		printf("\t2 - 50%% inverted with repetitions\n");
		printf("\t3 - 50%% inverted without repetitions\n");
		printf("\t4 - 100%% inverted without repetitions\n");
		exit(1);
	}

	num = atoi(argv[2]);

	outFile = fopen(argv[3], "w");
	if(!outFile) {
		printf("error: could not open %s for write\n", argv[2]);
		exit(1);
	}

	switch(atoi(argv[1])) {
	case 1:
		for(x = 0; x < num; x++) {
			fprintf(outFile, "%ld\n", x);
		}
		break;
	case 2:
		srand(time(0));
		for(x = 0; x < num; x++) {
			fprintf(outFile, "%ld\n", rand() % num);
		}
		break;
	case 3:
		used = malloc(num * sizeof(int));
		memset(used, 0, sizeof(int) * num);
		srand(time(0));
		for(x = 0; x < num; x++) {
			y = rand() & 0x7FFF;
			y <<= 15;
			y |= rand() & 0x7FFF;
			y <<= 15;
			y |= rand() & 0x7FFF;
			y %= num;
			while(used[y]) {
				y = (y + 1) % num;
			}
			used[y] = 1;
			fprintf(outFile, "%ld\n", y);
		}
		free(used);
		break;
	case 4:
		for(x = num; x; x--) {
			fprintf(outFile, "%ld\n", x);
		}
		break;
	default:
		printf("error: invalid type\n");
		break;
	}

	fclose(outFile);

	exit(0);
}

