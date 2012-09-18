/****************************************************************************
 * Functions for talking to the server.
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <pthread.h>
#include <signal.h>

#include "main.h"
#include "network.h"
#include "../global/debug.h"

static int sd;	/* Socket descriptor for the server */
static pthread_t utid;

static void *UpdateThread(void *arg);
static void UpdateTerminate(int sig);

/****************************************************************************
 * Establish a connection to host.
 ****************************************************************************/
void Connect(const char *host) {

	struct hostent *hp;
	struct sockaddr_in server_addr = { AF_INET, htons(SERVER_PORT) };

	if((hp = gethostbyname(host)) == NULL) {
		printf("error: unknown host: %s\n", host);
		exit(1);
	}
	bcopy(hp->h_addr_list[0], (char*)&server_addr.sin_addr, hp->h_length);

	if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		printf("error: socket failed\n");
		exit(1);
	}

	if(connect(sd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
		printf("error: could not connect to host\n");
		exit(1);
	}

	pthread_mutex_lock(&houseMutex);
	houseObject.type = TYPE_HOUSE;
	houseObject.active = 0;
	houseObject.locked = 0;
	houseObject.level[0] = 70;
	houseObject.level[1] = 0;
	pthread_mutex_unlock(&houseMutex);

	pthread_mutex_lock(&mapMutex);
	read(sd, map, sizeof(map));
	pthread_mutex_unlock(&mapMutex);

	if(pthread_create(&utid, NULL, UpdateThread, NULL)) {
		printf("error: could not create thread\n");
		Disconnect();
		exit(1);
	}

}

/****************************************************************************
 * Close the connection.
 ****************************************************************************/
void Disconnect() {
	pthread_kill(utid, SIGUSR1);
	close(sd);
}

/****************************************************************************
 * Send a message.
 ****************************************************************************/
void SendMessage(const char *msg) {
	write(sd, msg, MESSAGE_LENGTH);
}

/****************************************************************************
 * Thread to listen for updates.
 ****************************************************************************/
void *UpdateThread(void *arg) {
	UpdateObjectType msg;

	signal(SIGUSR1, UpdateTerminate);

	while(read(sd, &msg, sizeof(UpdateObjectType))) {

		if(msg.newx == -1 && msg.newy == -1) { 
			pthread_mutex_lock(&houseMutex);
			houseObject = msg.newObject;
			pthread_mutex_unlock(&houseMutex);
		} else if(msg.newx == -2 && msg.newy == -2) {
			pthread_mutex_lock(&flagMutex);
			parseError = 1;
			pthread_mutex_unlock(&flagMutex);
		} else if(msg.newx == -5 && msg.newy == -5) {
			pthread_mutex_lock(&flagMutex);
			done = 1;
			serverShutdown = 1;
			pthread_mutex_unlock(&flagMutex);
		} else {
			pthread_mutex_lock(&updateMutex);
			update[msg.oldy][msg.oldx] = 1;
			update[msg.newy][msg.newx] = 1;
			pthread_mutex_unlock(&updateMutex);
			pthread_mutex_lock(&mapMutex);
			map[msg.oldy][msg.oldx] = msg.oldObject;
			map[msg.newy][msg.newx] = msg.newObject;
			pthread_mutex_unlock(&mapMutex);
		}
		pthread_mutex_lock(&flagMutex);
		connected = 1;
		pthread_mutex_unlock(&flagMutex);

	}

	close(sd);
	return NULL;
}

/****************************************************************************
 * Signal handler to terminate the update thread.
 ***************************************************************************/
void UpdateTerminate(int sig) {
	pthread_exit(NULL);
}


