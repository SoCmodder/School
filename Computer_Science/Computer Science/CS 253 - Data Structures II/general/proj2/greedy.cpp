
#include "main.h"

void HeapSift(int, int (*)(struct Job*, struct Job*));
void HeapSort(int (*)(struct Job*, struct Job*));
int CalculateProfit();

int CompareProfits(struct Job *a, struct Job *b) {
	return a->profit > b->profit;
}

int CompareProfitsReverse(struct Job *a, struct Job *b) {
	return a->profit < b->profit;
}

int CompareTimes(struct Job *a, struct Job *b) {
	return a->time > b->time;
}

int CompareTimesReverse(struct Job *a, struct Job *b) {
	return a->time < b->time;
}

int CompareDeadlines(struct Job *a, struct Job *b) {
	return a->deadline > b->deadline;
}

int CompareDeadlinesReverse(struct Job *a, struct Job *b) {
	return a->deadline < b->deadline;
}

int GreedyProfit() {
	HeapSort(CompareProfits);
	return CalculateProfit();
}

int GreedyProfitReverse() {
	HeapSort(CompareProfitsReverse);
	return CalculateProfit();
}

int GreedyTime() {
	HeapSort(CompareTimes);
	return CalculateProfit();
}

int GreedyTimeReverse() {
	HeapSort(CompareTimesReverse);
	return CalculateProfit();
}

int GreedyDeadline() {
	HeapSort(CompareDeadlines);
	return CalculateProfit();
}

int GreedyDeadlineReverse() {
	HeapSort(CompareDeadlinesReverse);
	return CalculateProfit();
}


int CalculateProfit() {
	int profit, time;
	int x;


	// Calculate the profit obtained by the input order
	time = 0;
	profit = 0;
	for(x = 0; x < n; x++) {
		time += jobs[x].time;
		if(time <= jobs[x].deadline) {
			profit += jobs[x].profit;
		}
	}
	return profit;

	// Loop Invariants:
	// I1 : profit holds the profit obtained by running
	//      jobs 0 through x - 1

}

void HeapSift(int x, int max, int (compare)(struct Job*, struct Job*)) {
	struct Job temp;
	int y, finished;

	temp = jobs[x - 1];
	y = x << 1;

	finished = (y > max);
	while(!finished) {
		if(y < max) {
			if((compare)(&jobs[y + 1 - 1], &jobs[y - 1])) {
				++y;
			}
		}
		if((compare)(&jobs[y - 1], &temp)) {
			jobs[x - 1] = jobs[y - 1];
			x = y;
			y = x << 1;
			finished = (y > max);
		} else {
			finished = 1;
		}
	}
	jobs[x - 1] = temp;
}

void HeapSort(int (compare)(struct Job*, struct Job*)) {
	struct Job temp;
	int x;

	// Build a max-heap
	// Assert I2
	for(x = n >> 1; x > 1; x--) {
		// Assert I2 and x > 1
		HeapSift(x, n, compare);
		// Assert I2
	}
	// Assert !(x > 1)

	// Assert I3
	for(x = n; x > 1; x--) {
		// Assert I3 and x > 1

		// re-heapify the max-heap
		HeapSift(1, x, compare);

		temp = jobs[1 - 1];
		jobs[1 - 1] = jobs[x - 1];
		jobs[x - 1] = temp;

		// Assert I3
	}
	// Assert !(x > 1)

	// Loop Invariants
	// I2 : jobs[x - 1] is the root of the max heap for
	//	x = n / 2 down to 1
	// I3 : jobs[1 - 1] through jobs[x - 1] hold the smallest
	//	values in the array and jobs[x - 1 + 1] through
	//	jobs[n - 1] hold the largest values in the array
}

