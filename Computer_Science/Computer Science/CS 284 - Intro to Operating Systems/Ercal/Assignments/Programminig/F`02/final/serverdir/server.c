/***************************************************************************
 * Smart House server.
 ***************************************************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

#include "astar.h"
#include "server.h"
#include "parse.h"
#include "file.h"
#include "object.h"
#include "../global/proto.h"
#include "../global/queue.h"
#include "../global/debug.h"

#define TIME_MODULUS 1000
#define CHILD_MODULUS 1000
#define SLEEP_TIME 100

typedef struct {
	int tid;
	int ns;
} ThreadData;

typedef struct {
	int x, y;
} PersonObject;

ObjectType map[HOUSE_HEIGHT][HOUSE_WIDTH];
ObjectType houseObject;
static PersonObject child;
static ObjectType childBlock;

static QueueType *childPath = NULL;

static struct sockaddr_in server_addr = { AF_INET, htons(SERVER_PORT) };
static struct sockaddr_in client_addr = { AF_INET };
static int sd;
static int htid;

pthread_mutex_t clientMutex;
static ThreadData client[MAX_CLIENTS];

static QueueType *updateQueue = NULL;

pthread_mutex_t updateMutex;
pthread_mutex_t mapMutex;
pthread_mutex_t houseMutex;

static UpdateObjectType *GetHouseUpdate();
static void *HouseThread(void *arg);
static void *TalkThread(void *arg);
static void Terminate(int sig);
static void FastExit(int sig);
static void ActivateObject(int x, int y);
static int IsKidSafe(int x, int y);
inline static void MoveChild();
static void Change(int ox, int oy, int x, int y, int index);
static void FindObject(int *x, int *y);

/***************************************************************************
 ***************************************************************************/
int main(int argc, char *argv[]) {

	int client_len = sizeof(client_addr);
	int ns;
	int x, y;

	ReadMap("house.dat");

	pthread_mutex_lock(&mapMutex);
	for(y = 0; y < HOUSE_HEIGHT; y++) {
		for(x = 0; x < HOUSE_WIDTH; x++) {
			if(map[y][x].type == TYPE_KID) {
				child.x = x;
				child.y = y;
			}
		}
	}
	pthread_mutex_unlock(&mapMutex);

	pthread_mutex_lock(&houseMutex);
	houseObject.active = 0;
	houseObject.locked = 0;
	houseObject.level[0] = 70;
	houseObject.level[1] = 0;
	pthread_mutex_unlock(&houseMutex);

	childBlock.type = TYPE_FLOOR;
	childBlock.active = 0;
	childBlock.locked = 0;
	childBlock.level[0] = 0;
	childBlock.level[1] = 0;

	signal(SIGQUIT, Terminate);
	signal(SIGINT, Terminate);
	signal(SIGTERM, Terminate);

	if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		printf("%s: error: could not create socket\n", argv[0]);
		exit(1);
	}

	if(bind(sd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
		printf("%s: error: could not bind\n", argv[0]);
		exit(1);
	}

	if(listen(sd, MAX_CLIENTS) == -1) {
		printf("%s: error: listen()\n", argv[0]);
		exit(1);
	}

	for(x = 0; x < MAX_CLIENTS; x++) {
		client[x].ns = -1;
	}

	if(pthread_create(&htid, NULL, HouseThread, NULL)) {
		printf("%s: error: could not create thread\n", argv[0]);
	}

	printf("Press ^C to exit\n");

	for(;;) {
		ns = accept(sd, (struct sockaddr*)&client_addr, &client_len);
		pthread_mutex_lock(&clientMutex);
		for(x = 0; x < MAX_CLIENTS; x++) {
			if(client[x].ns < 0) {
				break;
			}
		}
		if(client[x].ns >= 0) {
			break;
		}
		client[x].ns = ns;
		pthread_mutex_unlock(&clientMutex);

		if(pthread_create(&client[x].tid, NULL, TalkThread, &client[x])) {
			printf("%s: error: could not create thread\n", argv[0]);
		}
	}

	close(sd);

	printf("%s: error: too many clients\n", argv[0]);

	return 0;
}

/***************************************************************************
 ***************************************************************************/
void *TalkThread(void *arg) {
	ThreadData data = *(ThreadData*)arg;
	char msg[MESSAGE_LENGTH];
	UpdateObjectType *update;
	UpdateObjectType errorMessage;
	int x;

	signal(SIGUSR1, FastExit);

	pthread_mutex_lock(&mapMutex);
	write(data.ns, map, sizeof(map));
	pthread_mutex_unlock(&mapMutex);

	update = GetHouseUpdate();
	write(data.ns, update, sizeof(UpdateObjectType));
	free(update);

	while(read(data.ns, msg, sizeof(msg)) != 0) {

		update = parseCommand(msg);
		if(update && update->newx >= 0 && update->newy >= 0) {
			pthread_mutex_lock(&mapMutex);
			map[update->oldy][update->oldx] = update->oldObject;
			map[update->newy][update->newx] = update->newObject;
			pthread_mutex_unlock(&mapMutex);
			if(update->newx != update->oldx || update->newy != update->oldy) {
				pthread_mutex_lock(&updateMutex);
				if(!updateQueue) {
					CreateQueue(&updateQueue);
				}
				Enqueue(&updateQueue, update);
				pthread_mutex_unlock(&updateMutex);
			} else {
				Change(update->newx, update->newy,
					update->newx, update->newy, 0);
			}
		} else if(!update) {
			errorMessage.newx = -2;
			errorMessage.newy = -2;
			errorMessage.oldx = -2;
			errorMessage.oldy = -2;
			write(data.ns, &errorMessage, sizeof(errorMessage));
		}
	}

	pthread_mutex_lock(&clientMutex);
	for(x = 0; x < MAX_CLIENTS; x++) {
		if(client[x].ns == data.ns) {
			client[x].ns = -1;
			break;
		}
	}
	pthread_mutex_unlock(&clientMutex);

	return NULL;
}

/***************************************************************************
 ***************************************************************************/
UpdateObjectType *GetHouseUpdate() {
	UpdateObjectType *msg;

	msg = (UpdateObjectType*)malloc(sizeof(UpdateObjectType));
	msg->oldx = -1;
	msg->oldy = -1;
	msg->newx = -1;
	msg->newy = -1;

	pthread_mutex_lock(&houseMutex);
	msg->newObject = houseObject;
	msg->oldObject = houseObject;
	pthread_mutex_unlock(&houseMutex);

	return msg;
}

/***************************************************************************
 ***************************************************************************/
void *HouseThread(void *arg) {
	UpdateObjectType *msg;
	int x;
	int timeCounter = 0;
	int childCounter = 0;

	signal(SIGUSR1, FastExit);

	srand48(time(NULL));

	for(;;) {
		pthread_mutex_lock(&updateMutex);
		if(updateQueue) {
			msg = Dequeue(&updateQueue);
			pthread_mutex_unlock(&updateMutex);
			pthread_mutex_lock(&clientMutex);
			for(x = 0; x < MAX_CLIENTS; x++) {
				if(client[x].ns > -1) {
					write(client[x].ns, msg, sizeof(UpdateObjectType));
				}
			}
			pthread_mutex_unlock(&clientMutex);
			free(msg);
			pthread_mutex_lock(&updateMutex);
		}
		pthread_mutex_unlock(&updateMutex);
		usleep(SLEEP_TIME);

		++timeCounter;
		if(timeCounter == TIME_MODULUS) {
			timeCounter = 0;
			pthread_mutex_lock(&houseMutex);
			houseObject.level[1] += 5;
			if((houseObject.level[1] & 0xFF) >= 60) {
				houseObject.level[1] &= ~0xFF;
				houseObject.level[1]
					= (houseObject.level[1] + 0x100) % (24 << 8);
			}
			pthread_mutex_unlock(&houseMutex);
			msg = GetHouseUpdate();
			pthread_mutex_lock(&updateMutex);
			if(!updateQueue) {
				CreateQueue(&updateQueue);
			}
			Enqueue(&updateQueue, msg);
			pthread_mutex_unlock(&updateMutex);
		}

		childCounter = (childCounter + 1) % CHILD_MODULUS;
		if(!childCounter) {
			MoveChild();
		}
	}

	return NULL;
}

/***************************************************************************
 ***************************************************************************/
void ActivateObject(int x, int y) {
	UpdateObjectType *msg;
	int temp;
	int a, b;
	int tx, ty;

	for(b = y - 1; b <= y + 1; b++) {
		if(b < 0 || b >= HOUSE_HEIGHT) {
			continue;
		}
		for(a = x - 1; a <= x + 1; a++) {
			if(a < 0 || b >= HOUSE_WIDTH) {
				continue;
			}
			tx = a;
			ty = b;
			FindObject(&tx, &ty);

			pthread_mutex_lock(&mapMutex);
			temp = !map[ty][tx].locked && !map[ty][tx].active
				&& objectDataMap[map[ty][tx].type].activatable;
			pthread_mutex_unlock(&mapMutex);

			if(temp) {
				msg = (UpdateObjectType*)malloc(sizeof(UpdateObjectType));
				msg->oldx = tx;
				msg->oldy = ty;
				msg->newx = tx;
				msg->newy = ty;

				pthread_mutex_lock(&mapMutex);
				map[ty][tx].active = 1;
				pthread_mutex_unlock(&mapMutex);

				Change(tx, ty, tx, ty, 0);

				pthread_mutex_lock(&mapMutex);
				msg->oldObject = map[ty][tx];
				msg->newObject = map[ty][tx];
				pthread_mutex_unlock(&mapMutex);

				pthread_mutex_lock(&updateMutex);
				if(!updateQueue) {
					CreateQueue(&updateQueue);
				}
				Enqueue(&updateQueue, msg);
				pthread_mutex_unlock(&updateMutex);
			}
		}
	}
}

/***************************************************************************
 ***************************************************************************/
inline int IsKidSafe(int x, int y) {
	int temp = 0;
	pthread_mutex_lock(&mapMutex);
	if(x >= 0 && x < HOUSE_WIDTH && y >= 0 && y < HOUSE_HEIGHT) {
		if(map[y][x].type == TYPE_FLOOR) {
			temp = 1;
		} else if(map[y][x].type == TYPE_DOOR && map[y][x].active) {
			temp = 1;
		}
	}
	pthread_mutex_unlock(&mapMutex);
	return temp;
}

/***************************************************************************
 ***************************************************************************/
void MoveChild() {
	UpdateObjectType *msg;
	ObjectType temp;
	int newx, newy;
	int block;

	while(!childPath) {
		do {
			newx = lrand48() % (HOUSE_WIDTH - 4) + 2;
			newy = lrand48() % (HOUSE_HEIGHT - 4) + 2;
			pthread_mutex_lock(&mapMutex);
			block = map[newy][newx].type;
			pthread_mutex_unlock(&mapMutex);
		} while(block != TYPE_FLOOR);
		childPath = AStarSearch(newx, newy, child.x, child.y);
	}

	msg = Dequeue(&childPath);

	pthread_mutex_lock(&mapMutex);
	temp = map[msg->newy][msg->newx];
	pthread_mutex_unlock(&mapMutex);

	if(temp.type == TYPE_DOOR && temp.locked) {
		while(childPath) {
			free(Dequeue(&childPath));
		}
	} else {
		pthread_mutex_lock(&mapMutex);
		map[msg->newy][msg->newx] = map[msg->oldy][msg->oldx];
		map[msg->oldy][msg->oldx] = childBlock;
		msg->oldObject = map[msg->oldy][msg->oldx];
		msg->newObject = map[msg->newy][msg->newx];
		pthread_mutex_unlock(&mapMutex);

		childBlock = temp;
		child.x = msg->newx;
		child.y = msg->newy;

		ActivateObject(child.x, child.y);

		pthread_mutex_lock(&updateMutex);
		if(!updateQueue) {
			CreateQueue(&updateQueue);
		}
		Enqueue(&updateQueue, msg);
		pthread_mutex_unlock(&updateMutex);
	}
}

/***************************************************************************
 ***************************************************************************/
void Terminate(int sig) {
	int x;
	UpdateObjectType shutdownMsg;

	shutdownMsg.newx = -5;
	shutdownMsg.newy = -5;
	shutdownMsg.oldx = -5;
	shutdownMsg.oldy = -5;

	pthread_kill(htid, SIGUSR1);

	pthread_mutex_lock(&clientMutex);
	for(x = 0; x < MAX_CLIENTS; x++) {
		if(client[x].ns >= 0) {
			pthread_kill(client[x].tid, SIGUSR1);
			write(client[x].ns, &shutdownMsg, sizeof(shutdownMsg));
			close(client[x].ns);
		}
	}
	pthread_mutex_unlock(&clientMutex);

	close(sd);

	exit(0);
}

/***************************************************************************
 ***************************************************************************/
void FindObject(int *x, int *y) {
	int a, b;
	int tx, ty;

	pthread_mutex_lock(&mapMutex);
	if(!map[*y][*x].type) {
		for(a = b = 1; b; a++) {
			for(ty = *y; b && *y - ty < a; ty--) {
				for(tx = *x; b && *x - tx < a; tx--) {
					switch(map[ty][tx].type) {
					case TYPE_HOUSE:
					case TYPE_FLOOR:
					case TYPE_WINDOW:
					case TYPE_DOOR:
					case TYPE_WALL:
					case TYPE_GRASS:
						break;
					default:
						*x = tx;
						*y = ty;
						b = 0;
						break;
					}
				}
			}
		}
	}
	pthread_mutex_unlock(&mapMutex);
}

/***************************************************************************
 ***************************************************************************/
void Change(int ox, int oy, int x, int y, int index) {
	UpdateObjectType *update;
	int beenThereX[10];
	int beenThereY[10];
	int block = map[oy][ox].type;
	int a;

	if(index >= 10 || !block) {
		return;
	}
	for(a = 0; a < index; a++) {
		if(beenThereX[a] == x && beenThereY[a] == y) {
			return;
		}
	}

	beenThereX[index] = x;
	beenThereY[index] = y;

	pthread_mutex_lock(&mapMutex);
	if(x != ox && y != oy && map[y][x].active == map[oy][ox].active
		&& map[y][x].locked == map[oy][ox].locked) {
		for(a = 0; a < LEVEL_COUNT; a++) {
			if(map[y][x].level[a] != map[oy][ox].level[a]) {
				break;
			}
		}
		if(a == LEVEL_COUNT) {
			pthread_mutex_unlock(&mapMutex);
			return;
		}
	}
	map[y][x].active = map[oy][ox].active;
	map[y][x].locked = map[oy][ox].locked;
	for(a = 0; a < LEVEL_COUNT; a++) {
		map[y][x].level[a] = map[oy][ox].level[a];
	}
	pthread_mutex_unlock(&mapMutex);

	update = (UpdateObjectType*)malloc(sizeof(UpdateObjectType));

	update->newx = x;
	update->newy = y;
	update->oldx = x;
	update->oldy = y;


	pthread_mutex_lock(&mapMutex);
	update->newObject = map[y][x];
	update->oldObject = map[y][x];
	pthread_mutex_unlock(&mapMutex);

	pthread_mutex_lock(&updateMutex);
	if(!updateQueue) {
		CreateQueue(&updateQueue);
	}
	Enqueue(&updateQueue, update);
	pthread_mutex_unlock(&updateMutex);

	
	if(x < HOUSE_WIDTH - 1 && map[y][x + 1].type == block) {
		Change(ox, oy, x + 1, y, index + 1);
	}
	if(x > 0 && map[y][x - 1].type == block) {
		Change(ox, oy, x - 1, y, index + 1);
	}
	if(y < HOUSE_HEIGHT - 1 && map[y + 1][x].type == block) {
		Change(ox, oy, x, y + 1, index + 1);
	}
	if(y > 0 && map[y - 1][x].type == block) {
		Change(ox, oy, x, y - 1, index + 1);
	}
}

/***************************************************************************
 ***************************************************************************/
void FastExit(int sig) {
	pthread_exit(NULL);
}


