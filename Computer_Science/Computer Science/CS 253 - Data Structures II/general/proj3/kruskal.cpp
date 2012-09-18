
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

const int INFINITY = -1;

struct Vertex {
	int parent;
	int next;
};

struct Edge {
	int v1, v2;
	int weight;
	int used;
};

struct AdjNode {
	int *weight;
	int *adj;
	int size;
};

void Kruskal();
void SiftHeap(int*, int, int);
void SortEdges(struct Edge*, int);
void MatrixToEdge(int*);
void EdgeToMatrix(int*, int);
void AdjToEdge(struct AdjNode*);
void *Allocate(int);
void GenerateDaVinci(int*, char*);
void DisplayMatrix(int*, int);

struct Vertex *vertices;
int *tails;
struct Edge *edges;
int n, numEdges;

int bytesAllocated;

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
	int maxEdges;
	struct timeval startTime, endTime;
	long totalTime;
	FILE *fd;
	struct AdjNode *adj;
	int *matrix;
	char type[4];
	int x, y, z;

	bytesAllocated = 0;

	matrix = 0;
	adj = 0;

	if(argc != 2) {
		printf("usage: %s <graphfile>\n", argv[0]);
		exit(1);
	}

	fd = fopen(argv[1], "r");
	if(!fd) {
		printf("error: could not open \"%s\" for input\n",
			argv[1]);
		exit(1);
	}

	fread(type, 1, 3, fd);
	type[3] = 0;

	fscanf(fd, " %d", &n);
	if(n <= 0) {
		printf("error: invalid input size\n");
		fclose(fd);
		exit(1);
	}

	if(!strcmp(type, "mat")) {
		matrix = (int*)Allocate(n * n * sizeof(int));
		for(x = 0; x < n; x++) {
			for(y = 0; y < n; y++) {
				fscanf(fd, " %d", &matrix[x * n + y]);
			}
		}
	} else if(!strcmp(type, "adj")) {
		adj = (struct AdjNode*)Allocate(n * sizeof(struct AdjNode));
		for(x = 0; x < n; x++) {
			fscanf(fd, " %d", &z);
			adj[x].size = z;
			if(z) {
				adj[x].adj = (int*)Allocate(z * sizeof(int));
				adj[x].weight = (int*)Allocate(z
					* sizeof(int));
			} else {
				adj[x].adj = 0;
				adj[x].weight = 0;
			}
			for(y = 0; y < z; y++) {
				fscanf(fd, " %d", &adj[x].adj[y]);
				fscanf(fd, " %d", &adj[x].weight[y]);
			}
		}
	} else {
		printf("error: unrecognized file format\n");
		fclose(fd);
		exit(1);
	}

	fclose(fd);

	maxEdges = (n * (n - 1)) / 2;
	edges = (struct Edge*)Allocate(maxEdges * sizeof(struct Edge));

	vertices = (struct Vertex*)Allocate(n * sizeof(struct Vertex));
	tails = (int*)Allocate(n * sizeof(int));

	if(matrix) {
		GenerateDaVinci(matrix, "in.davinci");
	} else {
		AdjToEdge(adj);
		matrix = (int*)malloc(n * n * sizeof(int));
		EdgeToMatrix(matrix, 1);
		GenerateDaVinci(matrix, "in.davinci");
	}

	gettimeofday(&startTime, 0);
	if(!strcmp(type, "adj")) {
		AdjToEdge(adj);
	} else {
		MatrixToEdge(matrix);
	}
	Kruskal();
	gettimeofday(&endTime, 0);

	endTime.tv_sec -= startTime.tv_sec;
	endTime.tv_usec -= startTime.tv_usec;
	totalTime = endTime.tv_usec + endTime.tv_sec * 1000000;

	EdgeToMatrix(matrix, 0);
	GenerateDaVinci(matrix, "out.davinci");

	free(matrix);
	free(edges);
	free(vertices);
	if(adj) {
		for(x = 0; x < n; x++) {
			free(adj[x].weight);
			free(adj[x].adj);
		}
		free(adj);
	}

	printf("Bytes Allocated: %d\n", bytesAllocated);
	printf("Algorithm run time: %ld us\n", totalTime);

	exit(0);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void GenerateDaVinci(int *matrix, char *fname) {
	FILE *fd;
	int x, y, z;

	fd = fopen(fname, "w");
	if(!fd) {
		printf("error: could not open %s\n", fname);
		return;
	}

	fprintf(fd, "[\n");
	for(x = 0; x < n; x++) {

		fprintf(fd, "l(\"%d\", n(\"%d\", ["
			"a(\"OBJECT\", \"%d\")], [", x, x, x);

		z = 0;
		for(y = x + 1; y < n; y++) {
			if(matrix[x * n + y] != INFINITY) {
				if(z) {
					fprintf(fd, ",");
				}
				z = 1;
				fprintf(fd, "l(\"%d->%d\","
					"e(\"%d\", [a(\"_DIR\", \"none\""
					")], r(\"%d\")))", x, y, y, y);
			}
		}
		fprintf(fd, "]))");
		if(x < n - 1) {
			fprintf(fd, ",");
		}
		fprintf(fd, "\n");
	}
	fprintf(fd, "]");

	fclose(fd);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void DisplayMatrix(int *matrix, int size) {
	int x, y;

	for(x = 0; x < size; x++) {
		for(y = 0; y < size; y++) {
			printf("%2d ", matrix[x * size + y]);
		}
		printf("\n");
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void *Allocate(int size) {

	bytesAllocated += size;

	return malloc(size);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void MatrixToEdge(int *graph) {
	int x, y;

	for(x = 0; x < n; x++) {
		vertices[x].parent = x;
		vertices[x].next = INFINITY;
		tails[x] = x;
	}

	numEdges = 0;
	for(x = 0; x < n; x++) {
		for(y = x + 1; y < n; y++) {
			if(graph[x * n + y] != INFINITY) {
				edges[numEdges].v1 = x;
				edges[numEdges].v2 = y;
				edges[numEdges].weight = 
					graph[x * n + y];
				edges[numEdges].used = 0;
				++numEdges;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void AdjToEdge(struct AdjNode *graph) {
	int x, y;

	for(x = 0; x < n; x++) {
		vertices[x].parent = x;
		vertices[x].next = INFINITY;
		tails[x] = x;
	}

	numEdges = 0;
	for(x = 0; x < n; x++) {
		if(graph[x].adj) {
			for(y = 0; y < graph[x].size; y++) {
				edges[numEdges].v1 = x;
				edges[numEdges].v2 = graph[x].adj[y];
				edges[numEdges].weight
					= graph[x].weight[y];
				edges[numEdges].used = 0;
				++numEdges;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void EdgeToMatrix(int *graph, int full) {
	int x;
	int v1, v2;
	int weight;

	for(v1 = 0; v1 < n; v1++) {
		for(v2 = 0; v2 < n; v2++) {
			graph[v1 * n + v2] = INFINITY;
			graph[v2 * n + v1] = INFINITY;
		}
	}
	for(x = 0; x < numEdges; x++) {
		if(edges[x].used || full) {
			v1 = edges[x].v1;
			v2 = edges[x].v2;
			weight = edges[x].weight;
			graph[v1 * n + v2] = weight;
			graph[v2 * n + v1] = weight;
		}
	}
	for(x = 0; x < n; x++) {
		graph[x * n + x] = 0;
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
int FindParent(int x) {
	if(vertices[x].parent != x) {
		vertices[x].parent = FindParent(vertices[x].parent);
	}
	return vertices[x].parent;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void Kruskal() {
	int v1, v2;
	int x, y;

	// Sort the edge list (non-decending)
	SortEdges(edges, numEdges);

	// Assert I1
	for(x = 0; x < numEdges; x++) {
		// Assert I1 and x < numEdges
		v1 = edges[x].v1;
		v2 = edges[x].v2;
		if(FindParent(v1) != FindParent(v2)) {
			edges[x].used = 1;
			y = FindParent(v2);
			// Assert I2
			while(y != INFINITY) {
				// Assert I2 and y != INFINITY
				vertices[y].parent = vertices[v1].parent;
				y = vertices[y].next;
				// Assert I2
			}
			// Assert !(y != INFINITY)
			vertices[tails[v1]].next = v2;
			tails[v1] = tails[v2];
		}
		// Assert I1
	}
	// Assert !(x < numEdges)

	// Loop Invariants
	// I1 : It has been determined whether edges 0 up to x - 1 should
	//	be included in the minimum spanning tree
	// I2 : The parent vertex for all vertices from v2 through
	//	(calculated from the "next" variable) have been set to
	//	point to the parent of v1 
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void SiftHeap(struct Edge *edges, int x, int size) {
	struct Edge root;
	int y, finished;

	root = edges[x];
	y = x << 1;

	finished = (y > size);
	while(!finished) {
		if(y < size && edges[y + 1].weight > edges[y].weight) {
			++y;
		}
		if(edges[y].weight > root.weight) {
			edges[x] = edges[y];
			x = y;
			y = x << 1;
			finished = (y > size);
		} else {
			finished = 1;
		}
	}
	edges[x] = root;
}

//////////////////////////////////////////////////////////////////////////
// Sort the edges of the graph in non-descending order, based on weight
// PRE: edges is a pointer to the edges of the graph
//	n is the number of elements to be sorted
// POST: edges points to the sorted edges, which are sorted by weight
//	in non-descending order
//////////////////////////////////////////////////////////////////////////
void SortEdges(struct Edge *edges, int n) {
	struct Edge temp;
	int x;

	// Change the pointer to the array so that it starts at 1
	// instead of 0
	--edges;

	// Assert I1
	for(x = n >> 1; x > 1; x--) {
		// Assert I1 and x > 1
		SiftHeap(edges, x, n);
		// Assert I1
	}
	// Assert !(x > 1)

	// Assert I2
	for(x = n; x > 1; x--) {
		// Assert I2 and x > 1
		SiftHeap(edges, 1, x);
		temp = edges[1];
		edges[1] = edges[x];
		edges[x] = temp;
		// Assert I2
	}
	// Assert !(x > 1)

	// Loop Invariants
	// I1 : edges[x] is the root of the max heap for
	//	x = n / 2 down to 1
	// I2 : edges[1] through edges[x] hold the smallest
	//	values in the array and edges[x + 1] through
	//	edges[n] hold the largest values in the array
}


