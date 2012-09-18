
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Node {
	int size;
	int *weight;
	int *adj;
};

const int INFINITY = -1;

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
	FILE *fd;
	struct Node *nodes;
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
	connected = (int*)malloc(n * sizeof(int));
        if(!graph || !connected) {
                printf("error: out of memory\n");
                fclose(fd);
                exit(1);
        }

	nodes = (struct Node*)malloc(n * sizeof(struct Node));
	if(!nodes) {
		printf("error: out of memory\n");
		free(graph);
		fclose(fd);
		exit(1);
	}

        srand(time(0));

	z = -2;
        for(x = 0; x < n; x++) {
                graph[x * n + x] = 0;
                for(y = x + 1; y < n; y++) {
                        if((rand() % 100) < density || z == -2) {
                                z = rand() % 100;
                                graph[x * n + y] = z;
                                graph[y * n + x] = z;
                        } else {
				graph[x * n + y] = INFINITY;
				graph[y * n + x] = INFINITY;
			}
                }
        }

        memset(connected, 0, n * sizeof(int));
        for(x = 0; x < n; x++) {
                for(y = x + 1; y < n; y++) {
                        if(graph[x * n + y] != INFINITY) {
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
                                        if(graph[x * n + y] != INFINITY) {
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


	fprintf(fd, "adj %d\n", n);

	for(x = 0; x < n; x++) {
		nodes[x].weight = (int*)malloc(n * sizeof(int));
		nodes[x].adj = (int*)malloc(n * sizeof(int));
		nodes[x].size = 0;
		for(y = x + 1; y < n; y++) {
			z = graph[x * n + y];
			if(z != INFINITY) {
				nodes[x].weight[nodes[x].size] = z;
				nodes[x].adj[nodes[x].size] = y;
				++nodes[x].size;
			}
		}
	}

	for(x = 0; x < n; x++) {
		fprintf(fd, "%d ", nodes[x].size);
		for(y = 0; y < nodes[x].size; y++) {
			fprintf(fd, "%d ", nodes[x].adj[y]);
			fprintf(fd, "%d ", nodes[x].weight[y] % 100);
		}
		fprintf(fd, "\n");
	}

	free(graph);
	for(x = 0; x < n; x++) {
		free(nodes[x].weight);
		free(nodes[x].adj);
	}
	free(nodes);
	fclose(fd);

	exit(0);
}



