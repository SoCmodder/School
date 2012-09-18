
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include "astar.h"
#include "server.h"
#include "../global/proto.h"
#include "../global/queue.h"
#include "../global/debug.h"

#define LISTBASESIZE 16

static int OpenListTop = 0;
static int ClosedListTop = 0;

static int OLSize = LISTBASESIZE;
static int CLSize = LISTBASESIZE;

static AStarNode **OpenList;
static AStarNode **ClosedList;
static QueueType *queue;

static int goalx, goaly;
static int sourcex, sourcey;

void cleanup()
{
	int x,y;
	AStarNode *temp;

	for(x = 0; x < OpenListTop; x++)
	{
		temp = OpenList[x];
		for(y = 0; y < EXPANDSTATES; y++)
		{
			if((AStarNode *)temp->State[y])
				free(temp->State[y]);
		}
	}
	for(x = 0; x < ClosedListTop; x++)
	{
		temp = ClosedList[x];
		for(y = 0; y < EXPANDSTATES; y++)
		{
			if((AStarNode *)temp->State[y])
				free(temp->State[y]);
		}
	}

	free(OpenList);
	free(ClosedList);
}

void printpath(AStarNode *a)
{
	AStarNode *temp;
	UpdateObjectType *update;
	int lastx, lasty;

	lastx = goalx;
	lasty = goaly;

	CreateQueue(&queue);

	for(temp = a->Parent; temp; temp = temp->Parent)
	{
		update = (UpdateObjectType*)malloc(sizeof(UpdateObjectType));
		update->newx = temp->x;
		update->newy = temp->y;
		update->oldx = lastx;
		update->oldy = lasty;
		Enqueue(&queue, update);
		lastx = temp->x;
		lasty = temp->y;
	}
}

int validposition(int x, int y)
{
	int ret = 0;
	pthread_mutex_lock(&mapMutex);
	if( (y < HOUSE_HEIGHT && y >= 0) && (x < HOUSE_WIDTH && x >= 0)
			&& (map[y][x].type == TYPE_FLOOR || map[y][x].type == TYPE_KID
			|| (map[y][x].type == TYPE_DOOR && !map[y][x].locked))) {
		ret = 1;
	}
	pthread_mutex_unlock(&mapMutex);
	return ret;
}

AStarNode *newnode(int x, int y, float cost, AStarNode *Parent)
{
	int b;
	AStarNode *node;

	if(!validposition(x,y))
		return NULL;

	node = (AStarNode *)malloc(sizeof(AStarNode));	
	node->x = x;
	node->y = y;
	node->cost = cost;
	
	node->Parent = Parent;

	for(b = 0; b < EXPANDSTATES; b++)
	{
		node->State[b] = NULL;	
	}

	return node;
}

void expandnode(AStarNode *node)
{
	float cost = 0;
	int count = 0;

	if(validposition(node->x, node->y - 1))	/* up */
	{
		count++;
		cost = node->cost + heuristic(node->x, node->y - 1, goalx, goaly) + 1;
		(AStarNode*)(node->State[UP]) = newnode(node->x, node->y - 1, cost, node);
	}
	if(validposition(node->x, node->y + 1))   /* down */		
	{
		count++;
		cost = node->cost + heuristic(node->x, node->y + 1, goalx, goaly) + 1;
		(AStarNode*)(node->State[DOWN]) = newnode(node->x, node->y + 1, cost, node);
	}
	if(validposition(node->x - 1, node->y))	/* left */
	{
		count++;
		cost = node->cost + heuristic(node->x - 1, node->y, goalx, goaly) + 1;
		(AStarNode*)(node->State[LEFT]) = newnode(node->x - 1, node->y, cost, node);
	}
	if(validposition(node->x + 1, node->y))	/* right */
	{
		count++;
		cost = node->cost + heuristic(node->x + 1, node->y, goalx, goaly) + 1;
		(AStarNode*)(node->State[RIGHT]) = newnode(node->x + 1, node->y, cost, node);
	}

}
void deletenode(AStarNode *node)
{
	if(node)
		free(node);
}

void printnodecontents(AStarNode *node)
{

	printf("Address: %lx\n", (unsigned long)node);
	printf("Parent: %lx\n", (unsigned long)node->Parent);
	printf("(x,y): (%d,%d)\n", node->x, node->y);
	printf("Cost: %f\n", node->cost);
}

float heuristic(int x, int y, int gx, int gy)
{
	float deltax, deltay;

	deltax = gx - x;
	deltay = gy - y;

	return sqrt( (deltax * deltax) + (deltay * deltay) );
}

int sameposition(AStarNode *a, AStarNode *b)
{
	if((a->x == b->x) && (a->y == b->y))
	{
		return 1;
	}

	return 0;
}

void pushnodeopen(AStarNode *a)
{
	if(OLSize <= OpenListTop)
	{
		OLSize += 12;
		OpenList = realloc(OpenList, OLSize * sizeof(AStarNode *));
	}
	(AStarNode*)(OpenList[OpenListTop]) = a;
	OpenListTop++;
}

