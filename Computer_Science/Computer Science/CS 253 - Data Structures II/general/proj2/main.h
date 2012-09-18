
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct Method {
	char *name;
	int (*function)();
};

struct Job {
	int deadline;
	int time;
	int profit;
	int order;
};

extern const struct Method methods[];
extern int n;
extern struct Job *jobs;

int main(int, char**);
int ReadFile(FILE*);
void DisplayArray(int*);
void ReleaseData();

int Recursive();
int Tabular();
int GreedyTime();
int GreedyTimeReverse();
int GreedyDeadline();
int GreedyDeadlineReverse();
int GreedyProfit();
int GreedyProfitReverse();

#endif

