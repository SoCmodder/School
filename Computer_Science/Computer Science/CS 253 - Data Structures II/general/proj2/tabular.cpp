
#include "main.h"

struct TableType {
	int profit;
	int *order;
};

int FindOrderTabular(int, int);
struct TableType *table;

int Tabular() {
	int x, sum;
	int profit;

	// Sum up the max time it will take all the jobs to execute
	sum = 0;
	// Assert I1
	for(x = 0; x < n; x++) {
		sum += jobs[x].time;
	}

	table = (struct TableType*)malloc(n * sum * sizeof(struct TableType));
	if(!table) {
		printf("error: out of memory\n");
		exit(1);
	}

	// Allocate memory and initialize the table
	// Assert I2
	for(x = 0; x < n * sum; x++) {
		table[x].profit = -1;
		table[x].order = (int*)malloc(n * sizeof(int));
		if(!table[x].order) {
			printf("error: out of memory\n");
			exit(1);
		}
	}

	profit = FindOrderTabular(0, 0);

	// Free memory used in the table
	// Assert I3
	for(x = 0; x < n * sum; x++) {
		free(table[x].order);
	}
	free(table);

	return profit;

	// Loop Invariants
	// I1 : sum holds the total amount of time for jobs 0 to x - 1
	//	to execute
	// I2 : table has been initialized from 0 to x - 1
	// I3 : table has been freed from 0 to x - 1
}

int FindOrderTabular(int i, int T) {
	int maxp, maxn;
	int x, y;

	// Check if this subproblem has already been calculated
	if(table[T * n + i].profit >= 0) {

		// Check if any jobs conflict from the last time
		// this subproblem was calculated.
		// Loop through values used for this calculation
		y = 0;
		// Assert I1
		for(x = 0; x < i; x++) {

			// Loop through the values used in for the last
			// calculation
			// Assert I2
			for(y = i; y < n; y++) {
				if(jobs[x].order
					== table[T * n + i].order[y]) {
					break;
				}
			}
			if(y != n) {
				break;
			}
		}

		if(x == i && y == n) {
			// Store the order as was last calculated to the
			// current order
			// Assert I3
			for(x = i; x < n; x++) {
				jobs[x].order = table[T * n + i].order[x];
			}
			return table[T * n + i].profit;
		}
	}

	// Check every subproblem with job x at this location
	maxp = -1;
	maxn = -1;
	// Assert I4
	for(x = 0; x < n; x++) {

		// Make sure this job hasn't been scheduled yet.
		// Assert I5
		for(y = 0; y < i; y++) {
			if(jobs[y].order == x) {
				break;
			}
		}
		if(y == i) {
			y = 0;
			if(T + jobs[x].time <= jobs[x].deadline) {
				y = jobs[x].profit;
			}
			jobs[i].order = x;
			if(i + 1 < n) {
				y += FindOrderTabular(i + 1, T + jobs[x].time);
			}
			if(y > maxp) {
				maxp = y;
				maxn = x;
			}
		}
	}
	jobs[i].order = maxn;
	y = 0;
	if(T + jobs[maxn].time <= jobs[maxn].deadline) {
		y = jobs[maxn].profit;
	} else {
		// Assert I6
		for(x = i; x < n; x++) {
			jobs[x].order = -1;
		}
		return y;
	}
	if(i + 1 < n) {
		y += FindOrderTabular(i + 1, T + jobs[maxn].time);
	}

	// Save the subproblem ordering for later use via the table
	// Assert I7
	for(x = 0; x < n; x++) {
		table[T * n + i].order[x] = jobs[x].order;
	}
	table[T * n + i].profit = y;
	return y;

	// Loop Invariants
	// I1 : jobs 0 through x - 1 have not been used in the table entry
	// I2 : job orders i to x - 1 have been copied from the table
	//	into the jobs array
	// I3 : the schedule from the table from i to
	// I4 : all combinations with jobs 0 through x - 1 have been tried
	//	for this location in the schedule
	// I5 : job x has not been scheduled to run in position 0 through
	//	y - 1
	// I6 : job x - 1 has been set to order -1, which means not scheduled
	// I7 : jobs[i].order has been copied to table[T*n+i].order[i]
	//	for i = 0 to x - 1
}


