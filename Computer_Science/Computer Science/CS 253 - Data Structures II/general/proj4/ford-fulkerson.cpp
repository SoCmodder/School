
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int FindPath(int*, int*, int*, int, int, int start = 0, int len = 0);
int *DoFordFulkerson(int*, int, int start = 0, int end = -1);
void DisplayGraph(int*, int);
int *CreateInOutGraph(int*, int);
int CheckVertexConnectivity(int*, int);
int CalculateFlow(int*, int, int);
int CalculateEdges(int*, int);

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
int main(char argc, char **argv) {
	FILE *fd;
	struct timeval startTime, endTime;
	long totalTime;
	char id[4];
	int *temp;
	int *graph, *flow;
	int x, n;

	if(argc != 2) {
		printf("usage: %s <infile>\n", argv[0]);
		exit(1);
	}

	fd = fopen(argv[1], "r");
	if(!fd) {
		printf("error: could not open \"%s\" for input\n", argv[1]);
		exit(1);
	}

	fread(id, sizeof(char), 3, fd);
	id[3] = 0;
	if(strcmp(id, "mat")) {
		printf("error: invalid file format\n");
		fclose(fd);
		exit(1);
	}

	fscanf(fd, " %d", &n);

	graph = (int*)malloc(n * n * sizeof(int));

	for(x = 0; x < n * n; x++) {
		fscanf(fd, " %d", &graph[x]);
	}

	fclose(fd);

	for(x = 0; x < n * n; x++) {
		if(graph[x] == -1) {
			graph[x] = 0;
		}
	}

	gettimeofday(&startTime, 0);
	flow = DoFordFulkerson(graph, n);
	gettimeofday(&endTime, 0);
	//DisplayGraph(flow, n);
	free(flow);

	totalTime = 1000000 * (endTime.tv_sec - startTime.tv_sec);
	totalTime += endTime.tv_usec - startTime.tv_usec;

	printf("Graph with %d vertices and %d edges\n", n,
		CalculateEdges(graph, n));
	printf("Time to run Ford Fulkerson: %ld us\n", totalTime);

	gettimeofday(&startTime, 0);
	temp = CreateInOutGraph(graph, n);
	printf("Vertex connectivity: %d\n",
		CheckVertexConnectivity(temp, n * 2));
	gettimeofday(&endTime, 0);
	free(temp);

	totalTime = 1000000 * (endTime.tv_sec - startTime.tv_sec);
	totalTime += endTime.tv_usec - startTime.tv_usec;

	printf("Time to calculate vertex connectivity: %ld us\n", totalTime);

	exit(0);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
int CalculateEdges(int *graph, int size) {
	int x, y;
	int edges;

	edges = 0;
	for(x = 0; x < size; x++) {
		for(y = 0; y < size; y++) {
			if(graph[x * size + y] > 0) {
				++edges;
			}
		}
	}
	return edges;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
int *CreateInOutGraph(int *graph, int size) {
	int *inout;
	int x, y;

	inout = (int*)malloc((size * 2) * (size * 2) * sizeof(int));
	memset(inout, 0, (size * 2) * (size * 2) * sizeof(int));

	for(x = 0; x < size; x++) {
		for(y = 0; y < size; y++) {
			if(graph[x * size + y] > 0) {
				inout[(x * 2 + 1) * (size * 2) + y * 2] = 1;
			}
		}
	}
	for(x = 0; x < size * 2; x += 2) {
		inout[x * (size * 2) + (x + 1)] = 1;
	}

	return inout;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
int CalculateFlow(int *graph, int size, int end) {
	int x;
	int flow;

	flow = 0;
	for(x = 0; x < size; x++) {
		flow += graph[x * size + end];
	}
	return flow;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
int CheckVertexConnectivity(int *graph, int size) {
	int *flow;
	int min;
	int x, y, t;

	min = INT_MAX;
	for(x = 1; x < size - 1; x += 2) {
		for(y = x + 1; y < size; y += 2) {
			flow = DoFordFulkerson(graph, size, x, y);
			t = CalculateFlow(graph, size, y);
			if(t < min) {
				min = t;
			}
			free(flow);
		}
	}
	return min;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void DisplayGraph(int *graph, int size) {
	int x, y;

	for(x = 0; x < size; x++) {
		for(y = 0; y < size; y++) {
			if(graph[x * size + y] > 0) {
				printf("%d\t", graph[x * size + y]);
			} else {
				printf("0\t");
			}
		}
		printf("\n");
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
int *DoFordFulkerson(int *graph, int size, int start = 0, int end = -1) {
	int *flow;
	int minFlow;
	int *path, pathLength;
	int x, y, z;

	if(end < 0) {
		end = size - 1;
	}

	flow = (int*)malloc(size * size * sizeof(int));
	memset(flow, 0, size * size * sizeof(int));

	path = (int*)malloc(size * sizeof(int));

	while((pathLength = FindPath(graph, flow, path, size, end))) {
		minFlow = INT_MAX;
		for(x = 1; x < pathLength; x++) {
			y = path[x - 1] * size + path[x];
			if(graph[y] - flow[y] < minFlow) {
				minFlow = graph[y] - flow[y];
			}
		}

		for(x = 1; x < pathLength; x++) {
			y = path[x - 1] * size + path[x];
			z = path[x] * size + path[x - 1];
			flow[y] += minFlow;
			flow[z] = -flow[y];
		}
	}

	return flow;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
int FindPath(int *graph, int *flow, int *path, int size, int end,
	int start = 0, int len = 0) {

	int x, y;

	path[len] = start;

	if(start == size - 1) {
		return len + 1;
	}

	y = start * size + end;
	if(flow[y] < graph[y]) {
		for(y = 0; y < len; y++) {
			if(path[y] == end) {
				break;
			}
		}
		if(y == len) {
			y = FindPath(graph, flow, path, size, end,
				end, len + 1);
			if(y) {
				return y;
			}
		}
	}

	for(x = 0; x < size; x++) {
		y = start * size + x;
		if(flow[y] < graph[y]) {
			for(y = 0; y < len; y++) {
				if(path[y] == x) {
					break;
				}
			}
			if(y == len) {
				y = FindPath(graph, flow, path, size, end,
					x, len + 1);
				if(y) {
					return y;
				}
			}
		}
	}

	return 0;
}