void pushnodeclosed(AStarNode *a)
{
	if(CLSize <= ClosedListTop)	/* make array bigger .. */
	{
		CLSize += 12;
		ClosedList = realloc(ClosedList, CLSize * sizeof(AStarNode *));
	}

	(AStarNode*)(ClosedList[ClosedListTop]) = a;
	ClosedListTop++;
}

int findopennode(AStarNode *a)
{
	int found = -1;
	int x;

	for(x = 0; x < OpenListTop; x++)
	{
		if(OpenList[x] == a)
		{
			found = x;
			break;
		}
	}

	return found; 
}

int findclosednode(AStarNode *a)
{
	int found = -1;
	int x;

	for(x = 0; x < ClosedListTop; x++)
	{
		if(ClosedList[x] == a)
		{
			found = x;
			break;
		}
	}
	
	return found;
}

int findopennodewithposition(AStarNode *a)
{
	int x; 

	for(x = 0; x < OpenListTop; x++)
	{
		if(sameposition(a, OpenList[x]))
			return x;
	}

	return -1;
}

int findclosednodewithposition(AStarNode *a)
{
	int x; 

	for(x = 0; x < ClosedListTop; x++)
	{
		if(sameposition(a, ClosedList[x]))
			return x;
	}

	return -1;
}

int FindBestNode()
{
	float lowestcost, temp;
	int lowestnode = 0;
	int x;

	lowestcost = OpenList[0]->cost;
	for(x = 0; x < OpenListTop; x++)
	{
		temp = OpenList[x]->cost;			
		if(temp < lowestcost)
		{
			lowestcost = temp;
			lowestnode = x;
		}
	}

	return lowestnode;
}

AStarNode *removefromclosed(int index)
{
	int x;
	AStarNode *temp;

	temp = ClosedList[index];

	for(x = index; x < ClosedListTop - 1; x++)
	{
		ClosedList[x] = ClosedList[x + 1];
	}

	ClosedListTop--;
	return temp;
}

AStarNode *removefromopen(int index)
{
	int x;
	AStarNode *temp;

	temp = OpenList[index];

	for(x = index; x < OpenListTop - 1; x++)
	{
		OpenList[x] = OpenList[x + 1];
	}

	OpenListTop--;
	return temp;
}

void pushsuccessors(AStarNode *a)
{
	int x,  openindex, closedindex;
	AStarNode *temp, *other;

	for(x = 0; x < EXPANDSTATES; x++)
	{
		temp = (AStarNode *)(a->State[x]);	

		if(!temp)	 	/* if no node for this direction, next iteration */
			continue;

		closedindex = findclosednodewithposition(temp);
		if(closedindex != -1)
		{
			if(ClosedList[closedindex]->cost < temp->cost)
			  continue;
			/* if found a node with same position that has already been
			 * explored and it has a cost lower than this nodes, then
			 * check other State nodes .. Forget this one..
			 */
		}

		openindex = findopennodewithposition(temp);
		if(openindex != -1)
		{
			if(OpenList[openindex]->cost < temp->cost)
					  continue;
			/* if found a node with the same position that has not yet been
			 * explored, and it has a lower cost than this node, then 
			 * check other State nodes, forget this one.
			 */
		}

		openindex = findopennode(temp);
		if(openindex != -1) 
		{
			other = removefromopen(openindex);
 			deletenode(other); 
		}

		closedindex = findclosednode(temp);
		if(closedindex != -1)
		{
			other = removefromclosed(closedindex);
			deletenode(other);  
		}

		pushnodeopen(temp);		
	}

}

void movetoclosed(AStarNode *a)
{
	int x;
	AStarNode *temp;

	for(x = 0; x < OpenListTop; x++)
	{
		if(OpenList[x] == a)
			break;
	}

	temp = removefromopen(x);
	pushnodeclosed(temp);	

}

QueueType *AStarSearch(int x, int y, int dx, int dy)
{
	AStarNode *startstate;
	AStarNode *endstate;
	AStarNode *temp;
	
	goalx = dx;
	goaly = dy;
	sourcex = x;
	sourcey = y;
	queue = NULL;

	OpenListTop = 0;
	ClosedListTop = 0;

	OpenList = malloc(OLSize * sizeof(AStarNode*));
	ClosedList = malloc(CLSize * sizeof(AStarNode*));

	startstate = newnode(x, y, heuristic(x,y,dx,dy), NULL);
	endstate = newnode(dx, dy, 0, NULL);

	pushnodeopen(startstate);

	while(OpenListTop > 0)	/* while nodes remain unexplored... */
	{
		temp = removefromopen(FindBestNode());	
		if(sameposition(endstate, temp))
		{
			printpath(temp);

			cleanup();					/* Cleanup stuff */
			deletenode(startstate);
			deletenode(endstate);

			return queue;
		}
	
		expandnode(temp);	
		pushsuccessors(temp);

		pushnodeclosed(temp);
	}

	cleanup();							/* Cleanup stuff */
	deletenode(startstate);
	deletenode(endstate);

	return NULL;
}
