
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "parse.h"
#include "server.h"
#include "../global/debug.h"

UpdateObjectType *parseCommand(const char *in)
{

	UpdateObjectType *update;
	char *message;
	char *offset;

	int x;
	int oldyco, oldxco, newyco, newxco, setting; 

	update = (UpdateObjectType*)malloc(sizeof(UpdateObjectType));

	/* convert command to lower case */
	message = (char*)malloc(strlen(in) + 1);
	for(x = 0; x <= strlen(in); x++)
		message[x] = tolower(in[x]);

	if(sscanf(message, " %d , %d", &oldxco, &oldyco) != 2) {
		free(message);
		free(update);
		return NULL;
	}
 
	--oldxco;
	--oldyco;

	update->oldx = oldxco;
	update->oldy = oldyco;
	update->newx = oldxco;
	update->newy = oldyco;

	pthread_mutex_lock(&mapMutex);
	update->oldObject = map[oldyco][oldxco];
	update->newObject = map[oldyco][oldxco];
	pthread_mutex_unlock(&mapMutex);

	if(strstr(message, "on")) {
		update->newObject.active = 1;
	} else if(strstr(message, "off")) {
		update->newObject.active = 0;
	} else if(strstr(message, "open")) {
		update->newObject.active = 1;
	} else if(strstr(message, "close")) {
		update->newObject.active = 0;
	} else if(strstr(message, "unlock")) {
		update->newObject.locked = 0;
	} else if(strstr(message, "lock")) {
		update->newObject.locked = 1;
	} else if(strstr(message, "use")) {
		update->newObject.active = 1;
	} else if(strstr(message, "flush")) {
		update->newObject.active = 0;
	} else if((offset = strstr(message, "temp"))) {
		sscanf(offset, " temp %d", &setting);
		update->newObject.level[0] = setting;
		pthread_mutex_lock(&houseMutex);
		houseObject.level[0] = setting;
		pthread_mutex_unlock(&houseMutex);
	} else if((offset = strstr(message, "volume"))) {
		sscanf(offset, " volume %d", &setting); 
		update->newObject.level[1] = setting;
	} else if((offset = strstr(message, "channel"))) {
		sscanf(offset, " channel %d", &setting);
		update->newObject.level[0] = setting;
	} else if((offset = strstr(message, "to"))) {
		sscanf(offset, " to %d , %d", &newxco, &newyco);
		update->oldObject.type = TYPE_FLOOR;
		update->newx = newxco - 1;
		update->newy = newyco - 1;
	} else {
		free(message);
		free(update);
		return NULL;
	}

	/* Make sure the update message is valid */
	if(   update->newx < -1 || update->newx > HOUSE_WIDTH
		|| update->newy < -1 || update->newy > HOUSE_HEIGHT
		|| update->oldx < -1 || update->oldx > HOUSE_WIDTH
		|| update->oldy < -1 || update->oldy > HOUSE_HEIGHT) {

		free(message);
		free(update);
		return NULL;
	}

	free(message);
	return update;

}
