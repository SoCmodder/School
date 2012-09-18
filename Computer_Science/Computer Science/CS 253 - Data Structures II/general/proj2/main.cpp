
#include "main.h"

const struct Method methods[] = {
//	Name,					Function
	{"Dynamic (exact)",			Recursive		},
	{"Dynamic Tabular (exact)",		Tabular			},
	{"Greedy Deadline (approx)",		GreedyDeadline		},
	{"Greedy Deadline Reversed (approx)",	GreedyDeadlineReverse	},
	{"Greedy Profit (approx)",		GreedyProfit		},
	{"Greedy Profit Reversed (approx)",	GreedyProfitReverse	},
	{"Greedy Time (approx)",		GreedyTime		},
	{"Greedy Time Reversed (approx)",	GreedyTimeReverse	},
	{0,					0			}
};

int n;
struct Job *jobs;
int *order;

// Data file format:
//	- Number of jobs
//	- List (space separated) of times
//	- List (space separated) of profits
//	- List (space separated) of deadlines

int main(int argc, char **argv) {
	struct timeval startTime;
	struct timeval endTime;
	unsigned long executionTime;
	FILE *fd;
	int x;

	if(argc != 3) {
		printf("usage: %s <method> <datafile>\n", argv[0]);
		printf("methods:\n");
		for(x = 0; methods[x].name; x++) {
			printf("\t%2d - %s\n", x, methods[x].name);
		}
		exit(1);
	}

	jobs = 0;

	atexit(ReleaseData);

	fd = fopen(argv[2], "r");
	if(!fd) {
		printf("error: could not open \"%s\" for read\n", argv[2]);
		exit(1);
	}

	if(!ReadFile(fd)) {
		printf("error: file format invalid\n");
		exit(1);
	}

	fclose(fd);

	x = atoi(argv[1]);
	if(x < 0 || x >= signed(sizeof(methods) / sizeof(struct Method)) - 1) {
		printf("error: invalid selection\n");
		exit(1);
	}

	gettimeofday(&startTime, 0);
	x = (methods[x].function)();
	gettimeofday(&endTime, 0);

	executionTime = endTime.tv_sec * 1000000 + endTime.tv_usec;
	executionTime -= startTime.tv_sec * 1000000 + startTime.tv_usec;

	printf("Execution time: %ld us\n", executionTime);
	printf("Best solution yields a profit of %d.\n", x);
	printf("Order: ");
	for(x = 0; x < n && jobs[x].order >= 0; x++) {
		printf("%d ", jobs[x].order + 1);
	}
	printf("\n");

	exit(0);
}

int ReadFile(FILE *fd) {
	int x;

	fscanf(fd, " %d", &n);
	if(n <= 0) {
		return 0;
	}

	jobs = (struct Job*)malloc(n * sizeof(struct Job));
	if(!jobs) {
		printf("error: out of memory\n");
		exit(1);
	}

	for(x = 0; x < n; x++) {
		fscanf(fd, " %d", &jobs[x].time);
		jobs[x].order = x;
	}
	for(x = 0; x < n; x++) {
		fscanf(fd, " %d", &jobs[x].profit);
	}
	for(x = 0; x < n; x++) {
		fscanf(fd, " %d", &jobs[x].deadline);
	}

	if(ferror(fd) || feof(fd)) {
		return 0;
	} else {
		return 1;
	}
}

void ReleaseData() {
	if(jobs) {
		free(jobs);
	}
}

