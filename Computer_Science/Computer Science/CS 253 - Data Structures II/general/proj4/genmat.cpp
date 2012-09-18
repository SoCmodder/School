
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char **argv) {
	FILE *fd;
	int *graph;
	int *connected;
	int density;
	int n;
	int x, y, z;

	if(argc != 4) {
		printf("usage: %s <vertices> <density:0..100> <outfile>\n",
			argv[0]);
		exit(1);
	}

	n = atoi(argv[1]);
	if(n <= 0) {
		printf("error: invalid number of vertices\n");
		exit(1);
	}

	density = atoi(argv[2]);
	if(density < 0 || density > 100) {
		printf("error: density out of range\n");
		exit(1);
	}

	fd = fopen(argv[3], "w");
	if(!fd) {
		printf("error: \"%s\" could not be opened for output\n",
			argv[3]);
		exit(1);
	}

	graph = (int*)malloc(n * n * sizeof(int));
	connected = (int*)malloc(n * n * sizeof(int));
	if(!graph || !connected) {
		printf("error: out of memory\n");
		fclose(fd);
		exit(1);
	}

	srand(time(0));

	z = -2;
	for(x = 0; x < n; x++) {
		for(y = 0; y < n; y++) {
			if((rand() % 100) < density || z == -2) {
				z = rand() % 100;
				graph[x * n + y] = z;
			} else {
				graph[x * n + y] = 0;
			}
		}
		graph[x * n + x] = 0;
	}

	memset(connected, 0, n * sizeof(int));
	for(x = 0; x < n; x++) {
		for(y = x + 1; y < n; y++) {
			if(graph[x * n + y] != 0) {
				connected[x] = 1;
				break;
			}
		}
		if(connected[x]) {
			break;
		}
	}
	for(z = 0; z < n; z++) {
		for(x = 0; x < n; x++) {
			if(connected[x]) {
				for(y = x + 1; y < n; y++) {
					if(graph[x * n + y] != 0) {
						connected[y] = 1;
					}
				}
			}
		}
	}

	for(x = 0; x < n; x++) {
		if(!connected[x]) {
			do {
				z = rand() % n;
			} while(!connected[z]);
			y = rand() % 100;
			graph[x * n + z] = y;
			graph[z * n + x] = y;
			connected[z] = 1;
		}
	}

	fprintf(fd, "mat %d\n", n);

	for(x = 0; x < n; x++) {
		for(y = 0; y < n; y++) {
			fprintf(fd, " %d", graph[x * n + y]);
		}
		fprintf(fd, "\n");
	}

	free(graph);
	fclose(fd);

	exit(0);
}



