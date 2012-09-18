
#ifndef ASTAR_H
#define ASTAR_H

#define EXPANDSTATES 4
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#include <math.h>
#include "../global/queue.h"

typedef struct
{
	int x,y;
	float cost;
	void *State[EXPANDSTATES];
	void *Parent;
	
} AStarNode;

void cleanup();	/* works */
void printpath(AStarNode *a);	/* works */
int validposition(int x, int y);	/* works */
AStarNode *newnode(int x, int y, float cost, AStarNode *Parent); /* works */
void expandnode(AStarNode *node);	/* works */
void deletenode(AStarNode *node);	/* works */
void printnodecontents(AStarNode *node);	/* works */
void printmap(void);	/* works */
float heuristic(int x, int y, int gx, int gy); /* works */
int sameposition(AStarNode *a, AStarNode *b); /* works */
void pushnodeopen(AStarNode *a);		/* WORKS--I THINK */
void pushnodeclosed(AStarNode *a);
int findopennode(AStarNode *a);
int findclosednode(AStarNode *a);
int findopennodewithposition(AStarNode *a);
int findclosednodewithposition(AStarNode *a);
int FindBestNode();
AStarNode *removefromclosed(int index);
AStarNode *removefromopen(int index);
void pushsuccessors(AStarNode *a);
void movetoclosed(AStarNode *a);
QueueType *AStarSearch(int x, int y, int dx, int dy);


#endif
