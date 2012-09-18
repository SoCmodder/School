
#include "main.h"

int FindOrder(int, int);

int Recursive() {
	return FindOrder(0, 0);
}

int FindOrder(int i, int T) {
	int maxp, maxn;
	int x, y;

	maxp = -1;
	maxn = -1;
	// Try to schedule each job at this location in the order
	for(x = 0; x < n; x++) {

		// Determine if job x has already been scheduled
		// Assert I2
		for(y = 0; y < i; y++) {
			// Assert I2 and y < i
			if(jobs[y].order == x) {
				break;
			}
			// Assert I2
		}
		// Assert !(y < i) or jobs[y].order == x

		if(y == i) {
			y = 0;
			if(T + jobs[x].time <= jobs[x].deadline) {
				y = jobs[x].profit;
			}
			jobs[i].order = x;
			if(i + 1 < n) {
				y += FindOrder(i + 1, T + jobs[x].time);
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
		// Assert I3
		for(x = i; x < n; x++) {
			jobs[x].order = -1;
		}
		return y;
	}
	if(i + 1 < n) {
		y += FindOrder(i + 1, T + jobs[maxn].time);
	}
	return y;

	// Loop invariants:
	// I1 : every possible combination of jobs with job 0 through x - 1
	//	has been tried at this location in the job order
	// I2 : job x has not been scheduled at locations 0 through y - 1
	// I3 : job x - 1 is set to order -1, which means not scheduled
}


