/****************************************************************************
 * CS 284 Operating Systems
 * Programming Assignment 8
 * Name:   message.h
 * Author: Chang Qian, Matt Walters, and Joe Wingbermuehle
 * Date:   2002-11-14
 ****************************************************************************/

#ifndef MESSAGE_H
#define MESSAGE_H

#define SERVER_PORT 2718

#define MAX_BUFFER 512
#define HOST_LENGTH 64
#define NAME_LENGTH 32

typedef enum {
	CONTROL_MSG,
	CONTROL_LOGIN,
	CONTROL_LOGOUT,
	CONTROL_TERM
} Control;

typedef struct {
	Control control;
	char name[NAME_LENGTH];
	char host[HOST_LENGTH];
	char message[MAX_BUFFER];
} Message;

#endif

