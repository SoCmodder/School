/****************************************************************************
 * CS 284 Operating Systems
 * Programming Assignment 8
 * Name:   server.c
 * Author: Chang Qian, Matt Walters, and Joe Wingbermuehle
 * Date:   2002-11-14
 * Description:
 * Server for a simple chat program.
 ****************************************************************************/

#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <thread.h>
#include <synch.h>

#include "message.h"

#define MAX_CLIENTS	10

static int fdArray[MAX_CLIENTS];
static thread_t tid[MAX_CLIENTS];
static mutex_t fdMutex;

static struct sockaddr_in server_addr = { AF_INET, htons(SERVER_PORT) };
static struct sockaddr_in client_addr = { AF_INET };
static int sd;

static void *ConnectionThread(void *arg);
static void Terminate(int data);
static void FastExit(int data);

/****************************************************************************
 * Main entry point.
 ****************************************************************************/
int main(int argc, char *argv[]) {
	int ns;
	int x;
	int client_len = sizeof(client_addr);

	if(argc != 1) {
		printf("usage: %s\n", argv[0]);
		exit(1);
	}

	if( (sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		printf("%s: error: could not create socket\n", argv[0]);
		exit(1);
	}

	if(bind(sd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
		printf("%s: error: could not bind\n", argv[0]);
		exit(1);
	}

	if(listen(sd, MAX_CLIENTS) == -1) {
		printf("%s: error: listen()\n");
		exit(1);
	}

	printf("SERVER is listening for clients to establish a connection\n");
	printf("Type ^C to terminate the server.\n");

	for(x = 0; x < MAX_CLIENTS; x++) {
		fdArray[x] = -1;
	}

	signal(SIGALRM, SIG_IGN);
	signal(SIGQUIT, Terminate);
	signal(SIGTERM, Terminate);
	signal(SIGINT, Terminate);
	signal(SIGUSR1, FastExit);

	/* Wait for clients to connect */
	for(;;) {
		ns = accept(sd, (struct sockaddr*)&client_addr, &client_len);
		mutex_lock(&fdMutex);
		for(x = 0; x < MAX_CLIENTS; x++) {
			if(fdArray[x] < 0) {
				break;
			}
		}
		if(fdArray[x] >= 0) {
			break;
		}
		fdArray[x] = ns;
		mutex_unlock(&fdMutex);

		if(thr_create(0, 0, ConnectionThread, &ns, 0, &tid[x])) {
			printf("%s: error: could not create thread\n", argv[0]);
			printf("errno: %d\n", errno);
		}
	}
	unlink(server_addr.sin_addr);
	close(sd);

	printf("error: %s\n", argv[0]);

	return 0;
}

/****************************************************************************
 * Thread to manage a client.
 ****************************************************************************/
void *ConnectionThread(void *arg) {
	int ns = *(int*)arg;
	int x;
	Message msg;

	read(ns, &msg, sizeof(msg));

	printf("CLIENT %s@%s connected\n", msg.name, msg.host);

	/* Send greeting to all clients */
	mutex_lock(&fdMutex);
	for(x = 0; x < MAX_CLIENTS; x++) {
		if(fdArray[x] >= 0 && fdArray[x] != ns) {
			msg.control = CONTROL_LOGIN;
			write(fdArray[x], msg, sizeof(msg));
		}
	}
	mutex_unlock(&fdMutex);

	/* Wait for messages */
	while(read(ns, &msg, sizeof(msg)) != 0) {
		if(msg.control == CONTROL_LOGOUT) {
			mutex_lock(&fdMutex);
			for(x = 0; x < MAX_CLIENTS; x++) {
				if(fdArray[x] == ns) {
					fdArray[x] = -1;
				} else if(fdArray[x] >= 0) {
					write(fdArray[x], msg, sizeof(msg));
				}
			}
			mutex_unlock(&fdMutex);
			break;
		} else {
			mutex_lock(&fdMutex);
			printf("SERVER RECEIVED FROM %s@%s: %s\n", msg.name,
				msg.host, msg.message);
			for(x = 0; x < MAX_CLIENTS; x++) {
				if(fdArray[x] >= 0 && fdArray[x] != ns) {
					write(fdArray[x], msg, sizeof(msg));
				}
			}
			mutex_unlock(&fdMutex);
		}
	}
	close(ns);
	printf("CLIENT %s@%s closed\n", msg.name, msg.host);
	thr_exit(NULL);
}

/****************************************************************************
 * Terminate all threads, unbind, and exit.
 * Called when a signal is received.
 ****************************************************************************/
void Terminate(int data) {
	int x;
	Message msg;

	msg.control = CONTROL_TERM;

	printf("Sending terminate message to all clients...");
	fflush(stdout);
	mutex_lock(&fdMutex);
	for(x = 0; x < MAX_CLIENTS; x++) {
		if(fdArray[x] >= 0) {
			write(fdArray[x], msg, sizeof(msg));
			thr_kill(tid[x], SIGUSR1);
		}
	}
	mutex_unlock(&fdMutex);
	printf("done\n");
	unlink(server_addr.sin_addr);
	close(sd);
	thr_exit(NULL);
}

/****************************************************************************
 * Terminate this thread.
 * Called when SIGUSR1 is received (from Terminate).
 ****************************************************************************/
void FastExit(int data) {
	thr_exit(NULL);
}

