/****************************************************************************
 * CS 284 Operating Systems
 * Programming Assignment 8
 * Name:   client.c
 * Author: Chang Qian, Matt Walters, and Joe Wingbermuehle
 * Date:   2002-11-14
 * Description:
 * Client for a simple chat program.
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <thread.h>
#include <signal.h>

#include "message.h"

/* Argument for thr_create for ReaderThread */
typedef struct {
	int sd;
	thread_t parent;
} ReaderData;

static thread_t tid;

void *ReaderThread(void *arg);

/****************************************************************************
 * Main entry point.
 ****************************************************************************/
int main(int argc, char *argv[]) {

	ReaderData data;
	int sd;
	int temp;
	int x;
	struct sockaddr_in server_addr = { AF_INET, htons(SERVER_PORT) };
	struct hostent *hp;
	Message msg;

	printf("\x1B[1;37;40m");

	signal(SIGALRM, SIG_IGN);

	if(argc != 3) {
		printf("usage: %s nickname hostname\n", argv[0]);
		exit(1);
	}

	if((hp = gethostbyname(argv[2])) == NULL) {
		printf("%s: error: %s unknown host\n", argv[0], argv[2]);
		exit(1);
	}
	bcopy(hp->h_addr_list[0], (char*)&server_addr.sin_addr, hp->h_length);


	/* Create a socket */
	if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		printf("%s: error: socket failed\n", argv[0]);
		exit(1);
	}

	/* Connect to the server */
	if(connect(sd, (struct sockaddr*)&server_addr,
		sizeof(server_addr)) == -1) {
		printf("%s: error: could not connect to host\n", argv[0]);
		exit(1);
	}

	printf("Connected to %s\n", argv[2]);
	printf("Type \"exit\" to quit.\n");

	gethostname(msg.host, HOST_LENGTH);
	strncpy(msg.name, argv[1], NAME_LENGTH);
	write(sd, msg, sizeof(msg));

	data.sd = sd;
	data.parent = thr_self();
	thr_create(0, 0, ReaderThread, &data, 0, &tid);

	/* Wait for user input */
	do {
		for(x = 0; x < MAX_BUFFER; x++) {
			temp = getc(stdin);
			if(temp == '\n') {
				break;
			}
			msg.message[x] = temp;
		}
		msg.message[x] = 0;
		msg.control = CONTROL_MSG;

		write(sd, msg, sizeof(msg));
	} while(x != 4 || strncmp(msg.message, "exit", 4));

	thr_kill(tid, SIGINT);

	msg.control = CONTROL_LOGOUT;
	write(sd, msg, sizeof(msg));
	close(sd);

	printf("\x1B[0m\n");

	exit(0);
}

/****************************************************************************
 * Read messages from the server.
 ****************************************************************************/
void *ReaderThread(void *arg) {
	ReaderData *data = arg;
	Message msg;

	for(;;) {
		printf("\x1B[1;37;40m\n");
		read(data->sd, &msg, sizeof(msg));
		switch(msg.control) {
		case CONTROL_MSG:
			printf("\x1B[1;32;40m");
			printf("\n%s@%s: %s", msg.name, msg.host, msg.message);
			break;
		case CONTROL_LOGIN:
			printf("\x1B[1;33;40m");
			printf("\n*** %s@%s has logged in.", msg.name, msg.host);
			break;
		case CONTROL_LOGOUT:
			printf("\x1B[1;34;40m");
			printf("\n*** %s@%s has logged out.", msg.name, msg.host);
			break;
		case CONTROL_TERM:
			printf("\x1B[1;31;40m");
			printf("\nServer is shutting down, exiting.");
			close(data->sd);
			thr_kill(data->parent, SIGINT);
			printf("\x1B[0m\n");
			exit(0);
			break;
		default:
			printf("\nInvalid response from server.\n");
			break;
		}
	}
}


