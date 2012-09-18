
#include <stdio.h>
#include <stdlib.h>

#include "server.h"
#include "../global/proto.h"
#include "../global/debug.h"

void ReadMap(const char *fileName) {
	FILE *fd;
	int x, y, z;

	fd = fopen(fileName, "r");
	if(!fd) {
		printf("Could not open \"%s\" for read\n", fileName);
		exit(1);
	}

	pthread_mutex_lock(&mapMutex);
	for(y = 0; y < HOUSE_HEIGHT; y++) {
		for(x = 0; x < HOUSE_WIDTH; x++) {
			if(fscanf(fd, " %d", &z) != 1) {
				printf("error reading \"%s\"\n", fileName);
				exit(1);
			}
			map[y][x].type = z;
		}
	}
	pthread_mutex_unlock(&mapMutex);

	fclose(fd);

}

